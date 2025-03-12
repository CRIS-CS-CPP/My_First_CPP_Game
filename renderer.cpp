void render_background() {
    unsigned int* pixel = (unsigned int*)render_state.memory;
    for (int y = 0; y < render_state.height; y++) {
        for (int x = 0; x < render_state.width; x++) {
            *pixel++ = 0x000000;
        }
    }
}