#include "config.h"
#include <ncurses.h>
#include <math.h>
#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif
#include "curslib.h"

#define N_AVE_COLOR 1000
#define N_AVE 4000
#define BAR_WIDTH 32


// Global flags
static int debug = 0;  // default to no debug info
static int docolor = 1;  // default to color
static int docomp = 0;  // default to random

void print_usage ()
{
   printf("Usage: cspeedtest [options]\n\n");
   printf("Options:\n");
   printf("   -b\tlow bandwidth (B/W)\n");
   printf("   -r\tnon-random pattern (test compression)\n");
   printf("   -v\tdisplay version\n");
   printf("   -h\tshow this help\n");
   printf("   -d\tprint debug info\n");
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
   int opt;
   const char* option_list = "bhrvd";
   if (HAVE_GETOPT_LONG)
   {
      int option_index = 0;
      struct option long_options[] =
          {
              {"debug", no_argument, 0, 'd'},
              {"low-bandwidth", no_argument, 0, 'b'},
              {"version", no_argument, 0, 'v'},
              {"help", no_argument, 0, 'h'},
              {0, 0, 0, 0}};
      while ((opt = getopt_long(argc, argv, option_list, long_options, &option_index)) != -1)
      {
         switch (opt)
         {
         case 'b':
            docolor = 0;
            break;
         case 'r':
            docomp = 1;
            break;
         case 'd':
            debug = 1;
            break;
         case 'h':
            print_usage();
            return (0);
         case 'v':
            print_version();
            return (0);
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

   // main loop
   long dk, k = -1, kold = -1;  // frame counters
   long bits = 0;  // estimate of bits sent
   int doreset = 1;
   int nave;
   int done = 0;
   while (!done)
   {
      ++k;

      // init
      if (docolor)
         nave = N_AVE_COLOR;
      else
         nave = N_AVE;
      getmaxyx (wnd, nrows, ncols);

      // static display
      static_display(nrows, ncols, docolor, docomp, debug);

      // write matrix of characters
      if (docomp)
         bits += write_matrix_det (nrows, ncols, docolor);
      else
         bits += write_matrix (nrows, ncols, docolor);

      // interface polling
      if (!(k % 8))
      {
         char d = getch ();
         switch (d)
         {
         case 'q':
            done = 1;
            break;
         case 'c':
            docolor = !docolor;
            doreset = 1;
            break;
         case 'r':
            docomp = !docomp;
            doreset = 1;
            break;
         case 'a':
            doreset = 1;
            break;
         case 'v':
            debug = !debug;
            break;
         }
      }

      if (doreset)
      {
        k = 0;
        bits = 0;
      }

      // update display
      if (!(k % (int) ceil(nave/BAR_WIDTH)))
      {
         attron (COLOR_PAIR(1));
         drawbar ((double) (k % nave)/nave, BAR_WIDTH, 0, 14);
         printw ("   frames: %d", k);
         attroff (COLOR_PAIR(1));
      }

      // throughput update
      if (k >= nave || doreset)
      {
         display_mbps (bits, nrows, ncols, docolor, docomp, doreset);
         drawbar (0, BAR_WIDTH, 0, 14);
         k = 0;
         bits = 0;
      }

      doreset = 0;
      refresh();
   }

   endwin ();

   return 0;
}
