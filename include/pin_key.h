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
#include "../include/command_parser.h"
typedef enum{
    PIN_INVALID,
    PIN_CORRECT,
    WAITING,
}PIN_STATE;

PIN_STATE check_pin(char *pass_key , uint8_t *combination_pressed);


void pin_init(char *init_pass_code);

uint8_t check_current_pin(char *old_pin_input);
void uppdate_pin(char *new_pin);
uint8_t valid_check_new_pin(char *new_pin);

#endif