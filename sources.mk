OBJ_SRCS := 
ASM_SRCS := 
C_SRCS := 
O_SRCS := 
S_UPPER_SRCS := 
EXECUTABLES := 
OBJS := 
C_DEPS := 

SUBDIRS := 

SRC_PATH := bsp
SUBDIRS += $(SRC_PATH)
-include $(SRC_PATH)/multiple.mk

SRC_PATH := boot
SUBDIRS += $(SRC_PATH)
-include $(SRC_PATH)/multiple.mk

SRC_PATH := app/devices
SUBDIRS += $(SRC_PATH)
-include $(SRC_PATH)/multiple.mk

SRC_PATH := app/init
SUBDIRS += $(SRC_PATH)
-include $(SRC_PATH)/multiple.mk

SRC_PATH := app/main
SUBDIRS += $(SRC_PATH)
-include $(SRC_PATH)/single.mk

SRC_PATH := app/share
SUBDIRS += $(SRC_PATH)
-include $(SRC_PATH)/single.mk

SRC_PATH := app/threads/thread_led
SUBDIRS += $(SRC_PATH)
-include $(SRC_PATH)/multiple.mk

SRC_PATH := cmsis/device/st/stm32f4xx
SUBDIRS += $(SRC_PATH)
-include $(SRC_PATH)/single.mk

SRC_PATH := cmsis/device/st/stm32f4xx/source
SUBDIRS += $(SRC_PATH)
-include $(SRC_PATH)/single.mk
