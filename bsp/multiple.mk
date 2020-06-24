## source file path  
CUR_SOURCE := $(wildcard $(SRC_PATH)/*.c)
CUR_OBJS := $(CUR_SOURCE:.c=.o)
CUR_DEPS := $(CUR_SOURCE:.c=.d)
OBJ_NAME := $(notdir $(SRC_PATH))

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += $(foreach file, $(CUR_SOURCE), ./$(BUILD_DIR)/$(file)) 

TEMP_OBJS :=
TEMP_OBJS += $(foreach file, $(CUR_OBJS), ./$(BUILD_DIR)/$(file)) 
OBJS += ./$(BUILD_DIR)/$(SRC_PATH)/$(OBJ_NAME).o
C_DEPS += $(foreach file, $(CUR_DEPS), ./$(BUILD_DIR)/$(file))
C_DEPS += ./$(BUILD_DIR)/$(TAG_PATH).d


$(BUILD_DIR)/$(SRC_PATH)/$(OBJ_NAME).o : $(TEMP_OBJS)
	@echo 'Linking file: $^'
	@echo 'Invoking: Cross GCC Linker'
	$(LL) -relocatable $^ -o $@
	@echo 'Finished Linking: $^'
	@echo ' '

# Each subdirectory must supply rules for building sources it contributes
$(BUILD_DIR)/$(SRC_PATH)/%.o : $(SRC_PATH)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	$(CC) $(CC_OPTIONS) $(CC_DEFINES) $(CC_INCLUDE) -MMD -MP -MF$(@:%.o=%.d) -MT$(@) -c -o $@ $<
	@echo 'Finished building: $<'
	@echo ' '
