/*
 * https://github.com/JiauZhang/FiBot/common/console.c
 */

#include <common/console.h>
#include <common/serial.h>
#include <stdarg.h>

static struct stdio_device *stdio_device;
// struct stdio_dev *stdio_devices[] = { 0, 0, 0 };
// char *stdio_names[3] = { "stdin", "stdout", "stderr" };

#define CONFIG_SYS_PBSIZE (128)

int prints(const char *fmt, ...)
{
	va_list args;
	int num;
	char *str;
	if (stdio_device && stdio_device->putc && stdio_device->puts) {
		va_start(args, fmt);
		
		for (; *fmt; fmt++) {
			if (*fmt != '%') {
				stdio_device->putc(*fmt);
				if (*fmt == '\n')
					stdio_device->putc('\r');
				continue;
			}
			
			++fmt;
			switch (*fmt) {
			case 's':
				str = va_arg(args, char *);
				stdio_device->puts(str);
				continue;
			
			case 'd':
				num = va_arg(args, int);
				stdio_device->putc(num+'0');
				continue;
			
			default:
				stdio_device->putc('%');
				if (*fmt)
					stdio_device->putc(*fmt);
				else
					--fmt;
				continue;
			}
		}
		
		return 0;
	}
	
	return -1;
}

int printc(const char c)
{
	int count = 0;
	
	if (stdio_device) {
		stdio_device->putc(c);
		count = 1;
	}
	
	return count;
}

int printb(const char c)
{
	unsigned char base = '0';
	unsigned char uc = c;
	unsigned char bit;
	int i;
	int count = 0;
	
	for (i=7; i>=0; i--) {
		bit = 0x01 << i;
		
		if (uc & bit)
			count += printc(base+1);
		else
			count += printc(base);
	}
	
	return count;
}

int printh(const char c)
{
	unsigned char uc = c;
	int count = 0;
	count += printc('0');
	count += printc('x');
	
	unsigned char high = (uc & 0xf0) >> 4;
	unsigned char low = uc & 0x0f;
	
	if (high < 10)
		count += printc(high + '0');
	else
		count += printc(high - 10 + 'a');
	
	if (low < 10)
		count += printc(low + '0');
	else
		count += printc(low - 10 + 'a');
	
	return count;
}

int printui(unsigned int ui)
{
	return ui;
}

char getc()
{
	char c;
	
	if (stdio_device)
		c = stdio_device->getc();
	
	return c;
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