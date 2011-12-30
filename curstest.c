#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define BARSIZE 10

void drawbar(double frac, int width, int line);

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
   clear ();
   refresh ();
   
   move (nrows - 1, 0);
   printw("awaiting command...");

   while (!done)
   {
      gettimeofday(&systime, NULL);
      lcltime = localtime (&(systime.tv_sec));
      ms = systime.tv_usec/1000;
      move (0, 0);
      printw ("frame %d:", ++k);
      move (2, 0);
      printw ("current time = %.2d:%.2d:%.2d.%0.3d",
	      lcltime->tm_hour, lcltime->tm_min, lcltime->tm_sec, ms);
      
      drawbar((double) ms/1000.0, BARSIZE, 3);
      
      move (nrows - 1, ncols - 1);
      usleep (50000);

      d = getch();
      if (d == 'q')
	 done = 1;
      if (d == 'p')
	 paused = !paused;
   }

   endwin();
}

void drawbar(double frac, int width, int line)
{
   move (line, 0);
   clrtoeol (); // is this slow?
   insch ('[');
   move (line, 1);
   for (int j = 0; j < round((double) width*frac); ++j)
   {
      addch ('=');
   }
   move (line, width + 1);
   insch (']');
}
   
