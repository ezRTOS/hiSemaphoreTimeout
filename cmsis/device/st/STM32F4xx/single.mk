## source file path  
CUR_SOURCE_ASM = $(wildcard $(SRC_PATH)/*.s)
CUR_OBJS_ASM = $(CUR_SOURCE_ASM:.s=.o)
CUR_DEPS_ASM = $(CUR_SOURCE_ASM:.s=.d)

CUR_SOURCE_C = $(wildcard $(SRC_PATH)/*.c)
CUR_OBJS_C = $(CUR_SOURCE_C:.c=.o)
CUR_DEPS_C = $(CUR_SOURCE_C:.c=.d)

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += $(foreach file, $(CUR_SOURCE), ./$(BUILD_DIR)/$(file)) 

OBJS += $(foreach file, $(CUR_OBJS_ASM), ./$(BUILD_DIR)/$(file))
OBJS += $(foreach file, $(CUR_OBJS_C), ./$(BUILD_DIR)/$(file))

# Each subdirectory must supply rules for building sources it contributes
$(BUILD_DIR)/$(SRC_PATH)/%.o: ./$(SRC_PATH)/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	$(CC) $(ASM_OPTIONS) -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(BUILD_DIR)/$(SRC_PATH)/%.o : $(SRC_PATH)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	$(CC) $(CC_OPTIONS) $(CC_DEFINES) $(CC_INCLUDE) -MMD -MP -MF$(@:%.o=%.d) -MT$(@) -c -o $@ $<
	@echo 'Finished building: $<'
	@echo ' '

