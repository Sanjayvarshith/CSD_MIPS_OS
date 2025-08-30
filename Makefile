# Makefile for the MIPS OS Kernel

# --- Toolchain and Flags ---
# Define the commands for the MIPS cross-compiler toolchain
AS = mips-linux-gnu-as
CC = mips-linux-gnu-gcc
LD = mips-linux-gnu-ld

# Define the flags for compiling, assembling, and linking
# -g: Include debug symbols
# -mips32: Target the MIPS32 architecture
# -nostdlib: Don't link the standard C library
# -ffreestanding: We're not running on an existing OS
# -mno-abicalls -fno-pic: Ensure simple, compatible machine code
ASFLAGS = -g -mips32
CFLAGS = -g -c -mips32 -nostdlib -ffreestanding -mno-abicalls -fno-pic
LDFLAGS = -T linker.ld

# --- Project Structure ---
# Define the build directory where compiled files will go
BUILD_DIR = build
# Define the final kernel executable name
KERNEL = kernel

# --- Source Files ---
# Automatically find all .S (assembly) and .c (C) files in the src directory
S_FILES = $(shell find src -name '*.S')
C_FILES = $(shell find src -name '*.c')

# --- Object Files ---
# Generate the list of object (.o) files that will be created in the build directory
# e.g., src/drivers/serial.c becomes build/drivers/serial.o
OBJS = $(patsubst src/%.S, $(BUILD_DIR)/%.o, $(S_FILES))
OBJS += $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(C_FILES))

# --- Main Build Rules ---

# The default rule, executed when you just type 'make'
# It depends on the final kernel ELF file
all: $(BUILD_DIR)/$(KERNEL).elf

# Rule to link the final kernel ELF file
# It depends on all the compiled object files
$(BUILD_DIR)/$(KERNEL).elf: $(OBJS)
	@echo "LD   $@"
	@$(LD) $(LDFLAGS) -o $@ $(OBJS)

# Rule to compile any C source file
# src/foo.c -> build/foo.o
$(BUILD_DIR)/%.o: src/%.c
	@echo "CC   $<"
	@mkdir -p $(dir $@) # Create the subdirectory in build/ if it doesn't exist
	@$(CC) $(CFLAGS) -Isrc -o $@ $< # -Isrc tells the compiler to look in src/ for headers

# Rule to assemble any Assembly source file
# src/foo.S -> build/foo.o
$(BUILD_DIR)/%.o: src/%.S
	@echo "AS   $<"
	@mkdir -p $(dir $@)
	@$(AS) $(ASFLAGS) -o $@ $<

# --- Utility Rules ---

# Rule to run the kernel in QEMU
run: all
		@qemu-system-mips -M malta -cpu 4Kc -m 128 -kernel $(BUILD_DIR)/$(KERNEL).elf -serial mon:stdio

# Rule to clean up all compiled files
clean:
	@echo "Cleaning project..."
	@rm -rf $(BUILD_DIR)

# Declare which rules are not actual files
.PHONY: all run clean
