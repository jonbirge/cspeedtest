#include <stdlib.h>
#include <ncurses.h>
#include <sys/time.h>
#include <math.h>
#include "curslib.h"


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

// Is number within limits?
int qlimit (int in, int min, int max)
{
   if ((in > max) || (in < min))
      return 0;
   else
      return 1;
}

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

void init_colors ()
{
   init_pair (1, COLOR_WHITE, COLOR_BLACK);
   init_pair (2, COLOR_WHITE, COLOR_BLACK);
   init_pair (3, COLOR_CYAN, COLOR_BLACK);
   init_pair (4, COLOR_MAGENTA, COLOR_BLACK);
   init_pair (5, COLOR_YELLOW, COLOR_BLACK);
   init_pair (6, COLOR_CYAN, COLOR_BLACK);
   init_pair (7, COLOR_MAGENTA, COLOR_BLACK);
   init_pair (8, COLOR_BLUE, COLOR_BLACK);
   init_pair (9, COLOR_BLACK, COLOR_CYAN);
   init_pair (10, COLOR_BLACK, COLOR_MAGENTA);
   init_pair (11, COLOR_BLACK, COLOR_YELLOW);
   init_pair (12, COLOR_BLACK, COLOR_CYAN);
   init_pair (13, COLOR_BLACK, COLOR_MAGENTA);
   init_pair (14, COLOR_BLACK, COLOR_YELLOW);
   init_pair (15, COLOR_CYAN, COLOR_BLUE);
   init_pair (16, COLOR_BLACK, COLOR_WHITE);
}
