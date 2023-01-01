#include <stdlib.h>
#include <ncurses.h>
#include <sys/time.h>
#include <math.h>
#include "curslib.h"

// Return random integer between 0 and max, inclusive.
int rand_max(int max)
{
   return rand() % (max + 1);
}

// pass through integer with limits
int limiter(int in, int min, int max)
{
   if (in > max)
      return max;
   if (in < min)
      return min;
   return in;
}

// is number within limits?
int qlimit(int in, int min, int max)
{
   if ((in > max) || (in < min))
      return 0;
   else
      return 1;
}

// draw box centered on screen
void draw_centered_box(int width, int height)
{
   // Get the current terminal size
   int terminal_width, terminal_height;
   getmaxyx(stdscr, terminal_height, terminal_width);

   // Calculate the starting position of the box
   int start_x = (terminal_width - width) / 2;
   int start_y = (terminal_height - height) / 2;

   // Draw the box using the ncurses functions
   for (int y = start_y; y < start_y + height; y++)
   {
      for (int x = start_x; x < start_x + width; x++)
      {
         if (y == start_y || y == start_y + height - 1)
         {
            mvaddch(y, x, '-');
         }
         else if (x == start_x || x == start_x + width - 1)
         {
            mvaddch(y, x, '|');
         }
         else
         {
            mvaddch(y, x, ' ');
         }
      }
   }
}

// draw graph centered on screen
void draw_graph(int width, int height, int x_values[], int y_values[], int num_values)
{
   // Get the current terminal size
   int terminal_width, terminal_height;
   getmaxyx(stdscr, terminal_height, terminal_width);

   // Calculate the starting position of the graph
   int start_x = (terminal_width - width) / 2;
   int start_y = (terminal_height - height) / 2;

   // Find the minimum and maximum values in the X and Y arrays
   int x_min = x_values[0], x_max = x_values[0];
   int y_min = y_values[0], y_max = y_values[0];
   for (int i = 0; i < num_values; i++)
   {
      x_min = fmin(x_min, x_values[i]);
      x_max = fmax(x_max, x_values[i]);
      y_min = fmin(y_min, y_values[i]);
      y_max = fmax(y_max, y_values[i]);
   }

   // Calculate the scaling factor for the X and Y axes
   double x_scale = (double)width / (x_max - x_min);
   double y_scale = (double)height / (y_max - y_min);

   // Draw the X and Y axes
   mvaddch(start_y + height, start_x, '+');
   mvaddch(start_y, start_x, '+');
   for (int x = start_x + 1; x < start_x + width; x++)
   {
      mvaddch(start_y + height, x, '-');
   }
   for (int y = start_y + 1; y < start_y + height; y++)
   {
      mvaddch(y, start_x, '|');
   }

   // Draw the data points
   for (int i = 0; i < num_values; i++)
   {
      int x = start_x + (x_values[i] - x_min) * x_scale;
      int y = start_y + height - (y_values[i] - y_min) * y_scale;
      mvaddch(y, x, '*');
   }
}

// draw single line horizontal bar graph
void drawbar(double frac, int width, int line, int offset)
{
   int j;

   move(line, offset);
   addch('[');
   for (j = 0; j < ceil((double)width * frac); ++j)
   {
      addch(ACS_VLINE);
   }
   for (; j < width; ++j)
   {
      addch(' ');
   }
   addch(']');
}

// draw horizonal line
void drawline(int row, int width)
{
   move(row, 0);
   clrtoeol();
   for (int j = 0; j < width; ++j)
      addch(ACS_HLINE);
}


// init color pairs
void init_colors()
{
   init_pair(1, COLOR_WHITE, COLOR_BLACK);
   init_pair(2, COLOR_BLUE, COLOR_BLACK);
   init_pair(3, COLOR_CYAN, COLOR_BLACK);
   init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
   init_pair(5, COLOR_YELLOW, COLOR_BLACK);
   init_pair(6, COLOR_CYAN, COLOR_BLACK);
   init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
   init_pair(8, COLOR_GREEN, COLOR_BLACK);
   init_pair(9, COLOR_BLACK, COLOR_WHITE);
   init_pair(10, COLOR_BLACK, COLOR_BLUE);
   init_pair(11, COLOR_BLACK, COLOR_CYAN);
   init_pair(12, COLOR_BLACK, COLOR_MAGENTA);
   init_pair(13, COLOR_BLACK, COLOR_YELLOW);
   init_pair(14, COLOR_BLACK, COLOR_CYAN);
   init_pair(15, COLOR_CYAN, COLOR_MAGENTA);
   init_pair(16, COLOR_BLACK, COLOR_GREEN);
}
