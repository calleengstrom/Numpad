#include <avr/io.h>
#include "../include/uart.h"

void uart_init(uint16_t ubrr)
{
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)(ubrr & 0xFF);

    /* Enable transmitter */
    UCSR0B = (1 << TXEN0);

    /* 8 databitar, ingen paritet, 1 stoppbit */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_putchar(char c)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }

    UDR0 = c;
}

void uart_puts(const char *s)
{
    while (*s)
    {
        uart_putchar(*s++);
    }
}