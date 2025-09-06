ENTRY(_start)

MEMORY
{
    ram (rwx) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS
{
    . = 0x80000000;

    .bootloader : { *(.bootloader) } > ram
    .text       : { *(.text)       } > ram
    .rodata     : { *(.rodata)     } > ram
    .data       : { *(.data)       } > ram
    .bss        : { *(.bss)        } > ram

    . = ALIGN(4096);
    _end_of_kernel = .;

    /*
     * Define the Application RAM Window. This reserves a 4MB space
     * immediately after the kernel for the single user process to run in.
     */
    __app_ram_start__ = .;
    . = . + 4M;
    __app_ram_end__ = .;

    _stack_start = . + 1M;

    /DISCARD/ :
    {
        *(.reginfo)
        *(.MIPS.abiflags)
        *(.MIPS.attributes)
    }
}