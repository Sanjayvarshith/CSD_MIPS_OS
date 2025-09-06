# Makefile for the MIPS OS Kernel

# --- Toolchain and Flags ---
AS = mips-linux-gnu-as
CC = mips-linux-gnu-gcc
LD = mips-linux-gnu-ld
ASFLAGS = -g -mips32
CFLAGS = -g -c -mips32 -nostdlib -ffreestanding -mno-abicalls -fno-pic
LDFLAGS = -T linker.ld 

# --- Project Structure ---
BUILD_DIR = build
KERNEL = kernel

# --- Source Files ---
S_FILES = $(shell find src -name '*.S')
C_FILES = $(shell find src -name '*.c')

# --- Object Files ---
OBJS = $(patsubst src/%.S, $(BUILD_DIR)/%.o, $(S_FILES))
OBJS += $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(C_FILES))

# --- Main Build Rules ---
all: $(BUILD_DIR)/$(KERNEL).elf

$(BUILD_DIR)/$(KERNEL).elf: $(OBJS)
	@echo "LD   $@"
	@$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.o: src/%.c
	@echo "CC   $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Isrc -o $@ $<

$(BUILD_DIR)/%.o: src/%.S
	@echo "AS   $<"
	@mkdir -p $(dir $@)
	@$(AS) $(ASFLAGS) -o $@ $<

# --- Utility Rules ---

# Rule to run the kernel in QEMU
# CRITICAL: This line must start with a single TAB character.
run: all
	@qemu-system-mips -M malta -cpu 4Kc -m 128 -kernel $(BUILD_DIR)/$(KERNEL).elf -nographic -serial mon:stdio

# Rule to clean up all compiled files
clean:
	@echo "Cleaning project..."
	@rm -rf $(BUILD_DIR)

.PHONY: all run clean