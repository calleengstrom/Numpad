#include <avr/io.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "../include/uart.h"
#define F_CPU 16000000UL
#define BAUD 9600UL
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1UL)


/* ---------- RX buffer ---------- */
#define UART_RX_BUF_SIZE 32

static volatile char uart_rx_buf[UART_RX_BUF_SIZE];
static volatile uint8_t uart_rx_head = 0;
static volatile uint8_t uart_rx_tail = 0;

/* ---------- INIT ---------- */
void uart_init(void)
{
    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)(UBRR_VALUE & 0xFF);

    // 8N1
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

    // Enable RX, TX + RX interrupt
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
}

/* ---------- TX ---------- */
void uart_tx_byte(uint8_t b)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }
    UDR0 = b;
}

/* ---------- RX ISR ---------- */
ISR(USART_RX_vect)
{
    char c = UDR0;
    uint8_t next = (uart_rx_head + 1) % UART_RX_BUF_SIZE;
    
    if (next != uart_rx_tail)
    {
        uart_rx_buf[uart_rx_head] = c;
        uart_rx_head = next;
    }
}

/* ---------- RX API ---------- */
uint8_t uart_rx_available(void)
{
    return uart_rx_head != uart_rx_tail;
}

char uart_rx_byte(void)
{
    char c = 0;
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        if (uart_rx_head != uart_rx_tail)
        {
            c = uart_rx_buf[uart_rx_tail];
            uart_rx_tail = (uart_rx_tail + 1) % UART_RX_BUF_SIZE;
        }
    }
    return c;
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
