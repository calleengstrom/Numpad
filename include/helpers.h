#ifndef HELPERS_H
#define HELPERS_H

typedef enum{
    PIN_INVALID,
    PIN_CORRECT,
    WAITING,
}PIN_STATE;


PIN_STATE check_pin(char *pass_key , uint8_t *combination_pressed);
void start_and_reset_system(uint8_t *counter,uint8_t *combination_pressed);
void wait_for_no_key();
#endif