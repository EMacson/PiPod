#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "pico/binary_info.h"
#include "drivers/lcd_1602_i2c.h"

/* ===================== CONFIG ===================== */

#define MAX_SONGS 5
#define SONG_LENGTH_SEC 30
#define PROGRESS_BAR_WIDTH 20

/* ===================== DATA ===================== */

const char* songs[MAX_SONGS] = {
    "One More Time",
    "Paranoid Android",
    "Time",
    "HUMBLE",
    "Dayvan Cowboy"
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

void draw_menu() {
    lcd_clear();
    char song_str[16] = ">";
    if (state.selected_song == 0) {  
        lcd_set_cursor(0, 0);      
        lcd_string("=== iPod Menu ===");
        lcd_set_cursor(1, 0);
        lcd_string(">");
        lcd_set_cursor(1, 1);
        lcd_string(songs[state.selected_song]);
        for (int i = 2; i < MAX_LINES; i++) {
            lcd_set_cursor(i, 0); 
            lcd_string(songs[state.selected_song+i]);   
        }
    }
    else {
        lcd_set_cursor(0, 0);
        lcd_string(">");
        lcd_set_cursor(0, 1);
        lcd_string(songs[state.selected_song]);
        for (int i = 1; i < MAX_LINES; i++) {
            lcd_set_cursor(i, 0); 
            lcd_string(songs[state.selected_song+i]);
        }
    }
}

int main() {
#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c/lcd_1602_i2c example requires a board with I2C pins
#else
    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

    lcd_init();
    adc_init();

    adc_gpio_init(26);
    adc_gpio_init(27);

    //state.selected_song = 1;
    while(1) {
        adc_select_input(0);
        uint adc_x_raw = adc_read();
        adc_select_input(1);
        uint adc_y_raw = adc_read();

        const uint bar_width = 40;
        const uint adc_max = (1 << 12) - 1;
        uint bar_x_pos = adc_x_raw * bar_width / adc_max;
        uint bar_y_pos = adc_y_raw * bar_width / adc_max;

        char y;

        if (bar_y_pos < 10) {
            y = 's';
        }
        else if (bar_y_pos > 30) {
            y = 'w';
        }

        if (state.screen == SCREEN_MENU) {
            handle_menu_input(y);
            draw_menu();
            //sleep_ms(2000);
        }  
        
        sleep_ms(100);
    }

    /*
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
        */
#endif
}
