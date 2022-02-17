#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "curslib.h"
#include "timecurses.h"

// Completely random matrix of data
long random_screen (int nrows, int ncols, int docolor)
{
   int r, c, attrb;

   attron (A_BOLD);
   for (r = 2; r < nrows - 2; ++r)
   {
      move (r, 0);
      for (c = 0; c < ncols; ++c)
      {
         if (docolor)
         {
            attrb = COLOR_PAIR((rand () & 0x000D) + 1);
            attron (attrb);
         }
         addch ((rand () & 0x3F) + 33);
      }
   }
   attroff (A_BOLD);

   // return frame bit count
   if (docolor)
   {
      return 64*(long)nrows*(long)ncols;
   }
   else
   {
      return 8*(long)nrows*(long)ncols;
   }
}
