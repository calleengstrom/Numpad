#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H
#include <stdio.h>
#include "../include/new_pin_holder.h"
#define PROTOCOL_SIZE 8
#define PIN_SIZE 5
void prase_commando(char *buf,NEW_PIN_HOLDER *new_pin_holder);
uint8_t valid_check_protocol(char *new_pin);

#endif