#ifndef	_P_MINI_UART_H
#define	_P_MINI_UART_H

#include "peripherals/base.h"

#define AUXENB              ((volatile unsigned int *)(PBASE+0x00215004)) 
#define AUX_MU_CNTL_REG     ((volatile unsigned int *)(PBASE+0x00215060))  
#define AUX_MU_IER_REG      ((volatile unsigned int *)(PBASE+0x00215044))
#define AUX_MU_LCR_REG      ((volatile unsigned int *)(PBASE+0x0021504C))
#define AUX_MU_MCR_REG      ((volatile unsigned int *)(PBASE+0x00215050))
#define AUX_MU_BAUD         ((volatile unsigned int *)(PBASE+0x00215068))
#define AUX_MU_IIR_REG      ((volatile unsigned int *)(PBASE+0x00215048))
#define AUX_MU_LSR_REG      ((volatile unsigned int *)(PBASE+0x00215054))
#define AUX_MU_IO_REG       ((volatile unsigned int *)(PBASE+0x00215040))
#endif  /*_P_GPIO_H */