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
    uint8_t state_change_complete = 0;

    while (1)
    {

        switch (get_system_state())
        {
        case IDLE:
            start_input_frequnce();

            break;
        case INPUT_AWIT:
            input_frequnce(key_pressed());
            toggle_input_awit();
            break;
        case ACCESS_GRANTED:
            toggle_access();
            state_change_complete = 1;
            break;
        case ACCESS_DENIED:
            toggle_denied();
            state_change_complete = 1;
            break;

        default:
            break;
        }

        if (state_change_complete && millis_delay(3000))
        {
            reset_loop(&counter_buttons_pressed);
            toggle_idle();
            state_change_complete = 0;
        }
    }
}

void input_frequnce(uint8_t key_pressed)
{
    if ((combination_pressed[counter_buttons_pressed] = key_pressed))
    {
        counter_buttons_pressed++;
    }

    if (counter_buttons_pressed == 4)
    {

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

void start_input_frequnce()
{
    if (key_pressed() == '*')
    {
        set_system_state(INPUT_AWIT);
    }
}