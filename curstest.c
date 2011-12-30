#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>

#define N_AVE 1000

void drawbar(double frac, int width, int line, int offset);

void drawline(int row, int width)
{
   move (row, 0);
   clrtoeol ();
   for (int j = 0; j < width; ++j)
      addch (ACS_HLINE);
}

int main()
{
   int done = 0;
   int paused = 0;
   struct timeval systime;
   char d;
   WINDOW *wnd;
   int nrows, ncols;
   
   wnd = initscr ();
   cbreak ();
   noecho ();
   nodelay (wnd, TRUE);
   getmaxyx (wnd, nrows, ncols);
   start_color ();
   init_pair (1, COLOR_GREEN, COLOR_BLACK);
   init_pair (2, COLOR_YELLOW, COLOR_BLACK);
   clear ();
   refresh ();
   
   attron(COLOR_PAIR(2));
   drawline (1, ncols);
   drawline (nrows - 2, ncols);
   move (nrows - 1, 0);
   printw("type q to quit, p to pause...");
   attroff(COLOR_PAIR(2));

   int r, c;
   int sec, us, secold = 0, usold = 0;
   double dt;
   long dk, k = 0, kold = 0;
   gettimeofday (&systime, NULL);
   secold = systime.tv_sec;
   usold = systime.tv_usec;
   while (!done)
   {
      ++k;

      if (k % N_AVE == 0)
      {
	 gettimeofday (&systime, NULL);
	 sec = systime.tv_sec;
	 us = systime.tv_usec;
	 dt = (double) (sec - secold) + (double) (us - usold)*1e-6;
	 secold = sec;
	 usold = us;
	 dk = k - kold;
	 kold = k;

	 attron(COLOR_PAIR(1));
	 move (0, 0);
	 clrtoeol ();
	 printw ("curses fps: ");
	 attron (A_BOLD);
	 printw ("%.1f", (double) dk/ (double) dt);
	 attroff (A_BOLD);
	 attroff(COLOR_PAIR(1));
      }
      
      drawbar((double) (k % N_AVE)/N_AVE, 10, 0, 22);

      if (!paused)
      {
	 for (r = 2; r < nrows - 2; ++r)
	 {
	    for (c = 0; c < ncols; ++c)
	    {
	       move (r, c);
	       insch ((random () & 0x3F) + 33);
	    }
	 }
      }

      if (k % 100 == 0)
      {
	 d = getch ();
	 if (d == 'q')
	    done = 1;
	 if (d == 'p')
	    paused = !paused;
      }

      refresh();
   }

   endwin ();
}

void drawbar(double frac, int width, int line, int offset)
{
   move (line, offset);
   clrtoeol ();
   insch ('[');
   move (line, offset + 1);
   for (int j = 0; j < round ( (double) width*frac); ++j)
   {
      addch (ACS_CKBOARD);
   }
   move (line, offset + width + 1);
   insch (']');
}
