#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init(uint16_t ubrr);
void uart_putchar(char c);
void uart_puts(const char *s);

#endif