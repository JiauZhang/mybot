set(obj-ON)
set(obj-OFF)
set(obj-)

list(APPEND obj-${CONFIG_USART} usart.c)
list(APPEND obj-${CONFIG_NRF24L01} nrf24l01.c)
list(APPEND obj-${CONFIG_PWM} pwm.c)
list(APPEND obj-${CONFIG_SPI} spi.c)

add_library(drivers ${obj-ON})