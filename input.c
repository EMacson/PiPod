#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "config.h"

/* ===================== INPUT ===================== */

char read_input_nonblocking() {
    int ch = getchar_timeout_us(0);
    return ch == PICO_ERROR_TIMEOUT ? 0 : (char)ch;
}

void handle_menu_input(char c) {
    if (c == 'w' && state.selected_song > 0)
        state.selected_song--;
    else if (c == 's' && state.selected_song < MAX_SONGS - 1)
        state.selected_song++;
    else if (c == 'd') {
        state.playing_song = state.selected_song;
        state.progress_sec = 0;
        state.is_playing = true;
        state.screen = SCREEN_PLAYING;
    }
}

void handle_playing_input(char c) {
    if (c == 'p')
        state.is_playing = !state.is_playing;
    else if (c == 'a') {
        state.is_playing = false;
        state.screen = SCREEN_MENU;
    }
}