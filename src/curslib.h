int rand_max (int max);

int limiter (int in, int min, int max);

int qlimit (int in, int min, int max);

void init_colors();

void draw_centered_box_border(int width, int height, int use_ext);

void draw_centered_box(int width, int height);

void draw_graph(int width, int height, double x_values[], double y_values[], int num_values, int use_ext);

void drawbar (double frac, int width, int line, int offset, int use_ext);

void drawline (int row, int width, int use_ext);
