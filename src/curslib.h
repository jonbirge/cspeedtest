int rand_max (int max);

int limiter (int in, int min, int max);

int qlimit (int in, int min, int max);

void init_colors();

void draw_centered_box_border(int width, int height);

void draw_centered_box(int width, int height);

void draw_graph(int width, int height, int x_values[], int y_values[], int num_values);

void drawbar (double frac, int width, int line, int offset);

void drawline (int row, int width);
