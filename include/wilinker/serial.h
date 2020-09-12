#ifndef __SERIAL_H__
#define __SERIAL_H__

struct serial_device {
	char name[16];

	int (*start)(void);
	int (*stop)(void);
	void (*setbrg)(void);
	int (*getc)(void);
	void (*putc)(const char c);
	void (*puts)(const char *s);

	struct serial_device *next;
};

extern void serial_register(struct serial_device *);
extern void serial_initialize(void);
extern void serial_stdio_init(void);
extern int serial_init(void);

extern void serial_putc(const char c);
extern void serial_puts(const char *s);

#endif