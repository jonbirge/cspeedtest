#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

void drawbar(double frac, int width, int line, int offset)
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

void drawline(int row, int width)
{
   move (row, 0);
   clrtoeol ();
   for (int j = 0; j < width; ++j)
      addch (ACS_HLINE);
}

void write_matrix(int nrows, int ncols, int docolor)
{
   int r, c, attrb;

   for (r = 2; r < nrows - 2; ++r)
      {
         move (r, 0);
         for (c = 0; c < ncols; ++c)
         {
            if (docolor)
            {
               attrb = COLOR_PAIR((rand () & (int)7) + 1);
               attron (attrb);
            }
            addch ((rand () & 0x3F) + 33);
         }
      }
}

void display_mbps(int dk, int nrows, int ncols, int docolor)
{
   static int sec, us, secold = 0, usold = 0;
   struct timeval systime;
   double dt, fps, bps;

   if (secold == 0)
   {
      // init
      gettimeofday (&systime, NULL);
      secold = systime.tv_sec;
      usold = systime.tv_usec;
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
         bps = (8+64+64)*fps*nrows*ncols;  // char and two attrib calls
      else
         bps = 8*fps*nrows*ncols;

      attron (COLOR_PAIR(1));
      move (0, 0);
      clrtoeol ();
      printw ("Mbps: ");
      attron (A_BOLD);
      printw ("%.1f", bps/1024/1024);
      attroff (A_BOLD);
      attroff (COLOR_PAIR(1));

      usold = us;
   }
}

void static_display(char* str, int nrows, int ncols)
{
   attron(COLOR_PAIR(1));
   drawline (1, ncols);
   drawline (nrows - 2, ncols);
   move (nrows - 1, 0);
   printw(str);
   attroff(COLOR_PAIR(1));
}

void init_colors()
{
   init_pair (1, COLOR_WHITE, COLOR_BLACK);
   init_pair (2, COLOR_GREEN, COLOR_BLACK);
   init_pair (3, COLOR_YELLOW, COLOR_BLACK);
   init_pair (4, COLOR_RED, COLOR_BLACK);
   init_pair (5, COLOR_CYAN, COLOR_BLACK);
   init_pair (6, COLOR_MAGENTA, COLOR_BLACK);
   init_pair (7, COLOR_BLUE, COLOR_BLACK);
   init_pair (8, COLOR_BLACK, COLOR_GREEN);
}
