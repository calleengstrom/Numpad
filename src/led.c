
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "../include/led.h"
#include "../include/millis.h"
#include "../include/uart.h"


void led_init()
{
    DDRB |= (1 << RED_LED);
    DDRB |= (1 << GREEN_LED);

    PORTB &= ~(1 << RED_LED);
    PORTB &= ~(1 << GREEN_LED);
}

void toggle_red()
{
    millis_t timer = millis_get();
    PORTB |= (1<<RED_LED);
    // uart_puts("Toggle on \r\n");
    while ((millis_t)(millis_get() - timer) < 150){

    }
    // uart_puts("Toggle off \r\n");
    
    PORTB ^= (1<<RED_LED);
}

void toggle_green(){
      millis_t timer = millis_get();
    PORTB ^= (1<<GREEN_LED);
    uart_puts("Toggle on \r\n");
    while ((millis_t)(millis_get() - timer) >= 150){

    }
    uart_puts("Toggle off \r\n");
    
    PORTB ^= (1<<GREEN_LED);
}