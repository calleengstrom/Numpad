#ifndef LED_H
#define LED_H

#define GREEN_LED PB5
#define RED_LED PB4

void led_init();
void button_pressed_toggle();
void toggle_access();
void toggle_denied();

#endif