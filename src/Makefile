objs := $(wildcard src/*.c src/*.S src/*.s)
objs := $(patsubst %.c,%.o,$(objs))
objs := $(patsubst %.s,%.o,$(objs))
objs := $(patsubst %.S,%.o,$(objs))

obj-y += $(objs)