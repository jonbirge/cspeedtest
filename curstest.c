#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define BARSIZE 10

int main()
{
   int done = 0;
   int nbar = 0, k = 0;
   time_t now;
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
   move (3, 0);
   addch ('[');
   move (3, BARSIZE + 1);
   addch (']');

   while (!done)
   {
      ++k;

      gettimeofday(&systime, NULL);
      lcltime = localtime (&(systime.tv_sec));
      ms = systime.tv_usec/1000;
      move (0, 0);
      printw ("frame id %d:", k);
      move (2, 0);
      printw ("current time = %.2d:%.2d:%.2d.%.1d",
	      lcltime->tm_hour, lcltime->tm_min, lcltime->tm_sec, ms);
      move (5, 0);
      printw ("seconds in unix epoch = %d", (int) now);
      
      if (++nbar > BARSIZE)
      {
	 for (int k = 0; k < BARSIZE; ++k)
	 {
	    move (3, k + 1);
	    addch (' ');
	 }

	 nbar = 1;
      }	
      move (3, nbar);
      addch ('=');
      
      move (nrows - 1, ncols - 1);
   
      usleep (50000);

      d = getch();
      if (d == 'q')
	 done = 1;
      if (d == 'r')
	 nbar = ncols;
   }

   endwin();
}
