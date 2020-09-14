#include <wilinker/serial.h>
#include <wilinker/console.h>

static struct serial_device *serial_devices;
static struct serial_device *serial_current;

static void serial_null(void)
{
}

#define serial_initfunc(name)   \
	void name(void)             \
		__attribute__((weak, alias("serial_null")));

serial_initfunc(stm32_serial_initialize);

void serial_register(struct serial_device *dev)
{
	dev->next = serial_devices;
	serial_devices = dev;
}

void serial_initialize(void)
{
	stm32_serial_initialize();
	serial_current = serial_devices;
}

static struct stdio_device serial_stdio_drv = {
	.flags  = DEV_FLAGS_INPUT | DEV_FLAGS_OUTPUT,
	.name   = "stm32_stdio",
	.start  = serial_init,
	.stop   = 0,
	.putc   = serial_putc,
	.puts   = serial_puts,
	.getc   = 0,
	.tstc   = 0,
};

void serial_stdio_init(void)
{
	stdio_register(&serial_stdio_drv);
}

int serial_init(void)
{
	serial_initialize();
	return serial_current->start();
}

void serial_putc(const char c)
{
	serial_current->putc(c);
}

void serial_puts(const char *s)
{
	serial_current->puts(s);
}