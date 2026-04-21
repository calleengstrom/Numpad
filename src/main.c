#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include "../include/keypad.h"
#include "../include/uart.h"
#include "../include/millis.h"
#include "../include/led.h"

int main(void)
{
    keypad_init();

    /* 9600 baud vid 16 MHz */
    uart_init(103);
    millis_init();
    led_init();
    sei();
    uart_puts("System startat\r\n");
    uint8_t counter_buttons_pressed = 0;
    char pass_key[4] = {'1', '7', '7', '2'};

    uint8_t combination_pressed[4];

    while (1)
    {
        char key = keypad_get_key_debounced();

        if (counter_buttons_pressed <= 4)
        {
            if (key != 0)
            {
                uart_puts("Tryckt: ");
                uart_putchar(key);
                uart_puts("\r\n");
                toggle_red();
                combination_pressed[counter_buttons_pressed] = key;
                uart_puts("Combination slagen : \r\n");
                for (uint8_t i = 0; i < counter_buttons_pressed+1; i++)
                {
                    uart_putchar(combination_pressed[i]);
                }
                
                counter_buttons_pressed++;
            }
        }
        else{
            counter_buttons_pressed = 0;
        }
        


    }
}