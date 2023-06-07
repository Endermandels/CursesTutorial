#ifndef UI
#define UI

#include <stdbool.h>

#define WIDTH 160
#define HEIGHT 50

#define MAX_INTENSITY 13
#define MIN_INTENSITY 4

typedef struct {
    char char_value;
    int intensity;
} cell;

// extern - defined in matrix.c
extern cell matrix[WIDTH][HEIGHT];

// prototypes
bool init_ui();
void cleanup_ui();
void show_matrix();

#endif
