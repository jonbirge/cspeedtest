#include <ncurses.h>
#include <getopt.h>
#include <math.h>
#include "curslib.h"
#include "config.h"

#define N_AVE_COLOR 128
#define N_AVE 128
#define BAR_WIDTH 32

int main (int argc, char **argv)
{
   int done = 0;
   char d;
   WINDOW *wnd;
   int nrows, ncols;
   int docolor, docomp, nave, doreset = 0;
   int opt;
   
   // options and defaults
   docolor = 1;  // default to color
   docomp = 0;  // default to random
   while ((opt = getopt (argc, argv, "bhrv")) != -1)
   {
      switch (opt)
      {
      case 'b':
         docolor = 0;
         break;
      case 'r':
         docomp = 1;
         break;
      case 'h':
         printf("Usage: cspeedtest [options]\n\n");
         printf("Options:\n");
         printf("   -b\tlow bandwidth (B/W)\n");
         printf("   -r\tnon-random pattern\n");
         printf("   -v\tdisplay version\n");
         printf("   -h\tshow this help\n");
         return (0);
      case 'v':
         printf(PACKAGE_STRING);
         printf("\n");
         printf("Copyright (c) 2021 Jonathan R. Birge\n");
         printf("Bug reports to ");
         printf(PACKAGE_BUGREPORT);
         printf("\n");
         return (0);
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
      static_display(nrows, ncols, docolor, docomp);

      // write matrix of characters
      if (docomp)
         write_matrix_comp (nrows, ncols, docolor);
      else
         write_matrix (nrows, ncols, docolor);

      // interface polling
      if (!(k % 8))
      {
         d = getch ();
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
         }
      }

      if (doreset)
      {
        k = 0;
        kold = 0;
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
      if (!(k % nave))
      {
         dk = k - kold;
         display_mbps (dk, nrows, ncols, docolor, doreset);
         drawbar (0, BAR_WIDTH, 0, 14);
         kold = k;
      }

      doreset = 0;
      refresh();
   }

   endwin ();

   return 0;
}
