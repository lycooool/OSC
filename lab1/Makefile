# 使用 Clang 和 LLD
CLANG = clang
LLD = ld.lld
OBJCOPY = llvm-objcopy
TARGET_TRIPLE = aarch64-rpi3-elf 


COPS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only --target=$(TARGET_TRIPLE)# 編譯 c 時使用的選項
ASMOPS = -Iinclude --target=$(TARGET_TRIPLE) # 編譯 asm 時使用的選項

BUILD_DIR = build
SRC_DIR = src

all : kernel8.img

clean :
	rm -rf $(BUILD_DIR) *.img

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c  # 把 BUILD_DIR 下的 xxx.c 編譯成 xxx_c.o
	mkdir -p $(@D) 
	$(CLANG) $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S  # 把 BUILD_DIR 下的 xxx.S 編譯成 xxx_c.o
	$(CLANG) $(ASMOPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c) # 找到 src 目錄下所有以 .c 結尾的檔案，並將列表賦值給 C_FILES。
ASM_FILES = $(wildcard $(SRC_DIR)/*.S) # 找到 src 目錄下所有以 .A 結尾的檔案，並將列表賦值給 ASM_FILES。
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o) #創建 OBJ_FILES 變數，包含所有 C 檔案編譯後應生成的 .o 檔案列表
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o) #新增 OBJ_FILES 變數，包含所有 asm 檔案編譯後應生成的 .o 檔案列表

DEP_FILES = $(OBJ_FILES:%.o=%.d) # 創建一個包含所有依賴檔案（Dependency Files）的列表，透過將 object_file.o轉成 object_file.d 的方式
-include $(DEP_FILES) #將所有自動生成的 .d 檔案的內容讀取並包含到當前的 Makefile 中

kernel8.img: $(SRC_DIR)/linker.ld $(OBJ_FILES) #Linking and Image Creation
	$(LLD) -m aarch64elf -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf  $(OBJ_FILES)
	$(OBJCOPY) $(BUILD_DIR)/kernel8.elf -O binary kernel8.img

qemu: kernel8.img
	qemu-system-aarch64 -M raspi3b -kernel $< -serial null -serial stdio  -d in_asm
