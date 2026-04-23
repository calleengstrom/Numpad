
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "../include/led.h"
#include "../include/millis.h"
#include "../include/uart.h"
static volatile millis_t timer_now;
static volatile millis_t timer_start;

void led_init()
{
    DDRB |= (1 << RED_LED);
    DDRB |= (1 << GREEN_LED);

    PORTB |= (1 << RED_LED);
    PORTB &= ~(1 << GREEN_LED);
    timer_start = millis_get();
}

//************************************ */

void button_pressed_toggle()
{
    timer_now = millis_get();

    PORTB ^= (1 << GREEN_LED);

    while ((millis_t)(millis_get() - timer_now) < 100)
        ;

    PORTB ^= (1 << GREEN_LED);
}

//************************************ */
void toggle_access()
{
    PORTB |= (1 << GREEN_LED);
    PORTB &= ~(1 << RED_LED);
}

//************************************ */

void toggle_denied()
{
    timer_now = millis_get();
    if ((millis_t)(timer_now - timer_start) >= 1000)
    {
        PORTB ^= (1 << RED_LED);
        timer_start = millis_get();
    }
}

//************************************ */
void toggle_idle()
{
    PORTB |= (1 << RED_LED);
    PORTB &= ~(1 << GREEN_LED);
}
//************************************ */
void toggle_input_awit()
{
    timer_now = millis_get();
    if (timer_now - timer_start > 500)
    {
        PORTB ^= (1 << RED_LED);
        timer_start = millis_get();
    }
}
//************************************ */

void toggle_timeout()
{
    uart_puts("\r\nstuck here ??\r\n");
    timer_now = millis_get();

    PORTB |= (1 << RED_LED);
    PORTB |= (1<< GREEN_LED);
    while ((millis_get() - timer_now) < 100);
    PORTB &= (1 << RED_LED);
    PORTB &= (1<< GREEN_LED);

    timer_now = millis_get();
    
    PORTB |= (1 << RED_LED);
    PORTB |= (1<< GREEN_LED);
    while ((millis_get() - timer_now) < 100);
    PORTB &= (1 << RED_LED);
    PORTB &= (1<< GREEN_LED);
    
}