#include "include/serial.h"

// --- Hardware Definitions ---
#define UART_BASE ((volatile unsigned char *)0xbf000900)
#define UART_THR (UART_BASE + 0)
#define UART_IER (UART_BASE + 1)
#define UART_FCR (UART_BASE + 2)
#define UART_LCR (UART_BASE + 3)
#define UART_MCR (UART_BASE + 4)
#define UART_LSR (UART_BASE + 5)
#define UART_LSR_THRE 0x20

// --- Driver Functions ---
void uart_init() {
    *UART_IER = 0x00;
    *UART_LCR = 0x03;
    *UART_FCR = 0x07;
    *UART_MCR = 0x0b;
}

static void putchar(char c) {
    while ((*UART_LSR & UART_LSR_THRE) == 0) {}
    *UART_THR = c;
}

void print(const char *s) {
    while (*s) {
        if (*s == '\n') {
            putchar('\r');
        }
        putchar(*s++);
    }
}