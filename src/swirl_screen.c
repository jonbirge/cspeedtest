#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "curslib.h"
#include "timecurses.h"

// Swirling dots display
#define np 1024
long swirl_screen (int nrows, int ncols, int docolor)
{
   int row, col, attrb;
   static double rs[np], phis[np];
   static int nrowslast, ncolslast;

   if ((nrows == nrowslast) && (ncols == ncolslast))
   {
      // rotate
      double speed = 0.000025, vorticity = 2.0;
      for (register int k = 0; k < np; k++)
      {
         phis[k] += speed/(vorticity*rs[k]/ncols+speed);
      }
   }
   else
   {
      // init
      double uniformrv;
      const double maxr = sqrt((double) (nrows*nrows + ncols*ncols))/2.0;
      for (int k = 0; k < np; k++)
      {
         uniformrv = (double) rand() / (double) RAND_MAX;
         rs[k] = uniformrv*maxr;
         phis[k] = rand_max(359) / 3.1456 * 180.0;
      }
      nrowslast = nrows; ncolslast = ncols;
   }

   // clear
   for (row = 2; row < nrows - 2; row++)
   {
      move (row, 0);
      clrtoeol();
   }

   // write field
   attron (A_BOLD);
   int cycletime;
   cycletime = (int) floor((double) np / 8.0);
   for (register int k = 0; k < np; k++)
   {
      col = (int) round(rs[k]*cos(phis[k]) + ncols/2.0);
      row = (int) round(rs[k]*sin(phis[k])/2.0 + nrows/2.0);
      move (limiter(row, 2, nrows - 3), limiter(col, 1, ncols));
      if (docolor && !(k % cycletime))
      {
         attrb = COLOR_PAIR((int) ceil((double) 8*k / (double) np) + 1);
         attron(attrb);
      }
      if (qlimit (row, 1, nrows - 2))
         addch ('.');  // in view
      else
         addch (' ');  // not in view
   }
   attroff (A_BOLD);

   // return frame bit count
   if (docolor)
   {
      return 24*np;
   }
   else
   {
      return 8*np;
   }
}
