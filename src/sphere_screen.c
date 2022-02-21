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
   const double speed = 0.0025;
   const int nlon = 20;  // number of lon lines
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
      rho = ncols/2 - 2;
      nrowslast = nrows;
      ncolslast = ncols;
   }

   // clear screen
   for (row = 2; row < nrows - 2; row++)
   {
      move (row, 0);
      clrtoeol();
   }

   // write field
   attron(COLOR_PAIR(8));
   int nchars = 0;
   char ch;
   for (double lon = 0; lon < 360; lon += 360.0/nlon)
   {
      double phi0 = (lon + phi);
      double phi0int = (int)ceil(lon + phi) % 360;
      if (docolor)
      {
         if (phi0int < 180)
         {
            attron(COLOR_PAIR((int)round((lon / (360.0/nlon))) % 8 + 9));
            ch = ' ';
         }
         else
         {
            attron(COLOR_PAIR((int)round((lon / (360.0/nlon))) % 8));
            ch = '.';
         }
         nchars++;
      }
      else
      {
         if (phi0int > 180)
         {
            continue;
         }
         else
         {
            ch = '*';
         }
      }
      for (row = 2; row < nrows - 2; row++)
      {
         double lat = minlat + (180.0 - minlat*2.0)*(row - 2)/(nrows - 5);
         double latfrac = (lat - 90)/90;
         double r = rho*sqrt(1 - latfrac*latfrac);
         int x = round(cos(phi0*DEGRAD)*r);
         move (row, x + round(ncols/2));
         addch (ch);
         nchars++;
      }
   }

   // double rowsteps = 8;
   // for (row = 2; row < nrows; row += floor(nrows/rowsteps))
   // {
   //    double lat = minlat + (180.0 - minlat*2.0)*(row - 2)/(nrows - 5);
   //    double latfrac = (lat - 90)/90;
   //    double r = rho*sqrt(1 - latfrac*latfrac);
   //    move (row, round(ncols/2 - r));
   //    for (int k = 0; k < 2*r; k++)
   //    {
   //       addch ('.');
   //    }
   // }
   
   attroff (A_BOLD);

   // return frame bit count
   return 8*nchars;
}
