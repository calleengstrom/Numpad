#ifndef PIN_KEY_H
#define PIN_KEY_H
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <string.h>
#include "../include/uart.h"
#include "../include/commando_eeprom.h"
typedef struct
{
 char *pass_key;
} PIN_KEY;

uint8_t check_old_pin(char *old_pin_input,char *current_pin);
void uppdate_pin(char *new_pin,char *current_pin);
uint8_t valid_check_new_pin(char *new_pin);

#endif