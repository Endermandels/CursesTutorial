#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <curses.h>
#include "ui.h"

WINDOW *uiwindow = NULL;

int color_map[MAX_INTENSITY+1] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 3, 6};

void set_colors();

bool init_ui() {

    // init curses
    uiwindow = initscr();
    if (!uiwindow) {
        return false;
    }

    start_color();
    if (!has_colors() || !can_change_color() || COLOR_PAIRS < 6) {
        puts("Warning!  Your terminal can't handle this program.");
        return false;
    }

    set_colors();

    return true;
}


void cleanup_ui() {
    delwin(uiwindow);
    endwin();
    refresh();
}

void show_matrix() {
    for (int xx = 0; xx < WIDTH; xx++) {
        for (int yy = 0; yy < HEIGHT; yy++) {
            int intensity = matrix[xx][yy].intensity;
            color_set(color_map[intensity], NULL);
            mvaddch(yy, xx, matrix[xx][yy].char_value); // Draw character to x and y position
        }
    }
    refresh();
}

void set_colors() {
    for (int ii = 0; ii < 8; ii++) {
        init_pair(ii+1, ii, COLOR_BLACK);
    }

    // set shades of green
    for (int ii = 0; ii < 5; ii++) {
        init_color(ii, 0, ii*200, 0); // something, R, G, B
    }

    init_color(6, 800, 1000, 800);

}