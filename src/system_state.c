#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include "../include/system_state.h"
#include "../include/uart.h"
static volatile SYSTEM_STATE system_state;

void set_state_idle()
{
    system_state = IDLE;
}

void set_state_awit_input(){
    system_state = INPUT_AWIT;
}

void set_state_time_out()
{
    system_state = TIME_OUT;
}

void set_state_grant_access()
{
    system_state = ACCESS_GRANTED;
}

void set_state_deny_access()
{
    system_state = ACCESS_DENIED;
}
void set_state_change_pin(){
    system_state = CHANGE_PIN;
}

void set_state_reset_pin(){
    system_state = RESET_PIN;
}

SYSTEM_STATE get_system_state()
{
    return system_state;
}