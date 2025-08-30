#include "include/keyboard.h"

// --- CORRECT HARDWARE ADDRESSES FOR MIPS MALTA (PS/2) ---
#define KBD_DATA_PORT   ((volatile unsigned char*)0xBFD00060)
#define KBD_STATUS_PORT ((volatile unsigned char*)0xBFD00064)

// Status register bits
#define KBD_STAT_OBF 0x01 // Output buffer full flag

static int shift_active = 0;
static int caps_active = 0;

// Lookup tables for converting scancodes to ASCII
static const char scancode_to_ascii[] = {
    [KEY_A] = 'a', [KEY_B] = 'b', [KEY_C] = 'c', [KEY_D] = 'd', [KEY_E] = 'e',
    [KEY_F] = 'f', [KEY_G] = 'g', [KEY_H] = 'h', [KEY_I] = 'i', [KEY_J] = 'j',
    [KEY_K] = 'k', [KEY_L] = 'l', [KEY_M] = 'm', [KEY_N] = 'n', [KEY_O] = 'o',
    [KEY_P] = 'p', [KEY_Q] = 'q', [KEY_R] = 'r', [KEY_S] = 's', [KEY_T] = 't',
    [KEY_U] = 'u', [KEY_V] = 'v', [KEY_W] = 'w', [KEY_X] = 'x', [KEY_Y] = 'y',
    [KEY_Z] = 'z',
    [KEY_1] = '1', [KEY_2] = '2', [KEY_3] = '3', [KEY_4] = '4', [KEY_5] = '5',
    [KEY_6] = '6', [KEY_7] = '7', [KEY_8] = '8', [KEY_9] = '9', [KEY_0] = '0',
    [KEY_ENTER] = '\n', [KEY_SPACE] = ' ', [KEY_BACKSPACE] = 0x08
};

static const char scancode_to_ascii_shift[] = {
    [KEY_A] = 'A', [KEY_B] = 'B', [KEY_C] = 'C', [KEY_D] = 'D', [KEY_E] = 'E',
    [KEY_F] = 'F', [KEY_G] = 'G', [KEY_H] = 'H', [KEY_I] = 'I', [KEY_J] = 'J',
    [KEY_K] = 'K', [KEY_L] = 'L', [KEY_M] = 'M', [KEY_N] = 'N', [KEY_O] = 'O',
    [KEY_P] = 'P', [KEY_Q] = 'Q', [KEY_R] = 'R', [KEY_S] = 'S', [KEY_T] = 'T',
    [KEY_U] = 'U', [KEY_V] = 'V', [KEY_W] = 'W', [KEY_X] = 'X', [KEY_Y] = 'Y',
    [KEY_Z] = 'Z',
    [KEY_1] = '!', [KEY_2] = '@', [KEY_3] = '#', [KEY_4] = '$', [KEY_5] = '%',
    [KEY_6] = '^', [KEY_7] = '&', [KEY_8] = '*', [KEY_9] = '(', [KEY_0] = ')'
};

void keyboard_init(void) {
    // For a simple polling driver, no initialization is needed.
}

char keyboard_poll(void) {
    if (!(*KBD_STATUS_PORT & KBD_STAT_OBF)) {
        return 0; // No key
    }
    uint8_t scancode = *KBD_DATA_PORT;

    if (scancode & 0x80) { // Handle key releases
        scancode &= 0x7F; // Remove the release bit
        if (scancode == KEY_SHIFT_L || scancode == KEY_SHIFT_R) {
            shift_active = 0;
        }
        return 0;
    }

    if (scancode == KEY_SHIFT_L || scancode == KEY_SHIFT_R) { // Handle key presses
        shift_active = 1;
        return 0;
    }
    if (scancode == KEY_CAPSLOCK) {
        caps_active = !caps_active;
        return 0;
    }

    char ascii = 0;
    if (shift_active) {
        ascii = scancode_to_ascii_shift[scancode];
    } else {
        ascii = scancode_to_ascii[scancode];
    }
    
    if (caps_active && !shift_active && ascii >= 'a' && ascii <= 'z') {
        ascii -= 32; // Convert to uppercase
    }

    return ascii;
}