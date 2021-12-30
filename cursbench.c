#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define N_AVE_COLOR 64
#define N_AVE 256

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
               attrb = random () & 0x0F00;
               attron (attrb);
            }
            addch ((random () & 0x3F) + 33);
            if (docolor)
               attroff (attrb);
         }
      }  
}

void static_display(char* str, int nrows, int ncols)
{
   attron(COLOR_PAIR(2));
   drawline (1, ncols);
   drawline (nrows - 2, ncols);
   move (nrows - 1, 0);
   printw(str);
   attroff(COLOR_PAIR(2));
}

void init_colors()
{
   init_pair (1, COLOR_GREEN, COLOR_BLACK);
   init_pair (2, COLOR_YELLOW, COLOR_BLACK);
   init_pair (3, COLOR_RED, COLOR_BLACK);
   init_pair (4, COLOR_CYAN, COLOR_BLACK);
   init_pair (5, COLOR_MAGENTA, COLOR_BLACK);
   init_pair (6, COLOR_BLUE, COLOR_BLACK);
   init_pair (7, COLOR_WHITE, COLOR_BLACK);
   init_pair (8, COLOR_BLACK, COLOR_GREEN);
   init_pair (9, COLOR_BLACK, COLOR_CYAN);
   init_pair (10, COLOR_BLACK, COLOR_RED);
   init_pair (11, COLOR_BLACK, COLOR_MAGENTA);
   init_pair (12, COLOR_BLACK, COLOR_BLUE);
   init_pair (13, COLOR_BLACK, COLOR_WHITE);
   init_pair (14, COLOR_BLACK, COLOR_YELLOW);
}

int main (int argc, char **argv)
{
   int done = 0;
   struct timeval systime;
   char d;
   WINDOW *wnd;
   int nrows, ncols;
   int docolor, nave;
   int opt;
   double fps, bps;
   
   // options and defaults
   docolor = 0;
   nave = N_AVE;
   while ((opt = getopt (argc, argv, "bch")) != -1)
   {
      switch (opt)
      {
      case 'c':
         docolor = 1;
         nave = N_AVE_COLOR;
         break;
      case 'h':
         printf("Usage: curses-benchmark [options]\n");
         printf("Options:\n");
         printf("-c   use color\n");
         printf("-h   show this help\n");
         return (0);
      }
   }  
   
   // init ncurses
   wnd = initscr ();
   nodelay (wnd, TRUE);
   cbreak ();
   noecho ();
   start_color ();
   init_colors ();
   getmaxyx (wnd, nrows, ncols);
   clear ();
   refresh ();

   // static displays
   static_display("type q to quit, c to toggle color...", nrows, ncols);

   // main loop
   int sec, us, secold, usold;
   double dt;
   long dk, k = -1, kold = -1;
   gettimeofday (&systime, NULL);
   secold = systime.tv_sec;
   usold = systime.tv_usec;
   while (!done)
   {
      ++k;

      // write matrix of characters
      write_matrix (nrows, ncols, docolor);

      // gui polling and update
      if (!(k % (nave/32)))
      {
	      d = getch ();
	      switch (d)
	      {
            case 'q':
               done = 1;
               break;
            case 'c':
               docolor = !docolor;
               if (docolor)
                  nave = N_AVE_COLOR;
               else
                  nave = N_AVE;
	      }

         drawbar ((double) (k % nave)/nave, 10, 0, 14);
         printw ("   frames: %d", k);
      }

      // fps and throughput update
      if (!(k % nave))
      {
         gettimeofday (&systime, NULL);
         sec = systime.tv_sec;
         us = systime.tv_usec;
         dt = (double) (sec - secold) + (double) (us - usold)*1e-6;
         secold = sec;
         dk = k - kold;
         
         fps = (double) dk / (double) dt;
         if (docolor)
            bps = 64*fps*nrows*ncols;
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
         kold = k;

	      drawbar (0, 10, 0, 14);
      }
      
      refresh();
   }

   endwin ();

   return 0;
}
