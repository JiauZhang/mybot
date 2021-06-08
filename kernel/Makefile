obj-y := $(wildcard kernel/*.c kernel/*.S kernel/*.s)
obj-y := $(patsubst kernel/%.c,%.o,$(obj-y))
obj-y := $(patsubst kernel/%.s,%.o,$(obj-y))
obj-y := $(patsubst kernel/%.S,%.o,$(obj-y))