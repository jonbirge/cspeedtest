/* timecurses.h */

typedef long (*screen_fun_ptr)(int, int, int);

struct screen_display
{
  char* name;
  screen_fun_ptr fun;
};

typedef struct screen_display screen_display;

void init_screen_table ();

screen_display* get_screen_table ();

int get_screen_count ();

void display_mbps (long bits, int nrows, int ncols, int warn, int reset, int inter);

void static_display (int nrows, int ncols, int inter, int docolor, int dograph, int verbose, char* name);

void set_current_screen (int i);

int get_current_screen ();

int draw_screen (int rows, int cols, int docolor, int dograph);
