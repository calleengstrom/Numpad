
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

void led_toggle_green()
{
    timer_now = millis_get();

    PORTB ^= (1 << GREEN_LED);

    while ((millis_t)(millis_get() - timer_now) < 100)
        ;

    PORTB ^= (1 << GREEN_LED);
}

//************************************ */
void led_green_on()
{
    PORTB |= (1 << GREEN_LED);
    PORTB &= ~(1 << RED_LED);
}

//************************************ */

void led_red_and_green_off()
{
    PORTB &= ~(1 << GREEN_LED);
    PORTB &= ~(1 << RED_LED);

}

//************************************ */
void led_red_on()
{
    PORTB |= (1 << RED_LED);
    PORTB &= ~(1 << GREEN_LED);
}
//************************************ */
void led_blink_red()
{
    timer_now = millis_get();
    if (timer_now - timer_start > 500)
    {
        PORTB ^= (1 << RED_LED);
        timer_start = millis_get();
    }
}
//************************************ */

void led_red_and_green_on()
{
    PORTB |= (1 << RED_LED);
    PORTB |= (1 << GREEN_LED);
}