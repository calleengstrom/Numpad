#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

typedef enum
{
    IDLE,
    INPUT_AWIT,
    ACCESS_GRANTED,
    ACCESS_DENIED,
    TIME_OUT,
    CHANGE_PIN,
    RESET_PIN,
} SYSTEM_STATE;

void set_state_idle();
void set_state_awit_input();
void set_state_grant_access();
void set_state_deny_access();
void set_state_change_pin();
void set_state_time_out();
void set_state_reset_pin();
SYSTEM_STATE get_system_state();





#endif