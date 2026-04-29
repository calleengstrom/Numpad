#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include "../include/keypad.h"
#include "../include/uart.h"
#include "../include/millis.h"
#include "../include/led.h"
#include "../include/system.h"
#include "../include/command_parser.h"
#include "../include/system_state.h"
#include "../include/pin_key.h"

int main(void)
{
    keypad_init();


    uart_init();
    millis_init();
    led_init();
    uart_puts("System startat\r\n");
    set_state_idle();
    sei();
    char check_pin[5];
    read_pin_from_eeprom(check_pin,5);
    if (!valid_check_new_pin(check_pin))
    {
        reset_pin();
    }
    run_system();
}