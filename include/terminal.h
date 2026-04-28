#ifndef TERMINAL_H
#define TERMINAL_H
#include <avr/io.h>
uint8_t get_input(char *buf, size_t buf_size);
uint8_t valid_input(char *buf, size_t buf_size);
#endif