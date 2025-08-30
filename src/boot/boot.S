.section .bootloader, "ax"
.set noreorder
.set noat

.globl _start
.ent _start

_start:
    la   $sp, _stack_start
    jal  kmain
    nop

halt:
    j    halt
    nop

.end _start
