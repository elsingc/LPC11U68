##########################################################################
# User configuration and firmware specific object files	
##########################################################################

FILENAME=firmware

# See projectconfig.h for a list of valid BOARD options!
BOARD=CFG_BRD_RF1GHZUSB

# Set TARGET to 'lpc11u' or 'lpc13u' depending on the target MCU
TARGET = lpc11u
ifeq (lpc11u,$(TARGET))
  CORE = cortex-m0plus
  LDSCRIPT = cmsis/lpc11u68.ld
else
  CORE = cortex-m3
  LDSCRIPT = cmsis/lpc1347.ld
endif

# Set OPTIMIZATION to '0', '1', '2', '3' or 's'
OPTIMIZATION = s

##########################################################################
# Output directories
##########################################################################

BIN_PATH = bin
OBJ_PATH = bin/obj

##########################################################################
# Source Files
##########################################################################

VPATH = cmsis
ifeq (lpc11u,$(TARGET))
  OBJS   = $(OBJ_PATH)/startup_lpc11u_gnumake.o 
  OBJS  += $(OBJ_PATH)/system_LPC11Uxx.o
else
  OBJS   = $(OBJ_PATH)/startup_lpc13u_gnumake.o 
  OBJS  += $(OBJ_PATH)/system_LPC13Uxx.o
endif

VPATH += src
OBJS  += $(OBJ_PATH)/printf-retarget.o
OBJS  += $(OBJ_PATH)/main.o

VPATH += driver
OBJS  += $(OBJ_PATH)/delay.o
OBJS  += $(OBJ_PATH)/fifo.o
OBJS  += $(OBJ_PATH)/gpio.o
OBJS  += $(OBJ_PATH)/stdio.o 
OBJS  += $(OBJ_PATH)/string.o

VPATH += driver/usb
OBJS  += $(OBJ_PATH)/descriptors.o 
OBJS  += $(OBJ_PATH)/usb_cdc.o 
OBJS  += $(OBJ_PATH)/usbd.o

##########################################################################
# Include paths
##########################################################################

ROOT_PATH = src
INC_PATH  = inc
INCLUDE_PATHS = -I$(ROOT_PATH) -I$(INC_PATH) -Icmsis

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
GCFLAGS += -DTARGET=$(TARGET)
GCFLAGS += -D$(BOARD)
# CMSIS DSP Flags
ifeq (lpc11u,$(TARGET))
  GCFLAGS += -DARM_MATH_CM0
else
  GCFLAGS += -DARM_MATH_CM3
endif
# For use with the GCC ARM Embedded toolchain
GCFLAGS += --specs=nano.specs

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
LDFLAGS  = -nostartfiles 
LDFLAGS += -mcpu=$(CORE) 
LDFLAGS += -mthumb 
LDFLAGS += -O$(OPTIMIZATION) 
LDFLAGS += -Wl,--gc-sections 
LDFLAGS += -T $(LDSCRIPT)
LDFLAGS += -Xlinker -Map=bin/firmware.map

# External Libraries
LDLIBS   += -lm

##########################################################################
# Rules
##########################################################################

all: firmware

$(OBJ_PATH)/%.o : %.c
	@echo "COMPILING $(@F)"
	@$(CC) $(GCFLAGS) -o $@ $<

$(OBJ_PATH)/%.o : %.s
	@echo "ASSEMBLING $(@F)"
	@$(AS) $(ASFLAGS) -o $@ $<

firmware: $(OBJS) $(SYS_OBJS)
	@echo ""
	@echo "LINKING $(OUTFILE).elf ($(CORE) -O$(OPTIMIZATION) $(BOARD))"
	@$(LD) $(LDFLAGS) -o $(OUTFILE).elf $(LDLIBS) $(OBJS) $(LDLIBS)
	@echo ""
	@$(SIZE) $(OUTFILE).elf
	@echo ""
	@echo "Generating $(OUTFILE).hex"
	@$(OBJCOPY) $(OCFLAGS) -O ihex $(OUTFILE).elf $(OUTFILE).hex
	@echo "Generating $(OUTFILE).bin"
	@$(OBJCOPY) $(OCFLAGS) -O binary $(OUTFILE).elf $(OUTFILE).bin

flash: firmware
	@echo ""
	@echo "Flashing device ..."
	@[ -e "$(MOUNT_POINT)/firmware.bin" ] && dd if=bin/firmware.bin of="$(MOUNT_POINT)/firmware.bin" conv=nocreat,notrunc && umount "$(MOUNT_POINT)" || echo "Error, no device?!"

lpcrc:
	@echo ""
	@echo "Building lpcrc (checksum tool) ..."
	@make -C tools/lpcrc
  
clean:
	@$(REMOVE) $(OBJS) $(OUTFILE).elf $(OUTFILE).bin $(OUTFILE).hex

#########################################################################
