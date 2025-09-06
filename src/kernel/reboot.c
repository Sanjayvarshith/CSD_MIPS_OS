#include "include/reboot.h"

// The MIPS Malta board's reset register address for QEMU
#define MALTA_RESET_REG ((volatile unsigned char*)0xBFD00064)

void reboot(void) {
    // Writing any value to this register on the Malta board triggers a reset.
    // We use the keyboard controller's status port address which also acts as reset.
    *MALTA_RESET_REG = 0; 
}