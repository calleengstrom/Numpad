#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>

uint8_t get_input(char *buf)
{
    if (!uart_rx_available())
    {
        return 0;
    }
    
    static uint8_t idx = 0;
    char c = uart_rx_byte();

    // ENTER avslutar kommado
    if (c == '\r' || c == '\n')
    {

        if (idx > 0)
        {

            buf[idx] = '\0';
            uart_print_str("Your input :");
            uart_print_str(buf);
            uart_print_str("\r\n");
            idx = 0;
            return 1;   // <-- färdigt
        }

        idx = 0;
        return 0;
    }
    else if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) && idx < 2)
    {
        // gör till versal
        if (c >= 'a' && c <= 'z')
            c -= 32;

        buf[idx++] = c;
    }
    return 0;
}