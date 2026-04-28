#ifndef LED_H
#define LED_H

#define GREEN_LED PB5
#define RED_LED PB4

void led_init();
void led_toggle_green();
void led_green_on();
void led_red_and_green_off();
void led_red_on();
void led_blink_red();
void led_red_and_green_on();

#endif