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


void pin_init(char *init_pass_code);
void uppdate_pin(char *new_pin);

uint8_t check_current_pin(char *old_pin_input);
uint8_t valid_check_new_pin(char *new_pin);

// void save_pin_to_eeprom(char *code, size_t pin_size);
// void read_pin_from_eeprom(char *code, size_t pin_size);
#endif