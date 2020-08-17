VERSION = 0
PATCHLEVEL = 1
EXTRAVERSION = -rc1

# MAKEFLAGS += -rR --no-print-directory
MAKEFLAGS += --no-print-directory

ifeq ("$(origin V)", "command line")
  BUILD_VERBOSE = $(V)
endif
ifndef KBUILD_VERBOSE
  BUILD_VERBOSE = 0
endif

ifeq ($(BUILD_VERBOSE),1)
  quiet =
  Q =
else
  quiet=quiet_
  Q = @
endif

srctree := $(CURDIR)
objtree := $(CURDIR)
src := $(srctree)
obj := $(objtree)

export srctree objtree

# Look for make include files relative to root of usboot src
MAKEFLAGS += --include-dir=$(srctree)

ARCH = arm
CPU = cortex-m3
BOARD = bluepill
CROSS_COMPILE = arm-none-eabi-

export ARCH CPU BOARD

AS = $(CROSS_COMPILE)as
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
AR = $(CROSS_COMPILE)ar
NM = $(CROSS_COMPILE)nm
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
SZ = $(CROSS_COMPILE)size

export AS CC LD AR NM OBJCOPY OBJDUMP

ASFLAGS = -mcpu=$(CPU) -mthumb

CFLAGS = -mcpu=$(CPU) -mthumb -DUSE_HAL_DRIVER -DSTM32F103xB
CFLAGS += -Wall -fdata-sections -ffunction-sections
CFLAGS += -Iinclude

LDSCRIPT = STM32F103C8Tx_FLASH.ld
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = -mcpu=$(CPU) -mthumb -specs=nano.specs -T$(LDSCRIPT) \
	$(LIBDIR) $(LIBS) -Wl,--gc-sections

# That's our default target when none is given on the command line
PHONY := _all
_all: WiLinker

obj-y := 
lib-y := 

include lib/Makefile
include src/Makefile

WiLinker: $(obj-y) $(lib-y)
	$(Q)$(CC) $(obj-y) $(lib-y) $(LDFLAGS) -o $@
	$(Q)$(SZ) $@
WiLinker.bin: WiLinker
	$(Q)$(OBJCOPY) -O binary -S $< $@
WiLinker.hex: WiLinker
	$(Q)$(OBJCOPY) -O -ihex $< $@
WiLinker.dis: WiLinker
	$(Q)echo "OBJDUMP   $@"
	$(Q)$(OBJDUMP) -D -m arm $< > $@

%.o: %.S
	$(Q)echo "AS        $@"
	$(Q)$(AS) -c $(ASFLAGS) $< -o $@
%.o: %.c
	$(Q)echo "CC        $@"
	$(Q)$(CC) -c $(CFLAGS) $< -o $@