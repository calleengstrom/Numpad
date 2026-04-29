#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <string.h>
#include "../include/keypad.h"
#include "../include/uart.h"
#include "../include/millis.h"
#include "../include/led.h"
#include "../include/system.h"
#include "../include/system_state.h"
#include "../include/terminal.h"
#include "../include/command_parser.h"
#include "../include/pin_key.h"
#define INPUT_TIMER_LIMIT 5000
PIN_STATE pin_state = WAITING;
static millis_t input_timer = 0;
static uint8_t counter_buttons_pressed = 0;
static char combination_pressed[5];
static uint8_t timer_reached = 0;
static char new_pin_holder[3][8];
static char buf[19];

void run_system()
{

    uint8_t end_point_reached = 0;
    start_and_reset_system();
    while (1)
    {
        switch (get_system_state())
        {
            // IDLE  *************************************************************************** IDLE/
        case IDLE:
            start_input_frequnce();

            if (get_input(buf, sizeof(buf)))
            {
                prase_commando(buf, new_pin_holder);
                if (valid_check_protocol(new_pin_holder))
                {
                    uart_puts("Entering Change pin \r\n");
                    change_pin();
                    break;
                }
                else
                    uart_puts("Unknnow commadno \r\n");
            }

            break;

            // INPUT_AWIT  *************************************************************************** INPUT_AWIT/

        case INPUT_AWIT:

            led_blink_red();
            pin_state = pin_input_frequnce_state(key_pressed());
            if (PIN_CORRECT == pin_state)
            {
                uart_puts("\r\nCorrect pin\r\n");
                grant_access();
                break;
            }
            else if (PIN_INVALID == pin_state)
            {
                uart_puts("\r\nInvalid pin\r\n");
                deny_access();
                break;
            }

            if ((millis_get() - input_timer) > INPUT_TIMER_LIMIT)
            {
                timer_reached = 1;
            }
            if (WAITING == pin_state && timer_reached)
            {
                uart_puts("\r\n!TIME OUT REACHED!\r\n");
                time_out_reached();
            }
            break;

            // ACCESS_GRANTED  *************************************************************************** ACCESS_GRANTED/

        case ACCESS_GRANTED:
            led_green_on();
            uart_puts("\r\nACCESS GRANTED !\r\n");
            end_point_reached = 1;
            break;

            // ACCESS_DENIED  *************************************************************************** CCESS_DENIED/

        case ACCESS_DENIED:
            led_red_and_green_off();
            uart_puts("\r\nACCESS DENIED !\r\n");
            end_point_reached = 1;
            break;

            // TIME_OUT  *************************************************************************** TIME_OUT/

        case TIME_OUT:
            led_red_and_green_on();
            uart_puts("\r\nTIMEOUT !\r\n");
            end_point_reached = 1;
            break;

            // CHANGE_PIN  *************************************************************************** CHANGE_PIN/

        case CHANGE_PIN:
        {
            led_red_and_green_off();
            if (PIN_CORRECT == check_current_pin(new_pin_holder[1]))
            {
                uart_puts("correct key \r\n");
                if (valid_check_new_pin(new_pin_holder[2]))
                    uppdate_pin(new_pin_holder[2]);
            }
            else uart_puts("ERROR ! INVALID INPUT \r\n");
            end_point_reached = 1;
            break;
        }

            // default  *************************************************************************** default/
        default:
            break;
        }

        if (end_point_reached)
        {
            start_and_reset_system();
            led_red_on();
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
        led_toggle_green();
        uart_puts("\r\nButton pressed\r\n");
    }

    if (counter_buttons_pressed == 4)
    {
        combination_pressed[counter_buttons_pressed] = '\0';
        pin_state = check_current_pin(combination_pressed);
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

void start_and_reset_system()
{
    uart_puts("\r\nRESTING\r\n");
    millis_delay(3000);
    wait_for_no_key();
    memset(combination_pressed, 0, 4);
    counter_buttons_pressed = 0;
    timer_reached = 0;
    memset(new_pin_holder[0], '\0', 8);
    memset(new_pin_holder[1], '\0', 8);
    memset(new_pin_holder[2], '\0', 8);
    strcpy(buf, "\0");
    system_state_idle();
    uart_puts("\r\nAwiat start frequnce \r\n");
}
