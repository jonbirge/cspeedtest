#include <stdlib.h>
#include <ncurses.h>
#include <sys/time.h>
#include <math.h>
#include "curslib.h"
#include "timecurses.h"


// Structure of all displays
const int screen_count = 2;
static screen_display* screen_table;

// API
void init_screen_table ()
{
   screen_table = malloc(sizeof(screen_display)*screen_count);
   screen_table[0].name = "random";
   screen_table[0].fun = random_matrix_screen;
   screen_table[1].name = "swirl";
   screen_table[1].fun = swirl_screen;
}

screen_display* get_screen_table ()
{
   return screen_table;
}

int get_screen_count ()
{
   return screen_count;
}

// Completely random matrix of data
long random_matrix_screen (int nrows, int ncols, int docolor)
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
      return 64*nrows*ncols;
   }
   else
   {
      return 8*nrows*ncols;
   }
}

// Swirling dots display
#define np 2048
long swirl_screen (int nrows, int ncols, int docolor)
{
   int row, col, attrb;
   static double rs[np], phis[np];
   static int nrowslast, ncolslast;

   if ((nrows == nrowslast) && (ncols == ncolslast))
   {
      // rotate
      double speed = 0.0001, vorticity = 2.0;
      for (register int k = 0; k < np; k++)
      {
         if (docolor)
            phis[k] += speed/(vorticity*rs[k]/ncols+speed);
         else
            phis[k] += speed/(vorticity*rs[k]/ncols+speed);
      }
   }
   else
   {
      // init
      double uniformrv;
      for (int k = 0; k < np; k++)
      {
         uniformrv = (double) rand() / (double) RAND_MAX;
         rs[k] = uniformrv*ncols/2.0;
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
      return 32*np;
   }
   else
   {
      return 16*np;
   }
}

// Track and display bitrate
void display_mbps (long bits, int nrows, int ncols, int warn, int reset)
{
   static int sec, us, secold, usold;
   struct timeval systime;
   double bps, dt;

   if (reset || secold == 0)  // init
   {
      gettimeofday (&systime, NULL);
      secold = systime.tv_sec;
      usold = systime.tv_usec;
      bps = 0;
   }
   else  // normal ops
   {
      gettimeofday (&systime, NULL);
      sec = systime.tv_sec;
      us = systime.tv_usec;
      dt = (double) (sec - secold) + (double) (us - usold)*1e-6;
      bps = bits/dt;
   }

   attron(COLOR_PAIR(1));
   move(0, 0);
   clrtoeol();
   attron(A_BOLD);
   if (bps == 0)
      printw ("---");
   else
      printw ("%d", (int) round(bps / 1024 / 1024));
   attroff(A_BOLD);
   printw (" Mbps");
   attroff(COLOR_PAIR(1));
   if (warn)
   {
      move(0, ncols - 26);
      attron(COLOR_PAIR(6));
      printw("Bitrate may be unreliable.");
      attroff(COLOR_PAIR(6));
   }
}


void static_display (int nrows, int ncols, int docolor, int verbose)
{
   attron(COLOR_PAIR(1));
   drawline (1, ncols);
   drawline (nrows - 2, ncols);
   move (nrows - 1, 0);
   printw ("Type ");
   attron (A_BOLD);
   addch ('q');
   attroff (A_BOLD);
   printw(" to to quit, ");
   attron (A_BOLD);
   addch ('r');
   attroff (A_BOLD);
   printw (" to cycle screen, ");
   attron (A_BOLD);
   addch ('c');
   attroff (A_BOLD);
   printw(" to toggle ");
   if (docolor)
   {
      attron (COLOR_PAIR(16));
      printw("color");
      attron (COLOR_PAIR(1));
   }
   else
   {
      printw("color");
   }
   addch ('.');
   if (verbose)
   {
      printw(" chars: ");
      printw("%d", nrows*ncols);
      printw(" res: %d x %d", ncols, nrows);
   }
   attroff(COLOR_PAIR(1));
}
