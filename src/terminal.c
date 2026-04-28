#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include <stdio.h>
#include "../include/uart.h"


uint8_t get_input(char *buf, size_t buf_size)
{
    if (!uart_rx_available())
    {
        return 0;
    }

    static uint8_t idx = 0;
    char c = uart_rx_byte();
    if (idx < buf_size - 1)
    {
        if (c == '\r' || c == '\n')
        {
            if (idx > 0)
            {

                buf[idx] = '\0';
                uart_puts("Your input :");
                uart_puts(buf);
                uart_puts("\r\n");
                idx = 0;
                return 1;
            }

            idx = 0;
            return 1;
        }
        else
        {
            buf[idx++] = c;
            return 0;
        }
    }
    else
    {
        buf[idx] = '\0';
        idx = 0;
        uart_puts("To long commando");
    }

    return 0;
}