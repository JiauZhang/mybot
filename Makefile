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

ASFLAGS = -mcpu=$(CPU) -mthumb -c
ASFLAGS += -Wall -fdata-sections -ffunction-sections

# CFLAGS = -mcpu=$(CPU) -mthumb -Os -DUSE_HAL_DRIVER -DSTM32F103xB
CFLAGS = -mcpu=$(CPU) -mthumb -c
CFLAGS += -Wall -fdata-sections -ffunction-sections
CFLAGS += -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER
CFLAGS += -Iinclude

LDSCRIPT = STM32F103C8Tx_FLASH.ld
LIBS = -lc -lm -lnosys 
LIBDIR =
LDFLAGS = -mcpu=$(CPU) -mthumb -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,--gc-sections

# That's our default target when none is given on the command line
PHONY := _all
_all: WiLinker-Tx.bin WiLinker-Rx.bin

obj-y := 
lib-y := 

include lib/Makefile
include init/Makefile
include drivers/Makefile

obj-tx = $(filter-out drivers/nrf24l01-rx.o,$(obj-y))
WiLinker-Tx.elf: $(obj-tx) lib/libcore.a
	$(Q)$(CC) $(obj-tx) -L lib -lcore $(LDFLAGS) -o $@
	$(Q)echo "\033[31m$@\033[0m is ready!"
obj-rx = $(filter-out drivers/nrf24l01-tx.o,$(obj-y))
WiLinker-Rx.elf: $(obj-rx) lib/libcore.a
	$(Q)$(CC) $(obj-rx) -L lib -lcore $(LDFLAGS) -o $@
	$(Q)echo "\033[31m$@\033[0m is ready!"
WiLinker-Tx.bin: WiLinker-Tx.elf
	$(Q)echo "OBJCOPY   $@"
	$(Q)$(OBJCOPY) -O binary -R .comment -S $< $@
	$(Q)echo "\033[31m$@\033[0m is ready!"
WiLinker-Rx.bin: WiLinker-Rx.elf
	$(Q)echo "OBJCOPY   $@"
	$(Q)$(OBJCOPY) -O binary -R .comment -S $< $@
	$(Q)echo "\033[31m$@\033[0m is ready!"
WiLinker.hex: WiLinker
	$(Q)echo "OBJCOPY   $@"
	$(Q)$(OBJCOPY) -O -ihex $< $@
	$(Q)echo "\033[31m$@\033[0m is ready!"
WiLinker.dis: WiLinker
	$(Q)echo "OBJDUMP   $@"
	$(Q)$(OBJDUMP) -D -m arm $< > $@
	$(Q)echo "\033[31m$@\033[0m is ready!"

%.o: %.S
	$(Q)echo "AS        $@"
	$(Q)$(CC) $(ASFLAGS) $< -o $@
%.o: %.c
	$(Q)echo "CC        $@"
	$(Q)$(CC) $(CFLAGS) $< -o $@

lib/libcore.a: $(lib-y)
	$(Q)echo "AR        $@"
	$(Q)rm -f $@
	$(Q)$(AR) rcs $@ $(lib-y)

clean:
	$(Q)rm -f lib/*.o lib/*.a
	$(Q)rm -f init/*.o
	@(Q)rm -f drivers/*.o
	$(Q)rm -f WiLinker WiLinker.bin WiLinker.dis
