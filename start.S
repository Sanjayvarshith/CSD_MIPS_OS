    .section .text
    .globl _start
_start:
    la   $sp, _stack_top    # set stack pointer
    jal  kmain              # jump to kernel main
    nop

hang:
    j hang
    nop

    .section .bss
    .space 0x1000
_stack_top:
