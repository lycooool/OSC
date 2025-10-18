#ifndef _MAILBOX_H
#define _MAILBOX_H

#include "peripherals/base.h"

#define MAILBOX_READ    ((volatile unsigned int *)(MAILBOX_BASE))
#define MAILBOX_STATUS  ((volatile unsigned int *)(MAILBOX_BASE + 0x18))
#define MAILBOX_WRITE   ((volatile unsigned int *)(MAILBOX_BASE + 0x20))

#define MAILBOX_EMPTY   0x40000000
#define MAILBOX_FULL    0x80000000

#endif

