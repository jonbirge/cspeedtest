/* cspeedtest.c */

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
#define BAR_WIDTH 35
#define MEAS_FRAMES 8
#define POLL_FRAMES 4
#define INT_TIME 7
#define GRAPH_N 256

// Global parameters
static int debug_flag = 0;   // default to no debug info
static int color_flag = 1;   // default to color
static int inter_flag = 0;   // default to non-interactive
static int graph_flag = 1;   // default to graph
static int run_test = 0;     // default no test
static int screen_index = 0; // default to random
static int screen_count;
static screen_display *screen_table;
int Tave = INT_TIME * 1000000; // usec

void print_usage ()
{
   if (!inter_flag)  // normal mode
   {
      printf("Usage: cspeedtest [options]\n\n");
      printf("Options:\n");
      printf("  -h, --help\t\tshow this help\n");
      printf("  -g, --graph\t\thide graph\n");
      printf("  -i, --interactive\tinteractive mode\n");
      printf("  -t T, --int=T\t\tintegration time in seconds\n");
      printf("  -b, --low-bw\t\tlow bandwidth mode\n");
      printf("  -V, --version\t\tdisplay version\n");
   }
   else
   {
      printf("Usage: cspeedtest-int [options]\n\n");
      printf("Options:\n");
      printf("  -h, --help\t\tshow this help\n");
      printf("  -g, --graph\t\thide graph\n");
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
   printf("Copyright 2022-2023, Jonathan R. Birge\n");
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
     inter_flag = 1;
   }
   else
   {
     inter_flag = 0;
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
         {"int", required_argument, 0, 't'},
         {"verbose", no_argument, 0, 'v'},
         {"graph", no_argument, 0, 'g'},
         {"low-bw", no_argument, 0, 'b'},
         {"interactive", no_argument, 0, 'i'},
         {"version", no_argument, 0, 'V'},
         {"help", no_argument, 0, 'h'},
         {"test", no_argument, 0, 'x'},
         {0, 0, 0, 0}
      };

      while ((opt = getopt_long(argc, argv, "t:ghiVbvx", long_options, &option_index)) != -1)
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
            inter_flag = 1;
	         break;
         case 'g':
            graph_flag = 0;
            break;
         case 'b':
            color_flag = 0;
            break;
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

   /*** main loop ***/
   struct timeval systime;
   int k = 0;                    // frame counters
   long bits = 0;                // estimate of bits sent
   long T, T0;                    // usec
   int doreset = 1;              // reset counter
   int done = 0;                 // quit next loop
   int measframes = MEAS_FRAMES; // initial frames between measurements
   int ngraphed = 0;             // number of graphed frames
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
        ngraphed = 0;
        doreset = 0;
      }

      // interface polling
      if (!(k % POLL_FRAMES))
      {
         char d = getch ();
         switch (d)
         {
         case 'q':
            done = 1;
            break;
         case 'c':
            if (inter_flag)
            {
               color_flag = !color_flag;
               doreset = 1;
            }
            break;
         case 'g':
            if (inter_flag)
            {
               graph_flag = !graph_flag;
            }
            break;
         case 'r':
            if (inter_flag)
            {
               screen_index = (screen_index + 1) % screen_count;
               set_current_screen(screen_index);
               doreset = 1;
            }
            break;
         case 'v':
            debug_flag = !debug_flag;
            break;
         }
         
         if (inter_flag)
            static_display(nrows, ncols, inter_flag, color_flag, graph_flag, debug_flag, screen_table[screen_index].name);
         else
            static_display(nrows, ncols, inter_flag, color_flag, graph_flag, debug_flag, "[non-interactive]");
      } // end interface polling

      // write screen
      bits += draw_screen(nrows, ncols, color_flag, graph_flag);

      // debugging
      if (debug_flag)
      {
         move(nrows - 2, 0);
         printw("dT = %f sec | frame: %d | measframes: %d | ngraphed: %d",
                (double)(T - T0) / 1000000.0, k, measframes, ngraphed);
      }

      // update display
      if (!(k % measframes) && !doreset)
      {
         // ensure graph is filled during integration time
         if ((T - T0) > 500000)  // wait until there's a good average...
         {
            ngraphed++;
            long Tleft = Tave - (T - T0);
            int graph_points_left = GRAPH_N - ngraphed;
            double frame_rate = (double) k / (T - T0);
            int frames_left = (int) ceil(Tleft * frame_rate); // estimate of frames left
            if (frames_left > 0 && graph_points_left > 0)
               measframes = (int) floor((double) frames_left / graph_points_left);
         }
         display_mbps(bits, nrows, ncols, screen_index, 0, inter_flag);
         attron(COLOR_PAIR(1));
         drawbar((double)(T - T0) / Tave, BAR_WIDTH, 0, 14);
         attroff(COLOR_PAIR(1));
      }

      // done with integration period
      if ((T - T0) >= Tave)
      {
         if (!inter_flag)
         {
            done = 1;
         }
         else
         {
            display_mbps (bits, nrows, ncols, screen_index, 1, inter_flag);
            drawbar (0, BAR_WIDTH, 0, 14);
            bits = 0;
            T0 = T;
            ngraphed = 0;
            k = 0;
         }
      }

      // loop clean-up
      refresh();
   }

   endwin ();

   // write final result to stdout
   if (!inter_flag)
     fprintf (stdout, "%g Mbps\n", (double) bits/(T - T0));
   
   return 0;
}
