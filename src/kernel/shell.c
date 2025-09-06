#include "include/shell.h"
#include "include/serial.h"
#includeinclude "include/keyboard.h"
#include "include/string.h"
#include "include/reboot.h"
#include "include/process.h" // <-- Include process management header

#define CMD_BUFFER_SIZE 256
#define PROMPT "> "

static char cmd_buffer[CMD_BUFFER_SIZE];

// Helper to find the start of the argument after a command (e.g., "run prog.bin")
static char* get_argument(char* command) {
    while (*command && *command != ' ') command++; // Find the first space
    while (*command && *command == ' ') command++; // Skip over all spaces
    return (*command) ? command : NULL;
}

static void read_line() {
    char c = 0;
    int i = 0;
    for (i = 0; i < CMD_BUFFER_SIZE - 1; ) {
        c = keyboard_poll();
        if (c != 0) {
            if (c == '\n') {
                print_char('\n');
                break;
            } else if (c == 0x08) {
                if (i > 0) {
                    i--;
                    print_char(0x08);
                }
            } else {
                cmd_buffer[i++] = c;
                print_char(c);
            }
        }
    }
    cmd_buffer[i] = '\0';
}


static void execute_command() {
    if (strlen(cmd_buffer) == 0) return;

    if (strcmp(cmd_buffer, "help") == 0) {
        print("Kernel Shell v1.1\n");
        print("Commands:\n");
        print("  help         - Show this help message\n");
        print("  reboot       - Reboot the machine\n");
        print("  run <file>   - Load and run a process from a file\n");
        print("  save <file>  - Save current process memory to a file\n");
    } else if (strcmp(cmd_buffer, "reboot") == 0) {
        print("Rebooting...\n");
        reboot();
    } else if (strncmp(cmd_buffer, "run ", 4) == 0) {
        char* filename = get_argument(cmd_buffer);
        if (filename) {
            uint32_t entry, sp;
            if (swap_in(filename, &entry, &sp) == 0) {
                run_process(entry, sp);
            }
        } else {
            print("Usage: run <filename>\n");
        }
    } else if (strncmp(cmd_buffer, "save ", 5) == 0) {
        char* filename = get_argument(cmd_buffer);
        if (filename) {
            swap_out(filename);
        } else {
            print("Usage: save <filename>\n");
        }
    } else {
        print("Unknown command: ");
        print(cmd_buffer);
        print("\n");
    }
}


void shell_init(void) {
    print("Shell initialized. Type 'help' for a list of commands.\n");
}

void shell_run(void) {
    while (1) {
        print(PROMPT);
        read_line();
        execute_command();
    }
}