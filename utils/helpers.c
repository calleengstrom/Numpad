#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include <string.h>
#include "../include/helpers.h"
#include "../include/uart.h"
#include "../include/system_state.h"
#include "../include/millis.h"
#include "../include/keypad.h"
PIN_STATE check_pin(char *pass_key , uint8_t *combination_pressed)
{
    if (memcmp(pass_key, combination_pressed,4)==0)
    {
        return PIN_CORRECT;
    }
    return PIN_INVALID;
}


// void start_and_reset_system(uint8_t *counter,uint8_t *combination_pressed, uint8_t *timer_reached){
//     uart_puts("\r\nRESTING\r\n");
//     wait_for_no_key();
//     memset(combination_pressed, 0, 4);
//     *counter = 0;
//     *timer_reached = 0;
//     system_state_idle();
//     uart_puts("\r\nAwiat start frequnce \r\n");
// }

void wait_for_no_key()
{
    while (key_pressed() != 0)
        ;
}