#ifndef COMMANDO_EEPROM_H
#define COMMANDO_EEPROM_H
#include <stdio.h>
#define PROTOCOL_SIZE 8
#define PIN_SIZE 5
void prase_commando(char *buf,char new_pin_holder[][8]);
uint8_t valid_check_protocol(char new_pin_holder[][8]);
#endif