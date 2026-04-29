#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <string.h>
#include "../include/uart.h"
#include "../include/command_parser.h"
static volatile uint8_t idx;
#define PROTOCOL_NEW_PIN "NEW PIN"

void prase_commando(char *buf, NEW_PIN_HOLDER *new_pin_holder)
{
    char *token = buf;
    char *index = buf;
    uint8_t size_tracker = 0;
    uint8_t token_idx = 0;

    while (*index != '\0')
    {
        if (*index == ';')
        {
            *index = '\0';
            if (token_idx == 0)
            {
                strcpy(new_pin_holder->protocol, token);
            }
            else if (token_idx == 1)
            {
                strcpy(new_pin_holder->old_pin, token);
            }

            token_idx++;
            token = index + 1;
        }
        else if (*(index + 1) == '\0' && token_idx == 2)
        {
            strcpy(new_pin_holder->new_pin, token);
        }
        size_tracker++;
        index++;

        if ((size_tracker >= 8 && token_idx == 0) || (size_tracker > 16 && token_idx == 1) || size_tracker > 20)
        {
            uart_puts("Too long and or unknow commando \r\n");
            break;
        }
    }
}

uint8_t valid_check_protocol(char *new_pin)
{
    return (strncmp(new_pin, PROTOCOL_NEW_PIN, 6) == 0);
}


