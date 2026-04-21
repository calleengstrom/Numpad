#ifndef UTILLS_H
#define UTILLS_H

typedef enum{
    ACCESS,
    DENIED
}PIN_CHECK;


PIN_CHECK check_pin(char *pass_key , uint8_t *combination_pressed);

#endif