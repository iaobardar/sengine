#include "swindow.h"

typedef struct {
    double time;
    double dt;

    double mouse_x;
    double mouse_y;
    double mouse_dx;
    double mouse_dy;

    double movement[2];
} frame_input_t;

frame_input_t init_inputs(const window_info* wnd);
void tick_inputs(const window_info* wnd, frame_input_t* input);
