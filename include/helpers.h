#ifndef HELPERS_H
#define HELPERS_H

typedef enum{
    ACCESS,
    DENIED
}PIN_CHECK;


PIN_CHECK check_pin(char *pass_key , uint8_t *combination_pressed);
void reset_loop(uint8_t *counter);

#endif