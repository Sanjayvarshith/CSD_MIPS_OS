#include "include/semihosting.h"
#include "include/string.h" // For strlen

// This function executes a semihosting call using a special MIPS instruction
// sequence that QEMU understands.
static inline int do_semihosting_call(int command, void *arg) {
    register int cmd_reg asm("a0") = command;
    register void *arg_reg asm("a1") = arg;
    register int result_reg asm("v0");

    asm volatile (
        // This specific sequence is a conventional "breakpoint" for MIPS semihosting
        ".word 0x0005000C\n\t" 
        "nop"
        : "=r"(result_reg)       // Output: the return value from the host
        : "r"(cmd_reg), "r"(arg_reg) // Input: command and argument block
        : "memory"               // Tells the compiler memory may have changed
    );

    return result_reg;
}

int sh_open(const char *path, int mode) {
    uint32_t args[] = {(uint32_t)path, (uint32_t)mode, (uint32_t)strlen(path)};
    return do_semihosting_call(0x01, args); // SYS_OPEN
}

int sh_close(int fd) {
    return do_semihosting_call(0x02, &fd); // SYS_CLOSE
}

int sh_write(int fd, const void *buffer, size_t len) {
    uint32_t args[] = {(uint32_t)fd, (uint32_t)buffer, (uint32_t)len};
    // Returns 0 on success
    return do_semihosting_call(0x05, args); // SYS_WRITE
}

int sh_read(int fd, void *buffer, size_t len) {
    uint32_t args[] = {(uint32_t)fd, (uint32_t)buffer, (uint32_t)len};
    // Returns 0 on success (if all bytes were read)
    return do_semihosting_call(0x06, args); // SYS_READ
}

int sh_flen(int fd) {
    return do_semihosting_call(0x0C, &fd); // SYS_FLEN
}