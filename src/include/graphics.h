#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

// Change to a more standard default resolution
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

// 16-bit color definitions
#define COLOR_BLACK   0x0000
#define COLOR_BLUE    0x001F
#define COLOR_GREEN   0x07E0
#define COLOR_RED     0xF800
#define COLOR_WHITE   0xFFFF
#define COLOR_YELLOW  0xFFE0

// Function declarations
void graphics_init();
void put_pixel(int x, int y, uint16_t color);
void draw_filled_rectangle(int x, int y, int width, int height, uint16_t color);

#endif // GRAPHICS_H