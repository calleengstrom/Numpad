#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include <stdint.h>

void uart_init(void);
void uart_tx_byte(uint8_t b);
char uart_rx_byte(void);
uint8_t uart_rx_available(void);
void uart_putchar(char c);
void uart_puts(const char *s);

#endif