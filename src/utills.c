#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include <string.h>
#include "../include/utills.h"
#include "../include/uart.h"
#include "../include/system_state.h"
PIN_CHECK check_pin(char *pass_key , uint8_t *combination_pressed)
{
    if (memcmp(pass_key, combination_pressed,4)==0)
    {
        return ACCESS;
    }
    return DENIED;
}


void reset_loop(uint8_t *counter){
    *counter == 0;
    set_system_state(IDLE);
}