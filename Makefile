VERSION = 0
PATCHLEVEL = 1
EXTRAVERSION = -rc1

MAKEFLAGS += -rR --no-print-directory

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

# That's our default target when none is given on the command line
PHONY := _all
_all:

obj-y := 
lib-y := 

include lib/Makefile
include src/Makefile

_all:
	$(Q)echo obj-y: $(obj-y)
	$(Q)echo lib-y: $(lib-y)