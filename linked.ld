ENTRY(_start)
SECTIONS {
    . = 0x80000000; /* Malta kernel load address */

    .text : { *(.text*) }
    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    .bss : { *(.bss*) }
}
