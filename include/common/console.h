#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <common/list.h>

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
	char (*getc) (void);             /* To get that char */

	struct list_head list;
};

int prints(const char *fmt, ...);

int printc(const char c);
int printb(const char c);
int printh(const char c);

int printui(unsigned int ui);
int printi(int i);

char getc();

extern int stdio_register(struct stdio_device *dev);
int stdio_init(void);

#endif