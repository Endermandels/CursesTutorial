#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "ui.h"

#define NUM_DRIPS 250
#define PROB_DRIP_SPAWN 0.65
#define PROB_DIM 0.55
#define PROB_CHANGE 0.95
#define RANDOM_PRINTABLE_CHARACTER 'X'

typedef struct {
    int x, y;
    bool alive;
    bool bright;
} drip;

cell matrix[WIDTH][HEIGHT];
drip drips[NUM_DRIPS];

/*
Retruns a random number between 0 and 1.
*/
double rand01() {
    return (double)rand()/(double)RAND_MAX;
}

void init_drips() {
    for (int ii = 0; ii < NUM_DRIPS; ii++) {
        drips[ii].alive = false;
    }
}

void matrix_init() {
    // set the matrix all to black
    for (int xx = 0; xx < WIDTH; xx++) {
        for (int yy = 0; yy < HEIGHT; yy++) {
            matrix[xx][yy].char_value = 0;
            matrix[xx][yy].intensity = 0;
        }
    }

    // init drips
    init_drips();
}

void fade_n_change_matrix() {
    for (int xx = 0; xx < WIDTH; xx++) {
        for (int yy = 0; yy < HEIGHT; yy++) {
            // randomly change characters --- even invisible ones
            if (rand01() < PROB_CHANGE || matrix[xx][yy].char_value == 0) {
                matrix[xx][yy].char_value = RANDOM_PRINTABLE_CHARACTER;
            }

            // randomly dim the cells
            if (rand01() < PROB_DIM) {
                if (matrix[xx][yy].intensity > 0) {
                    matrix[xx][yy].intensity--;
                }
            }
        }
    }
}

void try_add_drips() {
    for (int ii = 0; ii < NUM_DRIPS; ii++) {
        if (!drips[ii].alive) {
            drips[ii].alive = true;
            drips[ii].x = rand() % WIDTH;
            drips[ii].y = 0;
            drips[ii].bright = rand() % 2;
            return; // only one drip at a time
        }
    }
}

void update_drips() {
    for (int ii = 0; ii < NUM_DRIPS; ii++) {
        if (drips[ii].alive) {
            if (drips[ii].bright) {
                matrix[drips[ii].x][drips[ii].y].intensity = MAX_INTENSITY;
            } else {
                matrix[drips[ii].x][drips[ii].y].intensity = MIN_INTENSITY;
            }

            // drips die when they leave the screen
            if (++drips[ii].y >= HEIGHT-1) {
                drips[ii].alive = false;
            }
        }
    }
}

void matrix_update() {
    if (rand01() < PROB_DRIP_SPAWN) {
        try_add_drips();
    }
    update_drips();

    fade_n_change_matrix();
}
