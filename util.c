#include "config.h"

/* ===================== UTIL ===================== */

void clear_screen() {
    printf("\033[2J\033[H");  // ANSI clear + home
}

void draw_progress_bar(int progress, int total) {
    int filled = (progress * PROGRESS_BAR_WIDTH) / total;
    printf("[");
    for (int i = 0; i < PROGRESS_BAR_WIDTH; i++) {
        printf(i < filled ? "#" : "-");
    }
    printf("] %02d/%02d sec\n", progress, total);
}