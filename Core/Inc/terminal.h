#ifndef TERMINAL_H
#define TERMINAL_H

#include "stm32g4xx.h"
#include <stdint.h>
#include <stdio.h>
#include "terminal.h"
#include <time.h>
#include "fifo.h"
#include "tty.h"

int __io_putchar(int c);
int __io_getchar(void);

#endif
