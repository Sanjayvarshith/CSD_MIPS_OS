#include "include/process.h"
#include "include/semihosting.h"
#include "include/serial.h"

// These symbols are defined by our linker script and mark the start and
// end of the memory region dedicated to the user process.
extern uint32_t __app_ram_start__[];
extern uint32_t __app_ram_end__[];
#define APP_MEM_BASE ((uintptr_t)__app_ram_start__)
#define APP_MEM_SIZE ((uintptr_t)__app_ram_end__ - (uintptr_t)__app_ram_start__)

int swap_out(const char *path) {
    process_header_t header;
    header.ram_size = APP_MEM_SIZE;
    header.entry_point = 0; // Not applicable when saving a snapshot
    header.stack_pointer = (uint32_t)__app_ram_end__; // Use default end of region
    
    int fd = sh_open(path, SH_OPEN_W);
    if (fd < 0) {
        print("Swap-out failed: could not open file.\n");
        return -1;
    }

    if (sh_write(fd, &header, sizeof(header)) != 0) {
        sh_close(fd);
        print("Swap-out failed: could not write header.\n");
        return -2;
    }

    if (sh_write(fd, (void*)APP_MEM_BASE, APP_MEM_SIZE) != 0) {
        sh_close(fd);
        print("Swap-out failed: could not write app memory.\n");
        return -3;
    }

    sh_close(fd);
    print("Process state saved successfully.\n");
    return 0;
}

int swap_in(const char *path, uint32_t *entry, uint32_t *sp) {
    process_header_t header;
    
    int fd = sh_open(path, SH_OPEN_R);
    if (fd < 0) {
        print("Swap-in failed: could not open file.\n");
        return -1;
    }

    if (sh_read(fd, &header, sizeof(header)) != 0) {
        sh_close(fd);
        print("Swap-in failed: could not read header.\n");
        return -2;
    }

    if (header.ram_size > APP_MEM_SIZE) {
        sh_close(fd);
        print("Swap-in failed: process image is too large.\n");
        return -3;
    }
    
    if (sh_read(fd, (void*)APP_MEM_BASE, header.ram_size) != 0) {
        sh_close(fd);
        print("Swap-in failed: could not read app memory.\n");
        return -4;
    }
    
    sh_close(fd);
    
    *entry = header.entry_point;
    *sp = header.stack_pointer;
    print("Process loaded successfully.\n");
    return 0;
}

void run_process(uint32_t entry_point, uint32_t stack_pointer) {
    print("\n--- KERNEL: Transferring control to user process ---\n");
    
    // Use inline assembly to set the stack pointer ($sp) to the process's
    // value and then jump and link to the process's entry point.
    asm volatile (
        "move $sp, %0\n\t"
        "jalr %1"
        : // No output registers
        : "r"(stack_pointer), "r"(entry_point)
        : "$sp" // Clobbers the stack pointer
    );
    
    // This part of the function should ideally not be reached unless the
    // process explicitly returns, which our simple one won't.
    print("\n--- KERNEL: Regained control from user process ---\n");
}