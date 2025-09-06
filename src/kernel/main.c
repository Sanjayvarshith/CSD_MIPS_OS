#include "include/serial.h"
#include "include/keyboard.h"
#include "include/shell.h"
#include "include/graphics.h"

void kmain(void) {
    // 1. Initialize drivers
    uart_init();
    keyboard_init();
    graphics_init();

    // 2. Print a welcome message to the serial console
    print("--- KERNEL BOOTED ---\n\n");
    
    // 3. Initialize and run the shell
    shell_init();
    shell_run(); 

    // 4. Halt the CPU (should not be reached)
    while (1) {}
}