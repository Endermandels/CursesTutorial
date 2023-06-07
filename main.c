/*
How to Program Matrix Style Dripping Text
by Jacob Sorber (https://youtu.be/K8dCh3ZMLN8)
Copied by Elijah Delavar
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include "ui.h"
#include "matrix.h"

#define ITERATIONS 300
#define REFRESH_DELAY 50000L

int main(int argc, char const *argv[])
{
    
    if (!init_ui()) {
        return 1;
    }

    matrix_init();

    for (int ii = 0; ii < ITERATIONS; ii++) {
        matrix_update();
        show_matrix();
        usleep(REFRESH_DELAY);
    }

    cleanup_ui();

    return 0;
}
