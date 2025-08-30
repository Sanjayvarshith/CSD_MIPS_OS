ENTRY(_start)

MEMORY
{
    ram (rwx) : ORIGIN = 0x80000000, LENGTH = 128M
}

SECTIONS
{
    . = 0x80000000;

    .bootloader :
    {
        *(.bootloader)
    } > ram

    .text :
    {
        *(.text)
    } > ram

    .rodata : { *(.rodata) } > ram
    .data   : { *(.data)   } > ram
    .bss    : { *(.bss)    } > ram

    _stack_start = . + 1M;

    /DISCARD/ :
    {
        *(.reginfo)
        *(.MIPS.abiflags)
        *(.MIPS.attributes)
    }
}