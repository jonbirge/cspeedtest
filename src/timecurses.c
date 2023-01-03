/* timecurses.c */

#include <stdlib.h>
#include <ncurses.h>
#include <sys/time.h>
#include <math.h>
#include "curslib.h"
#include "timecurses.h"

// Define plug-in displays
#define SCREENDEF(name) long name (int nrows, int ncols, int docolor)
SCREENDEF(random_screen);
SCREENDEF(swirl_screen);
SCREENDEF(sphere_screen);
const int screen_count = 3;
static screen_display* screen_table;
static int current_screen = 0;

// Global variables (maybe these should go inside a function)
#define ng_max 128
static const int ng = ng_max;
static double mbps[ng_max];
static double ts[ng_max];

// API plumbing for eventual external plug-ins
void init_screen_table ()
{
   // Allocate memory for screen table
   screen_table = malloc(sizeof(screen_display)*screen_count);
   screen_table[0].name = "random";
   screen_table[0].fun = random_screen;
   screen_table[1].name = "sphere";
   screen_table[1].fun = sphere_screen;
   screen_table[2].name = "swirl";
   screen_table[2].fun = swirl_screen;

   // initialize ts to sequence from 1 to ng
   for (int i = 0; i < ng; i++)
      ts[i] = (double) i + 1.0;
}

// Return table of screen displays
screen_display* get_screen_table ()
{
   return screen_table;
}

// Return number of screens available
int get_screen_count ()
{
   return screen_count;
}

// Return current screen
int get_current_screen ()
{
   return current_screen;
}

// Draw current scree   n
int draw_screen (int rows, int cols, int docolor)
{
   int rawbits, totalbits;

   rawbits = screen_table[current_screen].fun(rows, cols, docolor);
   draw_centered_box (cols/2, rows/2);
   totalbits = 3 * rawbits / 4;
   draw_graph ((int) round(cols/2.0), (int) round(rows/2.0), ts, mbps, ng);

   return totalbits;
}

// Set current screen
void set_current_screen (int i)
{
   current_screen = i;
}

// Track and display bitrate. Run after screen display is done.
void display_mbps (long bits, int nrows, int ncols, int warn, int reset, int inter)
{
   static int sec, us, secinit, usinit;
   static int kt = 0;  // index of point to replace
   struct timeval systime;
   double bps, dt;

   if (!(reset || secinit == 0))  // normal ops
   {
      gettimeofday (&systime, NULL);
      sec = systime.tv_sec;
      us = systime.tv_usec;
      dt = (double) (sec - secinit) + (double) (us - usinit)*1e-6;
      bps = bits/dt;

      // add measurement to mbps array
      mbps[kt++] = bps/1024/1024;
      if (kt >= ng)
         kt = 0;
   }
   else  // init
   {
      gettimeofday (&systime, NULL);
      secinit = systime.tv_sec;
      usinit = systime.tv_usec;
      bps = 0;
      kt = 0;
      // initialize mbps to 0
      for (int i = 0; i < ng_max; i++)
         mbps[i] = 0;
   }

   // text display
   attron(COLOR_PAIR(1));
   move(0, 0);
   clrtoeol();
   attron(A_BOLD);
   if (bps == 0)
      printw ("---");
   else
      printw ("%d", (int) round(bps / 1024 / 1024));
   attroff(A_BOLD);
   printw (" Mbps");
   attroff(COLOR_PAIR(1));
   if (warn)
   {
      move(0, ncols - 23);
      attron(COLOR_PAIR(6));
      printw("Mbps may be unreliable");
      attroff(COLOR_PAIR(6));
   }
}

// Menu items
void static_display (int nrows, int ncols, int inter, int docolor, int verbose, char* name)
{
   attron(COLOR_PAIR(1));
   drawline (1, ncols);
   drawline (nrows - 2, ncols);
   move (nrows - 1, 0);
   printw ("Type ");
   attron (A_BOLD);
   addch ('q');
   attroff (A_BOLD);
   printw(" to to quit");
   if (inter)
   {
      attron (A_BOLD);
      printw (", r");
      attroff (A_BOLD);
      printw (" to cycle display, ");
      attron (A_BOLD);
      addch ('c');
      attroff (A_BOLD);
      printw (" to toggle ");
      if (docolor)
      {
         attron (COLOR_PAIR(16));
         printw ("color");
         attron (COLOR_PAIR(1));
      }
      else
      {
         printw ("color");
      }
      printw (". Display: ");
      attron (A_BOLD);
      printw ("%s", name);
      attroff (A_BOLD);
   }
   if (verbose)
   {
      printw (" | chars: ");
      printw ("%d", nrows*ncols);
      printw (" res: %d x %d", ncols, nrows);
   }
   attroff (COLOR_PAIR(1));
   clrtoeol ();
}
