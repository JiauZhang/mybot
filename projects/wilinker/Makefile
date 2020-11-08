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