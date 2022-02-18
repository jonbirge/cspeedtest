#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "curslib.h"

#define DEGRAD 0.01747555556

long sphere_screen (int nrows, int ncols, int docolor)
{
   int row;
   static double rho, phi;
   static int nrowslast, ncolslast;
   const double speed = 0.005;
   const int nlon = 15;  // number of lon lines
   const double minlat = 10;  // deg of min lat

   if ((nrows == nrowslast) && (ncols == ncolslast))
   {
      // rotate
      phi += speed;
   }
   else
   {
      // init
      phi = 0;
      rho = ncols/2;
      nrowslast = nrows;
      ncolslast = ncols;
   }

   // clear
   for (row = 2; row < nrows - 2; row++)
   {
      move (row, 0);
      clrtoeol();
   }

   // write field
   int nchars = 0;

   attron (A_BOLD);
   for (double lon = 0; lon < 360; lon += 360.0/nlon)
   {
      for (row = 2; row < nrows - 2; row++)
      {
         double lat = minlat + (180.0 - minlat*2.0)*(row - 2)/(nrows - 5);
         double latfrac = (lat - 90)/90;
         double phi0 = lon + phi;
         double r = rho*sqrt(1 - latfrac*latfrac);
         int x = round(cos(phi0*DEGRAD)*r);
         int y = round(sin(phi0*DEGRAD)*r);
         if (y > 0)
         {
            move (row, x + round(ncols/2));
            if (docolor)
            {
               attron(COLOR_PAIR(8));
            }
            addch ('.');
            nchars++;
         }
      }
   }
   attroff (A_BOLD);

   // return frame bit count
   if (docolor)
   {
      return 8*nchars;
   }
   else
   {
      return 16*nchars;
   }
}
