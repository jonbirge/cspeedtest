struct screen_display
{
  char* name;
  long (*fun)(int, int, int);
};

typedef struct screen_display screen_display;

void init_screen_table ();

screen_display* get_screen_table ();

int get_screen_count ();

long sphere_screen (int nrows, int ncols, int docolor);

void display_mbps (long bits, int nrows, int ncols, int warn, int reset);

void static_display (int nrows, int ncols, int docolor, int verbose);

long random_matrix_screen (int nrows, int ncols, int docolor);

long swirl_screen (int nrows, int ncols, int docolor);
