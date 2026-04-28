#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <string.h>
#include "../include/uart.h"
#include "../include/commando_eeprom.h"
static volatile uint8_t idx;
static char protocol_new_pin[] = "NEW PIN,";

void prase_eeporm(char *buf)
{
    char *token = buf;
    char *index = buf;
    char *protocol = NULL;
    char *old_pin = NULL;
    char *new_pin = NULL;
    uint8_t token_idx = 0;

    while (*index != '\0')
    {
        if (*index == ',')
        {
            *index = '\0';
            if (token_idx == 0)
            {
                protocol = token;
            }
            else if (token_idx == 1)
            {
                old_pin = token;
            }

            token_idx++;
            token = index + 1;
        }
        else if (*(index + 1) == '\0' && token_idx == 2)
        {
            new_pin = token;
        }

        index++;
    }

    uart_puts("Protocol : ");
    uart_puts(protocol);
    uart_puts("\n\r");

    uart_puts("Old pin : ");
    uart_puts(old_pin);
    uart_puts("\n\r");

    uart_puts("New pin : ");
    uart_puts(new_pin);
    uart_puts("\n\r");
}

// void save_code_to_eeprom(char *code, size_t pin_size) {
//     for (uint8_t i = 0; i <  pin_size ; i++) {
//         eeprom_write_byte((i + 0), code[i]); // Skriv till EEPROM från adress 0 till 3
//     }
// }

// void read_code_from_eeprom(char *code, size_t pin_size) {
//     for (uint8_t i = 0; i <  pin_size ; i++) {
//         code[i] = eeprom_read_byte(i + 0); // Läs från samma adress
//     }
// }new pin