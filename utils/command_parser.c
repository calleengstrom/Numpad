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

void prase_commando(char *buf, char new_pin_holder[][8])
{
    char *token = buf;
    char *index = buf;
    uint8_t size_tracker = 0;
    uint8_t token_idx = 0;

    while (*index != '\0')
    {
        if (*index == ',')
        {
            *index = '\0';
            if (token_idx == 0)
            {
                strcpy(new_pin_holder[token_idx], token);
            }
            else if (token_idx == 1)
            {
                strcpy(new_pin_holder[token_idx], token);
            }

            token_idx++;
            token = index + 1;
        }
        else if (*(index + 1) == '\0' && token_idx == 2)
        {
            strcpy(new_pin_holder[token_idx], token);
        }
        size_tracker++;
        index++;

        if ((size_tracker >= 8 && token_idx == 0) || (size_tracker > 16 && token_idx == 1) || size_tracker > 20)
        {
            uart_puts("Too long and or unknow commando \r\n");
            strcpy(new_pin_holder[0], "");
            strcpy(new_pin_holder[1], "");
            strcpy(new_pin_holder[2], "");
            break;
        }
    }
}

uint8_t valid_check_protocol(char new_pin_holder[][8])
{

    char *protocol = new_pin_holder[0];

    return (strncmp(protocol, PROTOCOL_NEW_PIN, 5) == 0);
}


