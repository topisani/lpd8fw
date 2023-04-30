######################################
# target
######################################
TARGET = lpd8fw

######################################
# building variables
######################################
# debug build?
DEBUG ?= 1
# optimization
OPT ?= -Os


# C defines
C_DEFS = -DGD32F3 -DGD32F303 -DGD32F30x -DGD32F30X_HD \

#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
	src/main.c \
	src/gd32f30x_it.c \
	src/systick.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_adc.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_bkp.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_can.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_crc.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_ctc.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_dac.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_dbg.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_dma.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_enet.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_exmc.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_exti.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_fmc.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_fwdgt.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_gpio.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_i2c.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_misc.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_pmu.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_rcu.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_rtc.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_sdio.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_spi.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_timer.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_usart.c \
	libs/GD32F30x/GD32F30x_standard_peripheral/Source/gd32f30x_wwdgt.c \
	libs/GD32F30x/CMSIS/GD/GD32F30x/Source/system_gd32f30x.c \

ifeq ($(DEBUG), 1)
C_SOURCES += \
	libs/SEGGER_RTT_V788/RTT/SEGGER_RTT.c \
	libs/SEGGER_RTT_V788/RTT/SEGGER_RTT_printf.c \
	libs/SEGGER_RTT_V788/Syscalls/SEGGER_RTT_Syscalls_GCC.c \
	
endif
	

# ASM sources
ASM_SOURCES =  \
	src/startup_gd32f30x_hd.S

# C++ Sources
CPP_SOURCES = \

# C includes
C_INCLUDES =  \
	-Isrc/ \
	-Ilibs/GD32F30x/CMSIS/ \
	-Ilibs/GD32F30x/CMSIS/GD/GD32F30x/Include/ \
	-Ilibs/GD32F30x/GD32F30x_standard_peripheral/Include/ \
	-Ilibs/SEGGER_RTT_V788/Config \
	-Ilibs/SEGGER_RTT_V788/RTT/ \

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
CXX = $(GCC_PATH)/$(PREFIX)g++
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4


# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard


# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C++ Defs
CXX_DEFS = $(C_DEFS)

# AS includes
AS_INCLUDES = 

# C++ Includes
CXX_INCLUDES = $(C_INCLUDES)

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CXXFLAGS = $(MCU) $(CXX_DEFS) $(CXX_INCLUDES) $(OPT) -Wall -fdata-sections -std=c++20 -ffunction-sections -fno-exceptions -fno-rtti -fcoroutines

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
CXXFLAGS += -g -gdwarf-2
else
CFLAGS += -DNDEBUG
CXXFLAGS += -DNDEBUG
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CXXFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = src/gd32f303rc.ld

# libraries
LIBS = -lc -lm 
LIBDIR = 
LDFLAGS = $(MCU) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

LDFLAGS += -specs=nano.specs -specs=nosys.specs

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))
# List of CPP objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(CPP_SOURCES:.cpp=.cpp.o)))
vpath %.cpp $(sort $(dir $(CPP_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp Makefile | $(BUILD_DIR) 
	$(CXX) -c $(CXXFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
	

#######################################
# flash
#######################################

.PHONY: jlink clean
jlink:
	JLinkExe -Device GD32F303RC -If SWD -Speed 4000
	
flash:
	JLinkExe -Device GD32F303RC -If SWD -Speed 4000 -CommandFile scripts/flash.jlink
	
	
gdbserver:
	JLinkGDBServer -Device GD32F303RC -If SWD -Speed 4000 & JLinkRTTClientExe
