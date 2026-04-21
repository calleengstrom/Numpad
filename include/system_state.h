#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

typedef enum
{
    IDLE,
    INPUT_AWIT,
    ACCESS_GRANTED,
    ACCESS_DENIED
} SYSTEM_STATE;

void system_state_init();
SYSTEM_STATE get_system_state();
void set_system_state(SYSTEM_STATE new_state);

#endif