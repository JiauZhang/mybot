obj-y += drivers/usart.o drivers/pwm.o
obj-y += projects/two-wheeled-robot/robot.o

robot.elf: $(obj-y) lib/libcore.a
	$(Q)$(CC) $(obj-y) -L lib -lcore $(LDFLAGS) -o $@
	$(Q)echo "\033[31m$@\033[0m is ready!"

robot.bin: robot.elf
	$(Q)echo "OBJCOPY   $@"
	$(Q)$(OBJCOPY) -O binary -R .comment -S $< $@
	$(Q)echo "\033[31m$@\033[0m is ready!"

robot.dis: robot.elf
	$(Q)echo "OBJDUMP   $@"
	$(Q)$(OBJDUMP) -D -m arm $< > $@
	$(Q)echo "\033[31m$@\033[0m is ready!"