$(PROJECT).bin: FiBot
	$(Q)echo "OBJCOPY   $@"
	$(Q)$(OBJCOPY) -O binary -R .comment -S $< $@
	$(Q)echo "\033[31m$@\033[0m is ready!"

$(PROJECT).dis: FiBot
	$(Q)echo "OBJDUMP   $@"
	$(Q)$(OBJDUMP) -D -m arm $< > $@
	$(Q)echo "\033[31m$@\033[0m is ready!"