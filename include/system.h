#ifndef SYSTEM_H
#define SYSTEM_H
#include "./helpers.h"

void run_system();
PIN_STATE pin_input_frequnce_state(uint8_t key_pressed);
void start_input_frequnce();
void time_out_reached();
void grant_access();
void deny_access();
void start_and_reset_system();
#endif