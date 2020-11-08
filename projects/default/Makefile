obj-y += drivers/usart.o projects/default/default.o

default.elf: $(obj-y) lib/libcore.a
	$(Q)$(CC) $(obj-y) -L lib -lcore $(LDFLAGS) -o $@
	$(Q)echo "\033[31m$@\033[0m is ready!"

default.bin: default.elf
	$(Q)echo "OBJCOPY   $@"
	$(Q)$(OBJCOPY) -O binary -R .comment -S $< $@
	$(Q)echo "\033[31m$@\033[0m is ready!"

default.dis: default.elf
	$(Q)echo "OBJDUMP   $@"
	$(Q)$(OBJDUMP) -D -m arm $< > $@
	$(Q)echo "\033[31m$@\033[0m is ready!"