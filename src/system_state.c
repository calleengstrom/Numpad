#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include "../include/system_state.h"
#include "../include/uart.h"
static volatile SYSTEM_STATE system_state;

void system_state_init()
{
    system_state = IDLE;
}

SYSTEM_STATE get_system_state()
{
    return system_state;
}

void set_system_state(SYSTEM_STATE new_state)
{
    system_state = new_state;
}