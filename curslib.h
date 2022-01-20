void init_colors();

void drawbar (double frac, int width, int line, int offset);

void drawline (int row, int width);

long write_matrix (int nrows, int ncols, int docolor);

long write_matrix_det (int nrows, int ncols, int docolor);

void display_mbps (long bits, int nrows, int ncols, int docolor, int docomp, int reset);

void static_display (int nrows, int ncols, int docolor, int docomp, int verbose);
