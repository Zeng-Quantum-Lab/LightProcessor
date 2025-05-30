#include <stdint.h>
#include <stdio.h>
#include "terminal.h"
#include <time.h>
#include "fifo.h"
#include "tty.h"

int __io_putchar(int c) {
    // TODO Copy from your STEP2
    if (c == '\n'){
        while(!(USART5->ISR & USART_ISR_TXE));
        USART5->TDR = '\r';
    }

    while(!(USART5->ISR & USART_ISR_TXE));
    USART5->TDR = c;
    return c;
}

int __io_getchar(void) {
    // TODO
    int c = line_buffer_getchar();
    return c;
}
