
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

    PORTB |= (1 << RED_LED);
    PORTB &= ~(1 << GREEN_LED);
}

//************************************ */

void button_pressed_toggle()
{
    millis_t timer = millis_get();
    
    PORTB ^= (1 << RED_LED);

    while ((millis_t)(millis_get() - timer) < 150);

    PORTB ^= (1 << RED_LED);
}

//************************************ */
void toggle_access()
{
    millis_t timer = millis_get();
    PORTB ^= (1 << GREEN_LED);

    while ((millis_t)(millis_get() - timer) < 1500);

    PORTB ^= (1 << GREEN_LED);
}

//************************************ */

void toggle_denied(){
    millis_t timer = millis_get();
    PORTB ^= (1 << RED_LED);

    while ((millis_t)(millis_get() - timer) < 1500);

    PORTB ^= (1 << RED_LED);
}

//************************************ */
