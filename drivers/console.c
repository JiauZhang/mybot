#include <wilinker/console.h>
#include <wilinker/serial.h>
#include <stdarg.h>

// static struct stdio_dev devs;
// struct stdio_dev *stdio_devices[] = { 0, 0, 0 };
// char *stdio_names[3] = { "stdin", "stdout", "stderr" };

#define CONFIG_SYS_PBSIZE (128)

int puts(const char *s)
{
	serial_puts(s);
	
	return 0;
}

int stdio_register(struct stdio_dev * dev)
{
	return 0;
}

int stdio_init(void)
{
	return 0;
}

int printf(const char *fmt, ...)
{
	return 0;
}