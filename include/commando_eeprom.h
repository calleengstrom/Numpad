#ifndef COMMANDO_EEPROM_H
#define COMMANDO_EEPROM_H
#include <stdio.h>
#define PROTOCOL_SIZE 8
#define PIN_SIZE 5
void prase_commando(char *buf,char new_pin_holder[][8]);
uint8_t valid_check_protocol(char new_pin_holder[][8]);
uint8_t check_old_pin(char *old_pin_input,char *current_pin);
void uppdate_pin(char *new_pin,char *current_pin);
uint8_t valid_check_new_pin(char *new_pin);
#endif