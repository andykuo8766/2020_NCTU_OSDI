ARMGNU ?= aarch64-linux-gnu

COPS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only -std=gnu99 -ggdb
ASMOPS = -Iinclude -ggdb

BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include

all : kernel8.img

clean :
	rm -rf $(BUILD_DIR) *.img ramdisk

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@	
	
$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@	
	
$(BUILD_DIR)/%_psf.o: %.psf
	mkdir -p $(@D)
	$(ARMGNU)-ld -r -b binary -o $@ $<

$(BUILD_DIR)/%_sfn.o: %.sfn
	mkdir -p $(@D)
	$(ARMGNU)-ld -r -b binary -o $@ $<

tar:
	tar -cf ramdisk $(SRC_DIR)/*.c $(INCLUDE_DIR)/*.h
	
cpio:
	ls $(SRC_DIR)/*.c $(INCLUDE_DIR)/*.h | cpio -H hpodc -o >ramdisk

$(BUILD_DIR)/rd.o: ramdisk
	$(ARMGNU)-ld -r -b binary -o $(BUILD_DIR)/rd.o ramdisk


C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

kernel8.img: $(SRC_DIR)/linker.ld  $(BUILD_DIR)/font_psf.o $(BUILD_DIR)/font_sfn.o $(BUILD_DIR)/rd.o $(OBJ_FILES)
	$(ARMGNU)-ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf $(BUILD_DIR)/font_psf.o $(BUILD_DIR)/font_sfn.o $(BUILD_DIR)/rd.o $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img
run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio

pi:
	sudo screen /dev/ttyUSB0 115200
