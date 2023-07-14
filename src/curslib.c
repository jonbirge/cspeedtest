/* curslib.c */

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

// draw box centered on screen, with no background and white border
void draw_centered_box_border(int width, int height, int use_ext)
{
   // Set to color pair 1
   attron(COLOR_PAIR(1));

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
            if (use_ext)
               mvaddch(y, x, ACS_VLINE);
            else
               mvaddch(y, x, '|');
         }
      }
   }

   // Reset to color pair 0
   attroff(COLOR_PAIR(1));
}

// draw box centered on screen, with black background
void draw_centered_box(int width, int height)
{
   // Set to color pair 1
   attron(COLOR_PAIR(1));

   // Get the current terminal size
   int terminal_width, terminal_height;
   getmaxyx(stdscr, terminal_height, terminal_width);

   // Calculate the starting position of the box
   int start_x = (terminal_width - width) / 2;
   int start_y = (terminal_height - height) / 2;

   // Draw the box using the ncurses functions
   for (int y = start_y; y < start_y + height; y++)
   {
      for (int x = start_x; x < start_x + width + 1; x++)
      {
         mvaddch(y, x, ' ');
      }
   }

   // Reset to color pair 0
   attroff(COLOR_PAIR(1));
}

// draw graph centered on screen
void draw_graph(int width, int height, double x_values[], double y_values[], int num_values, int use_ext)
{
   // Draw a box to contain the graph
   draw_centered_box (width, height);

   // Get the current terminal size
   int terminal_width, terminal_height;
   getmaxyx(stdscr, terminal_height, terminal_width);

   // Calculate the starting position of the graph
   int start_x = (terminal_width - width) / 2;
   int start_y = (terminal_height - height) / 2;

   // Find the minimum and maximum values in the X and Y arrays
   double x_min = x_values[0], x_max = x_values[0];
   double y_max = y_values[0];
   for (int i = 0; i < num_values; i++)
   {
      x_min = fmin(x_min, x_values[i]);
      x_max = fmax(x_max, x_values[i]);
      y_max = fmax(y_max, y_values[i]);
   }

   // Assume the minimum Y value is 0
   double y_min = 0;

   // Inflate y_max by 10% to make the graph look nicer
   y_max = y_max * 1.1;

   // Calculate the scaling factor for the X and Y axes
   double x_scale = (double) (width - 2) / (double) (x_max - x_min - 1);
   double y_scale = (double) height / (double) (y_max - y_min - 1);

   // Label Y axis limits
   mvprintw(start_y + 1, start_x + 1, "%d Mbps", (int) ceil(y_max));

   // switch to new color pair
   int colpair = 3;
   attron(COLOR_PAIR(colpair));
   // draw the data points
   for (int i = 0; i < num_values; i++)
   {
      if (y_values[i] != 0)
      {
         int x = floor(1 + start_x + (x_values[i] - x_min) * x_scale);
         int y = round(start_y + height - (y_values[i] - y_min) * y_scale);
         mvaddch(y, x, '.');
      }
   }
   // switch back to old color pair
   attroff(COLOR_PAIR(colpair));

   // draw outline
   draw_centered_box_border (width, height, use_ext);
}

// draw single line horizontal bar graph
void drawbar(double frac, int width, int line, int offset, int use_ext)
{
   int j;

   move(line, offset);
   addch('[');
   for (j = 0; j < ceil((double)width * frac); ++j)
   {
      if (use_ext)
         addch(ACS_CKBOARD);
      else
         addch('|');
   }
   for (; j < width; ++j)
   {
      addch(' ');
   }
   addch(']');
}

// draw horizonal line
void drawline(int row, int width, int use_ext)
{
   move(row, 0);
   clrtoeol();
   for (int j = 0; j < width; ++j)
      if (use_ext)
         addch(ACS_HLINE);
      else
         addch('-');
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
