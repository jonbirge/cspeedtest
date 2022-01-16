#include <stdlib.h>
#include <ncurses.h>
#include <sys/time.h>
#include <math.h>

#define NP 1024


/*** Library internal functions ***/

// Return random integer between 0 and max, inclusive. Placeholder for more uniform implementation.
int rand_max (int max)
{
   return rand() % (max + 1);
}

// Pass through integer with limits.
int limiter (int in, int min, int max)
{
   if (in > max)
      return max;
   if (in < min)
      return min;
   return in;
}


/*** Library external functions ***/

void drawbar (double frac, int width, int line, int offset)
{
   int j;
   
   move (line, offset);
   addch ('[');
   for (j = 0; j < ceil( (double) width*frac); ++j)
   {
      addch (ACS_CKBOARD);
   }
   for (; j < width; ++j)
   {
      addch (ACS_BULLET);
   }
   addch (']');
}

void drawline (int row, int width)
{
   move (row, 0);
   clrtoeol ();
   for (int j = 0; j < width; ++j)
      addch (ACS_HLINE);
}

// Completely random matrix of data
void write_matrix (int nrows, int ncols, int docolor)
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
            attrb = COLOR_PAIR((rand () & 0x0007) + 1);
            attron (attrb);
         }
         addch ((rand () & 0x3F) + 33);
      }
   }
   attroff (A_BOLD);
}

// Compressible matrix of data
void write_matrix_comp (int nrows, int ncols, int docolor)
{
   double slow;  // factor to slow animation
   register int row, col, attrb;
   static int init;
   static double rs[NP], phis[NP];

   if (init)
   {  // rotate
      for (int k = 0; k < NP; k++)
      {
         phis[k] += 0.0001;
      }
   }
   else
   {  // init
      for (int k = 0; k < NP; k++)
      {
         rs[k] = (double) rand_max ( ceil(ncols/2) );
         phis[k] = rand_max(359) / 3.1456 * 180.0;
      }
      init = 1;
   }

   // clear
   for (row = 2; row < nrows - 2; row++)
   {
      move (row, 0);
      clrtoeol();
   }

   // write field
   attron (A_BOLD);
   for (int k = 0; k < NP; k++)
   {
      col = round(rs[k]*cos(phis[k]) + ncols/2.0);
      row = round(rs[k]*sin(phis[k])/2.0 + nrows/2.0);
      move (limiter(row, 2, nrows - 3), limiter(col, 1, ncols));
      if (docolor)
      {
         attrb = COLOR_PAIR((k % 8) + 1);
         attron(attrb);
      }
      addch ('.');
   }
   attroff (A_BOLD);
}

// Track and display bitrate
void display_mbps (int dk, int nrows, int ncols, int docolor, int reset)
{
   static int sec, us, secold = 0, usold = 0;
   struct timeval systime;
   double dt, fps, bps;

   if (reset || secold == 0)
   {
      // init
      gettimeofday (&systime, NULL);
      secold = systime.tv_sec;
      usold = systime.tv_usec;
      bps = 0;
   }
   else
   {
      // normal ops
      gettimeofday (&systime, NULL);
      sec = systime.tv_sec;
      us = systime.tv_usec;
      dt = (double) (sec - secold) + (double) (us - usold)*1e-6;
      secold = sec;
      
      fps = (double) dk / (double) dt;
      if (docolor)
         bps = (8+64)*fps*nrows*ncols;  // char and attrib calls
      else
         bps = 8*fps*nrows*ncols;

      usold = us;
   }

   attron(COLOR_PAIR(1));
   move(0, 0);
   clrtoeol();
   printw ("Mbps: ");
   attron(A_BOLD);
   if (bps == 0)
      printw ("---");
   else
      printw ("%.1f", bps / 1024 / 1024);
   attroff(A_BOLD);
   attroff(COLOR_PAIR(1));
}

void static_display (int nrows, int ncols, int docolor, int docomp)
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
   printw (" to toggle ");
   if (docomp)
   {
      printw ("random");
   }
   else
   {
      attron (COLOR_PAIR(16));
      printw("random");
      attron (COLOR_PAIR(1));
   }
   printw (", ");
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
   attroff(COLOR_PAIR(1));
}

void init_colors ()
{
   init_pair (1, COLOR_WHITE, COLOR_BLACK);
   init_pair (2, COLOR_WHITE, COLOR_BLACK);
   init_pair (3, COLOR_CYAN, COLOR_BLACK);
   init_pair (4, COLOR_MAGENTA, COLOR_BLACK);
   init_pair (5, COLOR_YELLOW, COLOR_BLACK);
   init_pair (6, COLOR_RED, COLOR_BLACK);
   init_pair (7, COLOR_GREEN, COLOR_BLACK);
   init_pair (8, COLOR_BLUE, COLOR_BLACK);
   init_pair (9, COLOR_BLACK, COLOR_CYAN);
   init_pair (10, COLOR_BLACK, COLOR_MAGENTA);
   init_pair (11, COLOR_BLACK, COLOR_YELLOW);
   init_pair (12, COLOR_BLACK, COLOR_RED);
   init_pair (13, COLOR_BLACK, COLOR_GREEN);
   init_pair (14, COLOR_BLACK, COLOR_BLUE);
   init_pair (15, COLOR_CYAN, COLOR_BLUE);
   init_pair (16, COLOR_BLACK, COLOR_WHITE);
}
