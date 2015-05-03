##########################################################################
# User configuration and firmware specific object files	
##########################################################################

FILENAME=firmware

# See projectconfig.h for a list of valid BOARD options!
BOARD=CFG_BRD_LPCXPRESSO_LPC1168

# Set TARGET to 'lpc11u' or 'lpc13u' depending on the target MCU
TARGET = main
CORE = cortex-m0plus
LDSCRIPT = lpc11u68.ld

# Set OPTIMIZATION to '0', '1', '2', '3' or 's'
OPTIMIZATION = 0

##########################################################################
# Output directories
##########################################################################

BIN_PATH = bin
OBJ_PATH = bin/obj

##########################################################################
# Source Files
##########################################################################
#VPATH = cmsis
OBJS   = $(OBJ_PATH)/startup_lpc11u6x.o
OBJS  += $(OBJ_PATH)/lpc11u68_clock.o
#OBJS  += $(OBJ_PATH)/system_LPC11Uxx.o

VPATH += core/gpio
OBJS  += $(OBJ_PATH)/gpio.o
OBJS  += $(OBJ_PATH)/iocon.o

VPATH += core/delay
OBJS  += $(OBJ_PATH)/delay.o

VPATH += core/system
OBJS  += $(OBJ_PATH)/system.o

VPATH += core/usb
OBJS  += $(OBJ_PATH)/usbd.o
OBJS  += $(OBJ_PATH)/usb_cdc.o
OBJS  += $(OBJ_PATH)/usb_clock.o
OBJS  += $(OBJ_PATH)/descriptors.o


#VPATH += src/boards/lpcxpresso1168
OBJS  += $(OBJ_PATH)/main.o
  
##########################################################################
# Include paths
##########################################################################

ROOT_PATH = src
INCLUDE_PATHS = -I$(ROOT_PATH) -Icmsis

##########################################################################
# GNU GCC compiler prefix
##########################################################################

# Use the default toolchain (based on the PATH variable, etc.)
CROSS_COMPILE ?= arm-none-eabi-

# OR ... use a toolchain at a specific location
# CROSS_COMPILE = C:/code_red/RedSuiteNXP_5.0.12_1048/redsuite/tools/bin/arm-none-eabi-
# CROSS_COMPILE = C:/arm/gnu4.7.2012.q4/bin/arm-none-eabi-

AS           = $(CROSS_COMPILE)gcc
CC           = $(CROSS_COMPILE)gcc
LD           = $(CROSS_COMPILE)gcc
SIZE         = $(CROSS_COMPILE)size
OBJCOPY      = $(CROSS_COMPILE)objcopy
OBJDUMP      = $(CROSS_COMPILE)objdump
OUTFILE      = $(BIN_PATH)/$(FILENAME)
LPCRC       ?= tools/lpcrc/lpcrc
REMOVE       = rm -f
MOUNT_POINT ?= /media/CRP DISABLD

##########################################################################
# Compiler settings, parameters and flags
##########################################################################

# Compiler Options
GCFLAGS  = -c 
GCFLAGS += -std=gnu99 
GCFLAGS += -g 
GCFLAGS += -O$(OPTIMIZATION) 
GCFLAGS += $(INCLUDE_PATHS) 
GCFLAGS += -Wall 
GCFLAGS += -mthumb 
GCFLAGS += -ffunction-sections 
GCFLAGS += -fdata-sections 
GCFLAGS += -fmessage-length=0 
GCFLAGS += -fno-builtin 
GCFLAGS += -mcpu=$(CORE) 
#GCFLAGS += -DTARGET=$(TARGET)
#GCFLAGS += -D$(BOARD)

# CMSIS DSP Flags
#GCFLAGS += -DARM_MATH_CM0

# For use with the GCC ARM Embedded toolchain
GCFLAGS += --specs=nano.specs
# For use with the LPCXpresso toolchain
# GCFLAGS += -D__REDLIB__ -D__CODE_RED

# Assembler Options
ASFLAGS  = -c 
ASFLAGS += -g 
ASFLAGS += -O$(OPTIMIZATION) 
ASFLAGS += $(INCLUDE_PATHS) 
ASFLAGS += -Wall 
ASFLAGS += -mthumb 
ASFLAGS += -ffunction-sections 
ASFLAGS += -fdata-sections 
ASFLAGS += -fmessage-length=0 
ASFLAGS += -mcpu=$(CORE) 
ASFLAGS += -D__ASSEMBLY__ 
ASFLAGS += -x assembler-with-cpp

# Linker Options
LDFLAGS = -nostartfiles 
LDFLAGS += -mcpu=$(CORE) 
LDFLAGS += -mthumb 
LDFLAGS += -O$(OPTIMIZATION) 
LDFLAGS += -Wl,--gc-sections 
LDFLAGS += -T $(LDSCRIPT)
LDFLAGS += -Xlinker -Map=bin/firmware.map
# CMSIS Libraries
#LDFLAGS += -L./cmsis/libs

#LDLIBS   = -larm_cortexM0l_math -lRTX_CM0

# External Libraries
#LDLIBS   += -lm
# The following libraries are required with the LPCXpresso toolchain
# LDLIBS  += -lcr_c -lcr_eabihelpers

#OCFLAGS = --strip-unneeded

##########################################################################
# Rules
##########################################################################

all: firmware

$(OBJ_PATH)/%.o : %.c
	@mkdir -p $(dir $@)
	-@echo "COMPILING $(@F)"
	@$(CC) $(GCFLAGS) -o $@ $<

$(OBJ_PATH)/%.o : %.s
	@mkdir -p $(dir $@)
	-@echo "ASSEMBLING $(@F)"
	@$(AS) $(ASFLAGS) -o $@ $<

firmware: $(OBJS) $(SYS_OBJS)
	@mkdir -p $(BIN_PATH)
	-@echo ""
	-@echo "LINKING $(OUTFILE).elf ($(CORE) -O$(OPTIMIZATION) $(BOARD))"
	@$(LD) $(LDFLAGS) -o $(OUTFILE).elf $(LDLIBS) $(OBJS) $(LDLIBS)
	-@echo ""
	@$(SIZE) $(OUTFILE).elf
	-@echo ""
	-@echo "Generating $(OUTFILE).hex"
	@$(OBJCOPY) $(OCFLAGS) -O ihex $(OUTFILE).elf $(OUTFILE).hex
	-@echo "Generating $(OUTFILE).bin"
	@$(OBJCOPY) $(OCFLAGS) -O binary $(OUTFILE).elf $(OUTFILE).bin
	-@echo ""
	@$(LPCRC) $(OUTFILE).bin

flash: firmware
	-@echo ""
	-@echo "Flashing device ..."
	-@[ -e "$(MOUNT_POINT)/firmware.bin" ] && dd if=bin/firmware.bin of="$(MOUNT_POINT)/firmware.bin" conv=nocreat,notrunc && umount "$(MOUNT_POINT)" || echo "Error, no device?!"

#lpcrc:
#	-@echo ""
#	-@echo "Building lpcrc (checksum tool) ..."
#	@make -C tools/lpcrc
  
clean:
	@$(REMOVE) $(OBJS) $(OUTFILE).elf $(OUTFILE).bin $(OUTFILE).hex

#########################################################################
