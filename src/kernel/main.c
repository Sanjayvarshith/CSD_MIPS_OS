#include "include/serial.h"   // Our existing serial driver
#include "include/graphics.h" // Our new graphics driver

void kmain(void) {
    // 1. Initialize the serial console for debug messages
    uart_init();
    print("--- KERNEL BOOTED ---\n");
    print("Initializing graphics mode...\n");

    // 2. Initialize the graphics driver
    graphics_init();
    
    // 3. Draw to the screen
    print("Drawing to framebuffer...\n");

    // Clear the screen to blue
    draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BLUE);

    // Draw a white rectangle in the middle
    draw_filled_rectangle(312, 284, 400, 200, COLOR_WHITE);
    
    print("Graphics test complete.\n");

    // 4. Halt the CPU
    while (1) {}
}