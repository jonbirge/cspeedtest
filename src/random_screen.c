#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "curslib.h"

// Completely random matrix of data
long random_screen (int nrows, int ncols)
{
   int r, c, attrb;

   attron (A_BOLD);
   for (r = 2; r < nrows - 2; ++r)
   {
      move (r, 0);
      for (c = 0; c < ncols; ++c)
      {
         attrb = COLOR_PAIR((rand () & 0x000D) + 1);
         attron (attrb);
         addch ((rand () & 0x3F) + 33);
      }
   }
   attroff (A_BOLD);

   // return frame bit count
   return 64*(long)nrows*(long)ncols;
}
