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
#include "../include/helpers.h"
#include "../include/system_state.h"

int main(void)
{
    keypad_init();

    /* 9600 baud vid 16 MHz */
    uart_init(103);
    millis_init();
    led_init();
    uart_puts("System startat\r\n");
    system_state_init();
    sei();
    run_system();
}