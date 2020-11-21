#include <common/serial.h>
#include <common/console.h>

static struct serial_device *serial_devices;
static struct serial_device *serial_current;

static void serial_null(void)
{
}

#define serial_initfunc(name)   \
	void name(void)             \
		__attribute__((weak, alias("serial_null")));

serial_initfunc(ll_serial_initialize);

void serial_register(struct serial_device *dev)
{
	dev->next = serial_devices;
	serial_devices = dev;
}

void serial_initialize(void)
{
	ll_serial_initialize();
	serial_current = serial_devices;
}

static struct stdio_device serial_stdio_drv = {
	.flags  = DEV_FLAGS_INPUT | DEV_FLAGS_OUTPUT,
	.name   = "stm32_stdio",
	.start  = serial_init,
	.stop   = 0,
	.putc   = serial_putc,
	.puts   = serial_puts,
	.getc   = serial_getc,
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
	if (serial_current && serial_current->putc)
		serial_current->putc(c);
}

void serial_puts(const char *s)
{
	if (!serial_current || !serial_current->putc)
		return;
	
	const char *c = s;
	
	while (*s != '\0') {
		serial_current->putc(*s);
		s++;
	}
	
	if (s > c && *(s-1) == '\n') {
		serial_current->putc('\r');
	}
}

char serial_getc()
{
	char c = 0xff;
	if (serial_current && serial_current->getc)
		c = serial_current->getc();
	
	return c;
}