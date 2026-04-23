#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include "../include/keypad.h"
#include "../include/uart.h"
#include "../include/millis.h"
#include "../include/led.h"
#include "../include/system.h"
#include "../include/system_state.h"

#define INPUT_TIMER_LIMIT 5000
PIN_STATE pin_state = WAITING;
static millis_t input_timer = 0;
static uint8_t counter_buttons_pressed = 0;
static uint8_t combination_pressed[4];
static char pass_key[4] = {'1', '7', '7', '2'};
static char last_key = 0;

void run_system()
{
    uint8_t end_point_reached = 0;
    start_and_reset_system(&counter_buttons_pressed, combination_pressed,&last_key);
    while (1)
    {

        switch (get_system_state())
        {
        case IDLE:
            start_input_frequnce();
            break;

        case INPUT_AWIT:

            do
            {
                toggle_input_awit();
                pin_state = pin_input_frequnce_state(key_pressed());
                if (pin_state == PIN_CORRECT)
                {
                    uart_puts("\r\nCorrect pin\r\n");
                    grant_access();
                    break;
                }
                else if (pin_state == PIN_INVALID)
                {
                    uart_puts("\r\nInvalid pin\r\n");

                    deny_access();
                    break;
                }

            } while ((millis_get() - input_timer) < INPUT_TIMER_LIMIT);

            if (pin_state == WAITING)
            {
                uart_puts("\r\n!TIME OUT REACHED!\r\n");
                time_out_reached();
            }
            break;

        case ACCESS_GRANTED:
            toggle_access();
            uart_puts("\r\nACCESS GRANTED !\r\n");
            end_point_reached = 1;
            break;

        case ACCESS_DENIED:
            toggle_denied();
            uart_puts("\r\nACCESS DENIED !\r\n");
            end_point_reached = 1;
            break;

        case TIME_OUT:
            toggle_timeout();
            uart_puts("\r\nTIMEOUT !\r\n");
            end_point_reached = 1;
            break;
        default:
            break;
        }

        if (end_point_reached && millis_delay(3000))
        {
            start_and_reset_system(&counter_buttons_pressed, combination_pressed, &last_key);
            toggle_idle();
            end_point_reached = 0;
        }
    }
}

PIN_STATE pin_input_frequnce_state(uint8_t key_pressed)
{
    if (key_pressed && counter_buttons_pressed < 4)
    {
        combination_pressed[counter_buttons_pressed] = key_pressed;
        counter_buttons_pressed++;
        button_pressed_toggle();
        uart_puts("\r\nButton pressed\r\n");
    }

    if (counter_buttons_pressed == 4)
    {
        pin_state = check_pin(pass_key, combination_pressed);
    }
    return pin_state;
}

void start_input_frequnce()
{
    pin_state = WAITING;

    char key = key_pressed();

    if (key == '*' && key != last_key)
    {
        wait_for_no_key();
        awit_input();
        input_timer = millis_get();
        uart_puts("\r\ninput frequnce started \r\n");
    }

    last_key = key;
}
