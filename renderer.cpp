void render_background() {
    unsigned int* pixel = (unsigned int*)render_state.memory;
    for (int y = 0; y < render_state.height; y++) {
        for (int x = 0; x < render_state.width; x++) {
            *pixel++ = 0xFF0000;
        }
    }
}

void clear_screen(unsigned int bgcolor) {
    unsigned int* pixel = (unsigned int*)render_state.memory;
    for (int y = 0; y < render_state.height; y++) {
        for (int x = 0; x < render_state.width; x++) {
            *pixel++ = bgcolor;
        }
    }
}

int clamp(int min, int val, int max) {
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

void draw_rect(int x0, int y0, int x1, int y1, unsigned int color) {
    x0 = clamp(0, x0, render_state.width);
    x1 = clamp(0, x1, render_state.width);
    y0 = clamp(0, y0, render_state.height);
    y1 = clamp(0, y1, render_state.height);

    // for each row starting at y0 until y1
    for (int y = y0; y < y1; y++) {
        /*
        * We use the buffer to represent rows and columns (x * y),
        * but the buffer is represented as one continous block.
        *   For example, in a 3 x 3 grid, we think of it as:
        *       0:0  0:1  0:2
        *       1:0  1:1  1:2
        *       2:0  2:1  2:2
        *   But in memory, its represented like:
        *       0:0, 0:1, 0:2, 1:0, 1:1, 1:2, 2:0, 2:1, 2:2
        *       ^                                  ^
        *   render_state.memory is pointing to 0:0
        *   So, to point to row:col 2:1, it is
        *       0 + 1 + 2 * row_width
        *       ^   ^   ^    
        *       |   |   current row
        *       |   x offset
        *       start of buffer
        */
        unsigned int* pixel = (unsigned int*)render_state.memory + x0 + y*render_state.width;
        for (int x = x0; x < x1; x++) {
            *pixel++ = color;
        }
    }
}