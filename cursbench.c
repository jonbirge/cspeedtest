#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
#include <getopt.h>
#include "curslib.h"

#define N_AVE_COLOR 64
#define N_AVE 256

int main (int argc, char **argv)
{
   int done = 0;
   char d;
   WINDOW *wnd;
   int nrows, ncols;
   int docolor, nave;
   int opt;
   
   // options and defaults
   docolor = 0;
   nave = N_AVE;
   while ((opt = getopt (argc, argv, "ch")) != -1)
   {
      switch (opt)
      {
      case 'c':
         docolor = 1;
         nave = N_AVE_COLOR;
         break;
      case 'h':
         printf("Usage: curses-benchmark [options]\n");
         printf("Options:\n");
         printf("-c   use color\n");
         printf("-h   show this help\n");
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
      getmaxyx (wnd, nrows, ncols);

      // static display
      static_display("Type q to quit, c to toggle color.", nrows, ncols);

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
            if (docolor)
               nave = N_AVE_COLOR;
            else
               nave = N_AVE;
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
