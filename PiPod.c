#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/time.h"

#include "LCD.h"

/* ===================== CONFIG ===================== */

#define MAX_SONGS 5
#define SONG_LENGTH_SEC 30
#define PROGRESS_BAR_WIDTH 20

/* ===================== DATA ===================== */

const char* songs[MAX_SONGS*2] = {
    "Daft Punk", "One More Time",
    "Radiohead", "Paranoid Android",
    "Pink Floyd", "Time",
    "Kendrick Lamar", "HUMBLE",
    "Boards of Canada", "Dayvan Cowboy"
};

typedef enum {
    SCREEN_MENU,
    SCREEN_PLAYING
} Screen;

typedef struct {
    Screen screen;
    int selected_song;
    int playing_song;
    int progress_sec;
    bool is_playing;
} PlayerState;

PlayerState state = {
    .screen = SCREEN_MENU,
    .selected_song = 0,
    .playing_song = -1,
    .progress_sec = 0,
    .is_playing = false
};

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

/* ===================== MAIN ===================== */

int main() {   
#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c/lcd_1602_i2c example requires a board with I2C pins
#else
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

    lcd_init();


    static char *message[] =
            {
                    "RP2040 by", "Raspberry Pi",
                    "A brand new", "microcontroller",
                    "Twin core M0", "Full C SDK",
                    "More power in", "your product",
                    "More beans", "than Heinz!"
            };

    while (1) {
        for (uint m = 0; m < sizeof(message) / sizeof(message[0]); m += MAX_LINES) {
            for (int line = 0; line < MAX_LINES; line++) {
                lcd_set_cursor(line, (MAX_CHARS / 2) - strlen(message[m + line]) / 2);
                lcd_string(message[m + line]);
            }
            sleep_ms(2000);
            lcd_clear();
        }
    }

    /*
    stdio_init_all();
    sleep_ms(2000);  // Give terminal time to connect

    absolute_time_t last_tick = get_absolute_time();

    while (true) {
        char input = read_input_nonblocking();

        if (state.screen == SCREEN_MENU) {
            handle_menu_input(input);
            draw_menu();
        } else {
            handle_playing_input(input);
            draw_playing();
        }

        // Progress update every second 
        if (state.screen == SCREEN_PLAYING && state.is_playing) {
            if (absolute_time_diff_us(last_tick, get_absolute_time()) > 1000000) {
                last_tick = get_absolute_time();
                state.progress_sec++;

                if (state.progress_sec >= SONG_LENGTH_SEC) {
                    state.is_playing = false;
                    state.screen = SCREEN_MENU;
                }
            }
        }

        sleep_ms(100);
    }
        */
    #endif
}
