#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include "../include/keypad.h"
#include "../include/uart.h"
#include "../include/millis.h"
#include "../include/led.h"
#include "../include/system.h"
#include "../include/system_state.h"
#include "../include/terminal.h"
#include "../include/commando_eeprom.h"

#define INPUT_TIMER_LIMIT 5000
PIN_STATE pin_state = WAITING;

// emporm comando_new_pin -> "NEW PIN,1772,1337"
static millis_t input_timer = 0;
static uint8_t counter_buttons_pressed = 0;
static uint8_t combination_pressed[4];
static uint8_t timer_reached = 0;
static char pass_key[5] = {'1', '7', '7', '2', '\0'};

void run_system()
{
    char new_pin_holder[3][8];
    char buf[19];
    uint8_t end_point_reached = 0;
    start_and_reset_system(&counter_buttons_pressed, combination_pressed, &timer_reached);
    while (1)
    {
        switch (get_system_state())
        {
        case IDLE:
            start_input_frequnce();

            
            if (get_input(buf, sizeof(buf)))
            {
                prase_commando(buf, new_pin_holder);
            }
            if (!valid_check_protocol(new_pin_holder)){
                uart_puts("Invalid protocol \"NEW PIN\" \r\n");
                break;
            }
           
            
            break;

        case INPUT_AWIT:

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

            if ((millis_get() - input_timer) > INPUT_TIMER_LIMIT)
            {
                timer_reached = 1;
            }
            if (pin_state == WAITING && timer_reached)
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
            start_and_reset_system(&counter_buttons_pressed, combination_pressed, &timer_reached);
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
    input_timer = millis_get();

    char key = key_pressed();

    if (key == '*')
    {
        wait_for_no_key();
        awit_input();
        uart_puts("\r\ninput frequnce started \r\n");
    }
}
