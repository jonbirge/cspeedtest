#include "config.h"
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <sys/time.h>
#include <getopt.h>
#include "curslib.h"
#include "timecurses.h"


// Constants
#define BAR_WIDTH 32

// Global defaults
static int debug_flag = 0;  // default to no debug info
static int color_flag = 1;  // default to color
static int screen_index = 0;  // default to random
static int screen_count;
static screen_display* screen_table;
static screen_fun_ptr screen_fun;
int Tave = 5 * 1000000;  // usec

void print_usage ()
{
   printf("Usage: cspeedtest [options]\n\n");
   printf("Options:\n");
   printf("  -t T, --time=T\tintegration time in seconds\n");
   printf("  -b, --low-bandwidth\tlow bandwidth (B/W)\n");
   printf("  -V, --version\t\tdisplay version\n");
   printf("  -h, --help\t\tshow this help\n");
   printf("  -v, --verbose\t\tprint debug info\n");
}

void print_version ()
{
   printf(PACKAGE_STRING);
   printf("\n");
   printf("Copyright 2021, Jonathan R. Birge\n");
   printf("Bug reports to ");
   printf(PACKAGE_BUGREPORT);
   printf("\n");
}

int main (int argc, char **argv)
{
   WINDOW *wnd;
   int nrows, ncols;
   
   // options and defaults
   if (HAVE_GETOPT_LONG)
   {
      int opt;
      int option_index = 0;
      int T;
      struct option long_options[] =
      {
         {"verbose", no_argument, 0, 'v'},
         {"low-bandwidth", no_argument, 0, 'b'},
         {"time", required_argument, 0, 't'},
         {"version", no_argument, 0, 'V'},
         {"help", no_argument, 0, 'h'},
         {0, 0, 0, 0}
      };
      while ((opt = getopt_long(argc, argv, "t:hVbv", long_options, &option_index)) != -1)
      {
         switch (opt)
         {
         case 'h':
            print_usage();
            return (0);
         case 'V':
            print_version();
            return (0);
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
         case 'b':
            color_flag = 0;
            break;
         case 'v':
            debug_flag = 1;
            break;
         }
      }
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

   // main loop
   long k = -1;  // frame counters
   long bits = 0;  // estimate of bits sent
   int T, T0;  // usec
   struct timeval systime;
   int doreset = 1;
   int done = 0;
   while (!done)
   {
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
            color_flag = !color_flag;
            doreset = 1;
            break;
         case 'r':
            screen_index = (screen_index + 1) % screen_count;
            screen_fun = screen_table[screen_index].fun;
            doreset = 1;
            break;
         case 'a':
            doreset = 1;
            break;
         case 'v':
            debug_flag = !debug_flag;
            break;
         }
         static_display(nrows, ncols, color_flag, debug_flag, screen_table[screen_index].name);
         if (debug_flag)
         {
            move (nrows - 2, 0);
            printw("dT = %f sec", (double) (T - T0)/1000000.0);
         }
      }

      // write screen
      bits += screen_fun(nrows, ncols, color_flag);

      // update display
      if (!(k % 16) && !doreset)
      {
         display_mbps (bits, nrows, ncols, screen_index, 0);
         attron (COLOR_PAIR(1));
         drawbar ((double) (T - T0)/Tave, BAR_WIDTH, 0, 14);
         printw ("   frames: %d", k);
         attroff (COLOR_PAIR(1));
      }

      // throughput update
      if (((T - T0) >= Tave) || doreset)
      {
         display_mbps (bits, nrows, ncols, screen_index, 1);
         drawbar (0, BAR_WIDTH, 0, 14);
         bits = 0;
         T0 = T;
         k = -1;
      }

      // loop clean-up
      doreset = 0;
      refresh();
   }

   endwin ();

   return 0;
}
