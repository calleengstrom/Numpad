#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include "../include/system_state.h"
#include "../include/uart.h"
static volatile SYSTEM_STATE system_state;

void system_state_idle()
{
    system_state = IDLE;
}

void awit_input(){
    system_state = INPUT_AWIT;
}

void time_out_reached()
{
    system_state = TIME_OUT;
}

void grant_access()
{
    system_state = ACCESS_GRANTED;
}

void deny_access()
{
    system_state = ACCESS_DENIED;
}

SYSTEM_STATE get_system_state()
{
    return system_state;
}