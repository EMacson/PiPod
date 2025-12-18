#include "config.h"

/* ===================== UI ===================== */

void draw_menu() {
    clear_screen();
    printf("=== iPod Menu ===\n\n");
    for (int i = 0; i < MAX_SONGS; i++) {
        if (i == state.selected_song)
            printf(" > %s\n", songs[i]);
        else
            printf("   %s\n", songs[i]);
    }
    printf("\n(w/s = move, d = select)\n");
}

void draw_playing() {
    clear_screen();
    printf("=== Now Playing ===\n\n");
    printf("%s\n\n", songs[state.playing_song]);
    draw_progress_bar(state.progress_sec, SONG_LENGTH_SEC);
    printf("\n(p = pause, a = back)\n");
}