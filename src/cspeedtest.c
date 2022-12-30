#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <math.h>
#include <sys/time.h>
#include <getopt.h>
#include "curslib.h"
#include "timecurses.h"


// Constants
#define BAR_WIDTH 32

// Global parameters
static int debug_flag = 0;  // default to no debug info
static int color_flag = 1;  // default color, or -1 if non-interactive
static int run_test = 0;  // default no test
static int inter = 0;  // default to non-interactive
static int screen_index = 0;  // default to random
static int screen_count;
static screen_display* screen_table;
static screen_fun_ptr screen_fun;
int Tave = 5 * 1000000;  // 5 sec (usec)

void print_usage ()
{
   if (!inter)  // normal mode
   {
      printf("Usage: cspeedtest [options]\n\n");
      printf("Options:\n");
      printf("  -h, --help\t\tshow this help\n");
      printf("  -t T, --int=T\t\tintegration time in seconds\n");
      printf("  -i, --interactive\tinteractive mode\n");
      printf("  -b, --low-bw\t\tlow bandwidth mode\n");
      printf("  -V, --version\t\tdisplay version\n");
   }
   else
   {
      printf("Usage: cspeedtest-int [options]\n\n");
      printf("Options:\n");
      printf("  -h, --help\t\tshow this help\n");
      printf("  -i T, --int=T\t\tintegration time in seconds\n");
      printf("  -b, --low-bw\t\tlow bandwidth mode\n");
      printf("  -V, --version\t\tdisplay version\n");
      printf("  -v, --verbose\t\tprint debug info\n");
   }
}

void print_version (char* name)
{
   printf(PACKAGE_STRING);
   printf("\n");
   printf("Copyright 2022, Jonathan R. Birge\n");
   printf("Bug reports to ");
   printf(PACKAGE_BUGREPORT);
   printf("\n%s\n", name);
}

int main (int argc, char **argv)
{
   WINDOW *wnd;  // curses window
   int nrows, ncols;  // win size
   char* name = argv[0];  // called name

   // determine mode from calling name
   if (strstr(name, "cspeedtest-int") != NULL)
   {
     inter = 1;
   }
   else
   {
     inter = 0;
     color_flag = -1;
   }
   
   // options and defaults
   if (HAVE_GETOPT_LONG)
   {
      int opt;
      int option_index = 0;
      int T;

      struct option long_options[] =
      {
         {"verbose", no_argument, 0, 'v'},
         {"low-bw", no_argument, 0, 'b'},
         {"int", required_argument, 0, 't'},
	 {"interactive", required_argument, 0, 'i'},
         {"version", no_argument, 0, 'V'},
         {"help", no_argument, 0, 'h'},
	 {"test", no_argument, 0, 'x'},  // hidden option
         {0, 0, 0, 0}
      };

      while ((opt = getopt_long(argc, argv, "t:hiVbvx", long_options, &option_index)) != -1)
      {
         switch (opt)
         {
         case 'h':
            print_usage();
            return (0);
         case 'V':
            print_version(argv[0]);
            return (0);
	 case 'i':
	    inter = 1;
	    break;
         case 'b':
	    color_flag = 0;
         case 't':
            T = atoi(optarg);  // user specified in seconds
            if (T < 1)
            {
               fprintf(stderr, "Invalid integration time specified. Ignoring.\n");
            }
            else
            {
               fprintf(stderr, "Setting integration time to %d seconds.\n", T);
               Tave = T*1000000;  // convert to microsecs
            }
            break;
	 case 'x':
	    run_test = 1;
	    break;
         case 'v':
            debug_flag = 1;
            break;
         }
      }
   }  // end of getoptlong

   // if testing, just exit with success if we got this far
   if (run_test)
   {
     return 0;
   }
   
   // init ncurses
   wnd = initscr();
   nodelay (wnd, TRUE);
   cbreak();
   noecho();
   start_color();
   init_colors();
   clear();
   refresh();

   // init screens
   init_screen_table();
   screen_count = get_screen_count();
   screen_table = get_screen_table();
   screen_fun = screen_table[screen_index].fun;
   
   /*** main loop ***/
   struct timeval systime;
   long k = -1;  // frame counters
   long bits = 0;  // estimate of bits sent
   int T, T0;  // usec
   int doreset = 1;  // reset counter
   int done = 0;  // quit next loop
   while (!done)
   {
      // update frame counter
      ++k;
      
      // screen update
      getmaxyx (wnd, nrows, ncols);

      // timing
      gettimeofday (&systime, NULL);
      T = 1000000*systime.tv_sec + systime.tv_usec;

      // handle reset
      if (doreset)
      {
        bits = 0;
        T0 = T;
	doreset = 0;
      }

      // interface polling
      if (!(k % 4))
      {
         char d = getch ();
         switch (d)
         {
         case 'q':
            done = 1;
            break;
         case 'c':
	    if (inter)
	    {
	       color_flag = !color_flag;
	       doreset = 1;
	    }
            break;
         case 'r':
	    if (inter)
	    {
	       screen_index = (screen_index + 1) % screen_count;
	       screen_fun = screen_table[screen_index].fun;
	       doreset = 1;
	    }
            break;
         case 'v':
            debug_flag = !debug_flag;
            break;
         }

	 if (inter)
	   static_display(nrows, ncols, inter, color_flag, debug_flag, screen_table[screen_index].name);
	 else
	   static_display(nrows, ncols, inter, color_flag, 0, "non-interactive mode");
	 
         if (debug_flag)
         {
            move (nrows - 2, 0);
            printw("dT = %f sec", (double) (T - T0)/1000000.0);
         }
      }

      // write screen
      if (inter)
	bits += screen_fun(nrows, ncols, color_flag);
      else
	bits += screen_fun(nrows, ncols, color_flag);

      // update display
      if (!(k % 16) && !doreset)
      {
         display_mbps (bits, nrows, ncols, screen_index, 0);
         attron (COLOR_PAIR(1));
         drawbar ((double) (T - T0)/Tave, BAR_WIDTH, 0, 14);
         attroff (COLOR_PAIR(1));
      }

      // done with integration time
      if (((T - T0) >= Tave))
      {
	 if (!inter)
	 {
	    done = 1;
	 }
	 else
	 {
	    display_mbps (bits, nrows, ncols, screen_index, 1);
	    drawbar (0, BAR_WIDTH, 0, 14);
	    bits = 0;
	    T0 = T;
	    k = -1;
	 }
      }

      // loop clean-up
      refresh();
   }

   endwin ();

   if (!inter)
     fprintf (stdout, "%g Mbps\n", (double) bits/(T - T0));
   
   return 0;
}
