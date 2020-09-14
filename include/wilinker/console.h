#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <wilinker/list.h>

#define DEV_FLAGS_INPUT	 0x00000001   /* Device can be used as input console */
#define DEV_FLAGS_OUTPUT 0x00000002   /* Device can be used as output console */
#define DEV_FLAGS_SYSTEM 0x80000000   /* Device is a system device */

struct stdio_device {
	int flags;      /* Device flags: input/output/system */
	char name[16];  /* Device name */

	int (*start) (void);
	int (*stop) (void);
	void (*putc) (const char c);    /* To put a char */
	void (*puts) (const char *s);   /* To put a string (accelerator) */
	int (*tstc) (void);             /* To test if a char is ready... */
	int (*getc) (void);             /* To get that char */

	struct list_head list;
};

// extern struct stdio_device *stdio_devices[];
// extern char *stdio_names[3];

void puts(const char *s);
void putc(const char c);
// extern int printf(const char *fmt, ...);

extern int stdio_register(struct stdio_device *dev);
extern int stdio_init(void);

#endif