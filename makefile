# All Target
OBJ_FILE := ezRTOS_app
LINK_FILE := stm32m4.ld

# Build folder
ifneq ($(MAKECMDGOALS), release)
	BUILD_DIR := _Debug
else
	BUILD_DIR := _Release
endif	

############################
# Command for removing files
RM := rm -rf

############################
# Compiler path
CC_PATH := /opt/eclipse/toolchain/bin

############################
# Compiler
#CC := $(CC_PATH)/arm-none-eabi-gcc
CC := arm-none-eabi-gcc

############################
# Linker
#LL := $(CC_PATH)/arm-none-eabi-gcc
LL := arm-none-eabi-ld

############################
# Compiler include
CC_INCLUDE := \
	-I. \
	-I./include \
	-I./app \
	-I./app/tasks \
	-I./boot \
	-I./bsp \
	-I./cmsis/include \
	-I./cmsis/device/st/stm32f4xx/include	
	
############################
# Compiler include
CC_DEFINES := -D "STM32F40_41xxx"

############################
# Compiler options
ifneq ($(MAKECMDGOALS), release)
	ASM_OPTIONS := -g -mthumb -O0 -mcpu=cortex-m4 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -x assembler-with-cpp
else
	ASM_OPTIONS := -mthumb -O0 -mcpu=cortex-m4 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -x assembler-with-cpp
endif

############################
# Compiler options
ifneq ($(MAKECMDGOALS), release)
	CC_OPTIONS := -g -mthumb -O0 -mcpu=cortex-m4 -fno-builtin -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -std=gnu11 -ffixed-r9
else
	CC_OPTIONS := -mthumb -Os -mcpu=cortex-m4 -fno-builtin -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -std=gnu11 -ffixed-r9
endif

############################
# Compiler options
LL_OPTIONS := -T$(LINK_FILE) -Map=$(BUILD_DIR)/$(OBJ_FILE).map -nostdlib

############################

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

all: $(OBJ_FILE)
debug: $(OBJ_FILE)
release: $(OBJ_FILE)

# Tool invocations
$(OBJ_FILE): $(BUILD_DIR) $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	$(LL) $(LL_OPTIONS) -o "$(BUILD_DIR)/$(OBJ_FILE).elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	-@echo 'Cross ARM GNU Print Size; Cross ARM GNU Create Hex Image; Cross ARM GNU Create Bin Image;'
	-arm-none-eabi-size --format=berkeley "$(BUILD_DIR)/$(OBJ_FILE).elf";arm-none-eabi-objcopy -O ihex "$(BUILD_DIR)/$(OBJ_FILE).elf" "$(BUILD_DIR)/$(OBJ_FILE).hex";arm-none-eabi-objcopy -O binary "$(BUILD_DIR)/$(OBJ_FILE).elf" "$(BUILD_DIR)/$(OBJ_FILE).bin"
	-@echo ' '

# Other Targets
clean:
	-$(RM) _Debug
	-$(RM) _Release
	-@echo ' '

.PHONY: $(BUILD_DIR)
$(BUILD_DIR):
	-$(RM) $(BUILD_DIR)
	busybox mkdir -p $(BUILD_DIR)
	$(foreach DIR,$(SUBDIRS),busybox mkdir -p $(BUILD_DIR)/$(DIR);)
	-@echo ' '
    
.PHONY: all clean dependents

-include ../makefile.targets
