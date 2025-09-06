#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

// Defines the metadata header for a saved process image.
typedef struct {
    uint32_t ram_size;      // The size of the process's memory snapshot
    uint32_t entry_point;   // The address where the process should start executing
    uint32_t stack_pointer; // The initial value for the stack pointer
    uint32_t reserved;      // For future use
} process_header_t;

// Saves the current content of the application memory region to a file.
int swap_out(const char *path);

// Loads a process from a file into the application memory region.
int swap_in(const char *path, uint32_t *entry, uint32_t *sp);

// Transfers control from the kernel to the loaded process.
void run_process(uint32_t entry_point, uint32_t stack_pointer);

#endif // PROCESS_H