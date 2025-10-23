#ifndef	_P_GPIO_H
#define	_P_GPIO_H

#include "peripherals/base.h"

#define GPFSEL1         ((volatile unsigned int *)(PBASE+0x00200004)) // select function of GPIO 10 - GPIO 19
#define GPPUD           ((volatile unsigned int *)(PBASE+0x00200094)) //GPIO Pin Pull-up/down Enable 
#define GPPUDCLK0       ((volatile unsigned int *)(PBASE+0x00200098)) //GPIO Pin Pull-up/down Enable Clock 0

#endif  /*_P_GPIO_H */