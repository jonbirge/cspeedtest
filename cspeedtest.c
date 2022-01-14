#include <ncurses.h>
#include <getopt.h>
#include "curslib.h"

#define N_AVE_COLOR 128
#define N_AVE 1024

int main (int argc, char **argv)
{
   int done = 0;
   char d;
   WINDOW *wnd;
   int nrows, ncols;
   int docolor, nave;
   int opt;
   
   // options and defaults
   docolor = 1;  // default to color
   while ((opt = getopt (argc, argv, "bhv")) != -1)
   {
      switch (opt)
      {
      case 'b':
         docolor = 0;
         break;
      case 'h':
         printf("Usage: cspeedtest [options]\n\n");
         printf("Options:\n");
         printf("   -b\tlow bandwidth (B/W)\n");
         printf("   -v\tdisplay version\n");
         printf("   -h\tshow this help\n");
         return (0);
      case 'v':
         printf("cspeedtest ");
         printf(VERSION);
         printf("\n");
         printf("Copyright (c) 2021 Jonathan R. Birge\n");
         return (0);
      }
   }  
   
   // init ncurses
   wnd = initscr ();
   nodelay (wnd, TRUE);
   cbreak ();
   noecho ();
   start_color ();
   init_colors ();
   clear ();
   refresh ();

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
      static_display(nrows, ncols, docolor);

      // write matrix of characters
      write_matrix (nrows, ncols, docolor);

      // gui polling and update
      if (!(k % (nave/32)))
      {
         d = getch ();
         switch (d)
         {
         case 'q':
            done = 1;
            break;
         case 'c':
            docolor = !docolor;
         }

         attron (COLOR_PAIR(1));
         drawbar ((double) (k % nave)/nave, 10, 0, 14);
         printw ("   frames: %d", k);
         attroff (COLOR_PAIR(1));
      }

      // fps and throughput update
      if (!(k % nave))
      {
         dk = k - kold;
         display_mbps (dk, nrows, ncols, docolor);
         kold = k;
         drawbar (0, 10, 0, 14);
      }
      
      refresh();
   }

   endwin ();

   return 0;
}
