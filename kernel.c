#define SERIAL0 0xBFD003F8   // MIPS Malta UART base

void serial_putc(char c) {
    volatile char *serial = (volatile char*)SERIAL0;
    *serial = c;
}

void serial_puts(const char *s) {
    while(*s) {
        serial_putc(*s++);
    }
}

typedef struct {
    int pid;
    char *name;
} Process;

void kmain() {
    serial_puts("Running the MIPS OS...\n");

    Process p1 = {1, "Process1"};
    Process p2 = {2, "Process2"};

    Process *plist[2] = {&p1, &p2};
    int i = 0;

    while(1) {
        serial_puts(plist[i]->name);
        serial_puts(" is running\n");
        for(volatile int j=0;j<1000000;j++); // dummy delay
        i = (i + 1) % 2;
    }
}
