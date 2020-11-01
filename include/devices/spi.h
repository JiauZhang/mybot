#ifndef __SPI_H__
#define __SPI_H__

#include <stm32f10x.h>

void spi_init();
u8 spi_read();
void spi_write(u8 data);

#endif
