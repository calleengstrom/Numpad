#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include "../include/keypad.h"
#include "../include/uart.h"
#include "../include/millis.h"
#include "../include/led.h"
#include "../include/system.h"
#include "../include/helpers.h"
#include "../include/system_state.h"

static uint8_t counter_buttons_pressed = 0;
static char pass_key[4] = {'1', '7', '7', '2'};
static uint8_t combination_pressed[4];

void run_system()
{

    while (1)
    {

        switch (get_system_state())
        {
        case IDLE:

            break;
        case INPUT_AWIT:
            input_frequnce();
            break;
        case ACCESS_GRANTED:
            toggle_access();
            reset_loop(&counter_buttons_pressed);
            break;
        case ACCESS_DENIED:

            break;

        default:
            break;
        }
    }
}

void input_frequnce()
{
    if ((combination_pressed[counter_buttons_pressed] = key_pressed()))
    {
        button_pressed_toggle();
        counter_buttons_pressed++;
    }

    if (counter_buttons_pressed == 4)
    {
        for (uint8_t i = 0; i < counter_buttons_pressed; i++)
        {
            
            uart_putchar(combination_pressed[i]);
        }
        
        switch (check_pin(pass_key, combination_pressed))
        {
        case ACCESS:
            set_system_state(ACCESS_GRANTED);
            break;
        case DENIED:
            set_system_state(ACCESS_DENIED);
            break;
        default:
            break;
        }
        
    }
}