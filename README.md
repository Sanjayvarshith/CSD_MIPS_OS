# CSD_MIPS_OS

This project demonstrates running a minimal MIPS bare-metal program using QEMU. The code is written in assembly, compiled with mips-linux-gnu-gcc, and executed on the QEMU MIPS emulator

## Team members:

Sanjay Varshith, cs22b029
Sai Preethika, cs22b006
Gosu Jashwant, cs22b020

## Contribution:

Since it was just a setup all the team members have done all the steps.# CSD_MIPS_OS

---

## Team members:

Sanjay Varshith, cs22b029
Sai Preethika, cs22b006
Gosu Jashwant, cs22b020

---

## Module 1:

- Demonstrates running a minimal MIPS bare-metal program using QEMU. The code is written in assembly, compiled with mips-linux-gnu-gcc, and executed on the QEMU MIPS emulator
- Since it was just a setup all the team members have done all the steps.

---

## Module 2

### Sanjay Varshith: Core System & Build Infrastructure

- Writing the `Makefile` to automate the build, link, and emulation processes.
- Defining the kernel's memory map and section layouts in the `linker.ld` script.
- Implementing the low-level assembly entry point (`_start`) in `boot.S` to set up the stack and call the main C kernel.
- Creating the primary kernel entry file `main.c`, which orchestrates the initialization of all drivers.

### Sai Preethika: Display Drivers (Serial & Graphics)

- Implemented a UART driver for text communication with the host, including initialization and functions to print characters and strings.
- Developing the graphics driver to interface with the screen's framebuffer memory.
- Creating graphics primitives like `put_pixel` and `draw_filled_rectangle` to allow for drawing basic shapes.
- Defining screen dimensions and a 16-bit color palette in `graphics.h`.

### Gosu Jashwant: Input Driver (Keyboard)

- Researching PS/2 keyboard hardware addresses for the MIPS Malta platform and defining them.
- Implementing a keyboard driver (`keyboard_poll`) to read scancodes from the keyboard data port.
- Implementing state management for modifier keys, including **Shift** and **Caps Lock**, to handle uppercase characters and symbols correctly.
- Defining standard PC/AT scancodes in `keyboard.h` for better code readability.

---

## Module 3

### Common Task:

- The hardware specifications of the keyboard (USB/PS2) and the screen (including size and pixel positioning) were studied and documented for driver development.

- The process of loading a program from a pendrive into main memory and transferring control to the loaded program was understood and analyzed.

### Sanjay Varshith: Interactive Shell Interface

- Implementing the core interactive loop in `shell_run` to continuously display a prompt, read user input, and execute commands.
- Developing a line reader that uses the keyboard driver to buffer user input, supporting character echoing and backspace functionality.
- Creating a command parser to interpret strings from the user, with branching logic to handle built-in commands like `help`, `reboot`, `run`, and `save`.
- Defining the public shell interface (`shell_init`, `shell_run`) in `shell.h` for initialization and invocation by the main kernel.

### Sai Preethika: Single-Process Swapping System

- Defining and managing the dedicated application memory region using symbols (`__app_ram_start__`, `__app_ram_end__`) provided by the linker script.
- Implementing the `swap_in` function to load a process binary from a file into the application memory, reading a metadata header to determine the process's entry point and stack pointer.
- Implementing the `swap_out` function to save a snapshot of the application memory region to a file, creating a "swapped out" state.
- Writing the `run_process` function, which uses inline MIPS assembly to switch the stack pointer and jump from kernel code to the user process's entry point, effectively transferring CPU control.

### Gosu Jashwant: System Utilities & Host Communication

- Developing the semihosting driver, which provides a critical link between the guest OS and the host machine for file I/O. This involved writing low-level MIPS assembly to trigger QEMU's semihosting features.
- Creating a simple file API (`sh_open`, `sh_read`, `sh_write`) on top of the semihosting backend to abstract file operations for the process manager.
- Implementing essential string utility functions from scratch, including `strlen` and `strcmp`, to support the shell's command parsing logic.
- Creating a `reboot` utility that interfaces directly with MIPS Malta hardware registers to allow the system to be reset from a shell command.

---
