#ifndef SEMIHOSTING_H
#define SEMIHOSTING_H

#include <stddef.h> // For size_t
#include <stdint.h>

// Semihosting file open modes
#define SH_OPEN_R   0 // Read-only
#define SH_OPEN_W   4 // Write-only, create if not exists
#define SH_OPEN_A   8 // Append, create if not exists

// Function prototypes for file operations
int sh_open(const char *path, int mode);
int sh_close(int fd);
int sh_write(int fd, const void *buffer, size_t len);
int sh_read(int fd, void *buffer, size_t len);
int sh_flen(int fd);

#endif // SEMIHOSTING_H