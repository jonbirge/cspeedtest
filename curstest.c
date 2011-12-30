#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define BARSIZE 10

void drawbar(double frac, int width, int line, int offset);

int main()
{
   int done = 0;
   int paused = 0;
   int k = 0;
   struct tm *lcltime;
   struct timeval systime;
   int ms;
   char d;
   WINDOW *wnd;
   int nrows, ncols;
   
   wnd = initscr ();
   cbreak ();
   noecho ();
   nodelay (wnd, TRUE);
   getmaxyx (wnd, nrows, ncols);
   start_color ();
   init_pair (1, COLOR_RED, COLOR_BLACK);
   clear ();
   refresh ();
   
   move (nrows - 1, 0);
   printw("type q to quit, p to pause timer...");

   while (!done)
   {
      gettimeofday (&systime, NULL);
      lcltime = localtime (&systime.tv_sec);
      ms = systime.tv_usec/1000;
      move (0, 0);
      printw ("frame: ");
      attron (A_BOLD);
      printw ("%d", ++k);
      attroff (A_BOLD);

      if (!paused)
      {
	 move (2, 0);
	 printw ("current time: ");
	 attron (A_BOLD);
	 attron (COLOR_PAIR(1));
	 printw ("%.2d:%.2d:%.2d.%0.3d",
		lcltime->tm_hour, lcltime->tm_min, lcltime->tm_sec, ms);
	 attroff (A_BOLD);
	 attroff (COLOR_PAIR(1));
	 
	 drawbar ( 1.0 - (double) ms/1000.0, BARSIZE, 2, 28);
      }

      move (nrows - 1, ncols - 1);
      usleep (50000);

      d = getch ();
      if (d == 'q')
	 done = 1;
      if (d == 'p')
	 paused = !paused;

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
