objs := $(wildcard init/*.c init/*.S init/*.s)
objs := $(patsubst %.c,%.o,$(objs))
objs := $(patsubst %.s,%.o,$(objs))
objs := $(patsubst %.S,%.o,$(objs))

obj-y += $(objs)