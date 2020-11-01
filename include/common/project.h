#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <devices/console.h>

void __attribute__((weak)) start_project(void);

void __attribute__((weak)) start_project(void)
{
	prints("FiBot default empty project!\n");
	while (1);
}

#endif