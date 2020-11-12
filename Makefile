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

# Look for make include files relative to root of FiBot src
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
_all: help

obj-y := 
lib-y := 

include lib/Makefile
include init/Makefile
include common/Makefile

# include project specific Makefile
-include projects.include
ifneq ($(project-dirs),)
include projects/$(project-dirs)/Makefile
endif

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

help:
	@echo "\033[31mStep 1\033[0m: include YOUR projects' Makefile in projects.include"
	@echo "\033[31mStep 2\033[0m: execute \"make [targets]\" to build your projects"