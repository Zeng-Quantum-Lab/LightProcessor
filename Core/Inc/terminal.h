#ifndef TERMINAL_H
#define TERMINAL_H

#include "stm32g4xx_hal.h"
#include "stm32g4xx.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "fifo.h"
#include "tty.h"

void init_terminal();
int __io_putchar(int c);
int __io_getchar(void);

#endif
