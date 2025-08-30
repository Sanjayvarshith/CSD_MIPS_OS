#include "include/graphics.h"

// We will assume the standard framebuffer address is correct until proven otherwise.
#define FRAMEBUFFER_ADDRESS 0xB4000000

// A pointer to our framebuffer memory (Video RAM)
volatile uint16_t* vram = (volatile uint16_t*)FRAMEBUFFER_ADDRESS;

// This function is now intentionally empty.
// We will not send any commands to the graphics card to avoid crashing.
void graphics_init() {
    return;
}

// Draws a single pixel at a given coordinate
void put_pixel(int x, int y, uint16_t color) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }
    // Calculate the memory location of the pixel and write the color
    vram[y * SCREEN_WIDTH + x] = color;
}

// Draws a filled rectangle using put_pixel
void draw_filled_rectangle(int x, int y, int width, int height, uint16_t color) {
    for (int j = y; j < y + height; j++) {
        for (int i = x; i < x + width; i++) {
            put_pixel(i, j, color);
        }
    }
}