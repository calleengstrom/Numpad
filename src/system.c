#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include "../include/keypad.h"
#include "../include/uart.h"
#include "../include/millis.h"
#include "../include/led.h"
#include "../include/system.h"
#include "../include/utills.h"
#include "../include/keypad_logic.h"


void run_system(){
    uint8_t counter_buttons_pressed = 0;
    char pass_key[4] = {'1', '7', '7', '2'};
    uint8_t combination_pressed[4];

    while (1)
    {
        
        if ((combination_pressed[counter_buttons_pressed] = key_pressed()))
        {
            button_pressed_toggle();
            counter_buttons_pressed++;
        }


        if (counter_buttons_pressed == 4)
        {
            if (check_pin(pass_key, combination_pressed) == ACCESS)
            {
                toggle_access();
            }
            else
            {  
                toggle_denied();
            }
            counter_buttons_pressed = 0;
        }
    }

}
