#include <wilinker/console.h>
#include <wilinker/serial.h>

static struct stdio_device *stdio_device;
// struct stdio_dev *stdio_devices[] = { 0, 0, 0 };
// char *stdio_names[3] = { "stdin", "stdout", "stderr" };

#define CONFIG_SYS_PBSIZE (128)

void puts(const char *s)
{
	if (stdio_device)
		stdio_device->puts(s);
}

void putc(const char c)
{
	if (stdio_device)
		stdio_device->putc(c);
}

static void stdio_null(void)
{
}

#define stdio_initfunc(name)   \
	void name(void)             \
		__attribute__((weak, alias("stdio_null")));

stdio_initfunc(serial_stdio_init);

int stdio_register(struct stdio_device *dev)
{
	stdio_device = dev;

	return 0;
}

int stdio_init(void)
{
	serial_stdio_init();
	
	if (stdio_device)
		return stdio_device->start();
	else
		return -1;
}

int printf(const char *fmt, ...)
{
	return 0;
}