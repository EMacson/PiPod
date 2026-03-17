/*
 * File: example.c
 * Project: dwm_pico_5110_lcd
 * -----
 * This source code is released under GPLv3 license.
 * Check LICENSE file for license agreement,
 * copyrights, 3rd party licenses and changes info can be found in COPYING file.
 * -----
 * Copyright 2023 - 2023 M.Kusiak (timax)
 */

#include "pico/stdlib.h"
#include "lib/dwm_pico_5110_LCD/dwm_pico_5110_LCD.h"

#define SPI_PORT spi1
#define SCE_PIN 13
#define RST_PIN 12
#define DC_PIN 11
#define DIN_PIN 15
#define SCLK_PIN 14

#define SLEEP_DEFAULT 3000

void displayLogo()
{
    // Clear buffer
    LCD_clrBuff();

    // Draw some lines
    LCD_drawLine(27, 9, 57, 0);
    LCD_drawLine(57, 0, 57, 9);
    LCD_drawLine(57, 9, 46, 12);
    LCD_drawLine(46, 12, 46, 41);
    LCD_drawLine(46, 41, 38, 43);
    LCD_drawLine(38, 43, 38, 15);
    LCD_drawLine(38, 15, 27, 19);
    LCD_drawLine(27, 19, 27, 9);
    LCD_drawLine(27, 21, 36, 18);
    LCD_drawLine(36, 18, 36, 44);
    LCD_drawLine(36, 44, 28, 47);
    LCD_drawLine(27, 47, 27, 21);
    LCD_drawLine(48, 14, 57, 12);
    LCD_drawLine(57, 12, 57, 38);
    LCD_drawLine(57, 38, 48, 40);
    LCD_drawLine(48, 40, 48, 14);

    // Refresh screen
    LCD_refreshScr();

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT);

    // Fill figures;
    LCD_fillShape(28, 10, true);
    LCD_fillShape(28, 22, true);
    LCD_fillShape(49, 15, true);

    // Refresh screen
    LCD_refreshScr();

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT);
}

void displayLibraryInfo()
{
    // Clear screen
    LCD_clrScr();

    // Write some text
    LCD_print("Nokia 5110 LCD", 0, 0);
    LCD_print("pico library", 0, 1);
    LCD_print("by Timax (DWM)", 0, 3);
    LCD_print("2023", 0, 4);

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT);
}

void displayText()
{
    // Clear screen
    LCD_clrScr();

    // Print string
    LCD_print("Hello world!", 0, 0);

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT);
}

void displayTextByChar()
{
    char *text = "Hello world!";

    // Clear screen
    LCD_clrScr();

    // Set cursor at position 0, on row 0
    LCD_goXY(0, 0);

    for (int i = 0; i < 12; i++)
    {
        LCD_putChar(*text);
        text++;
        sleep_ms(200);
    }

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT);
}

void invertColors()
{
    static bool inverted = true;
    // Clear screen
    LCD_clrScr();

    // Invert screen color
    LCD_invert(inverted);

    // Display text
    LCD_print("This is inverted screen color!", 0, 0);

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT);

    // Clear screen
    LCD_clrScr();

    // Turn off screen inversion
    LCD_invert(!inverted);

    // Invert text color
    LCD_invertText(inverted);

    // Display text
    LCD_print("This is inverted text color.", 0, 0);

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT);

    // Clear screen
    LCD_clrScr();

    // Invert screen color
    LCD_invert(inverted);

    // Display text
    LCD_print("This is inverted text on inverted screen.", 0, 0);

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT);

    // Turn off screen inversion
    LCD_invert(!inverted);

    // Turn off text inversion
    LCD_invertText(!inverted);
}

void drawFigures()
{
    // Clear buffer
    LCD_clrBuff();

    // Clear screen
    LCD_clrScr();

    // Draw Circle
    LCD_drawCircle(43, 24, 24);

    // Refresh screen
    LCD_refreshScr();

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT);

    // Draw Triangle inside circle
    LCD_drawTriangle(28, 7, 28, 40, 66, 24);

    // Refresh screen
    LCD_refreshScr();

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT);

    // Draw Square around the circle
    LCD_drawRectangle(19, 0, 67, 47);

    // Refresh screen
    LCD_refreshScr();

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT);
}

void fillShapes()
{
    // Clear buffer
    LCD_clrBuff();

    // Clear screen
    LCD_clrScr();

    // Draw Circle
    LCD_drawCircle(43, 24, 24);

    // Refresh screen
    LCD_refreshScr();

    // Wait
    sleep_ms(SLEEP_DEFAULT / 2);

    // Fill shape
    LCD_fillShape(43, 24, true);

    // Refresh screen
    LCD_refreshScr();

    // Wait
    sleep_ms(SLEEP_DEFAULT / 2);

    // Clear buffer
    LCD_clrBuff();

    // Draw Triangle inside circle
    LCD_drawTriangle(28, 7, 28, 40, 66, 24);

    // Refresh screen
    LCD_refreshScr();

    // Wait
    sleep_ms(SLEEP_DEFAULT / 2);

    // Fill shape
    LCD_fillShape(29, 16, true);

    // Refresh screen
    LCD_refreshScr();

    // Wait
    sleep_ms(SLEEP_DEFAULT / 2);

    // Clear buffer
    LCD_clrBuff();

    // Draw Square around the circle
    LCD_drawRectangle(19, 0, 67, 47);

    // Refresh screen
    LCD_refreshScr();

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT / 2);

    // Fill shape
    LCD_fillShape(20, 1, true);

    // Refresh screen
    LCD_refreshScr();

    // Wait
    sleep_ms(SLEEP_DEFAULT / 2);
}

void drawLines()
{
    // Clear buffer
    LCD_clrBuff();

    // Clear screen
    LCD_clrScr();

    // Draw line across the screen
    LCD_drawLine(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

    // Refresh screen
    LCD_refreshScr();

    // Wait
    sleep_ms(SLEEP_DEFAULT / 2);

    // Draw line across the screen
    LCD_drawLine(LCD_WIDTH - 1, 0, 0, LCD_HEIGHT - 1);

    // Refresh screen
    LCD_refreshScr();

    // Wait
    sleep_ms(SLEEP_DEFAULT / 2);

    // Draw line across quarter of the screen
    LCD_drawLine(0, LCD_HEIGHT / 2, LCD_WIDTH / 2, 0);

    // Refresh screen
    LCD_refreshScr();

    // Wait
    sleep_ms(SLEEP_DEFAULT / 2);

    // Draw line across quarter of the screen
    LCD_drawLine(LCD_WIDTH / 2, 0, LCD_WIDTH - 1, LCD_HEIGHT / 2);

    // Refresh screen
    LCD_refreshScr();

    // Wait
    sleep_ms(SLEEP_DEFAULT / 2);

    // Draw line across quarter of the screen
    LCD_drawLine(LCD_WIDTH - 1, LCD_HEIGHT / 2, LCD_WIDTH / 2, LCD_HEIGHT - 1);

    // Refresh screen
    LCD_refreshScr();

    // Wait
    sleep_ms(SLEEP_DEFAULT / 2);

    // Draw line across quarter of the screen
    LCD_drawLine(LCD_WIDTH / 2, LCD_HEIGHT - 1, 0, LCD_HEIGHT / 2);

    // Refresh screen
    LCD_refreshScr();

    // Wait
    sleep_ms(SLEEP_DEFAULT / 2);
}

void drawSecondPixel()
{
    // Clear buffer
    LCD_clrBuff();

    // Clear screen
    LCD_clrScr();

    // Lit pixels
    for (uint16_t i = 0; i < LCD_HEIGHT; i++)
        for (uint16_t j = 0; j < LCD_WIDTH; j++)
            if (!((i + j) % 2))
                LCD_setPixel(j, i, true);

    // Refresh screen
    LCD_refreshScr();

    // Wait 3 seconds
    sleep_ms(SLEEP_DEFAULT);
}

void refreshScreenPart()
{
    // Clear buffer
    LCD_clrBuff();

    // Fill buffer
    LCD_fillShape(0, 0, true);

    // Refresh screen
    LCD_refreshScr();

    // Clear buffer
    LCD_clrBuff(); // Notice that whole buffer is cleared at this point

    // Blink square at the screen centre
    for (uint16_t i = 0; i <= SLEEP_DEFAULT; i += 400)
    {
        LCD_drawRectangle(37, 16, 45, 24);
        LCD_fillShape(38, 20, true);
        LCD_refreshArea(37, 45, 2, 1);
        sleep_ms(200);
        LCD_clrBuff();
        LCD_refreshArea(37, 44, 2, 1);
        sleep_ms(200);
    }
}

int main()
{
    stdio_init_all();

    // Set gpio pins.
    LCD_setSPIInstance(SPI_PORT);
    LCD_setSCE(SCE_PIN);
    LCD_setRST(RST_PIN);
    LCD_setDC(DC_PIN);
    LCD_setDIN(DIN_PIN);
    LCD_setSCLK(SCLK_PIN);

    // Init SPI communication protocol with max allowed speed.
    spi_init(SPI_PORT, LCD_SPI_MAX_SPEED);

    // Init LCD
    LCD_init();

    // Display library info
    displayLogo();
    displayLibraryInfo();

    // Iterate through examples
    while (true)
    {
        displayText();
        displayTextByChar();
        invertColors();
        drawFigures();
        fillShapes();
        drawLines();
        drawSecondPixel();
        refreshScreenPart();
    }
}

/**
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5



int main()
{
    stdio_init_all();

    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART
    
    // Send out a string, with CR/LF conversions
    uart_puts(UART_ID, " Hello, UART!\n");
    
    // For more examples of UART use see https://github.com/raspberrypi/pico-examples/tree/master/uart

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
*/