#include "terminal.h"


int __io_putchar(int c) {
    if (c == '\n'){
        while(!(UART5->ISR & USART_ISR_TXE));
        UART5->TDR = '\r';
    }

    while(!(UART5->ISR & USART_ISR_TXE));
    UART5->TDR = c;
    return c;
}

int __io_getchar(void) {
    int c = line_buffer_getchar();
    return c;
}
