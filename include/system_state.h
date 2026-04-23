#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

typedef enum
{
    IDLE,
    INPUT_AWIT,
    ACCESS_GRANTED,
    ACCESS_DENIED,
    TIME_OUT
} SYSTEM_STATE;

void system_state_idle();
void awit_input();
void grant_access();
void deny_access();
void time_out_reached();
SYSTEM_STATE get_system_state();





#endif