
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include "../include/pin_key.h"

static char current_pin[5];

void pin_init(char *init_pass_code)
{
    strcpy(current_pin, init_pass_code);
}

uint8_t valid_check_new_pin(char *new_pin)
{

    for (size_t i = 0; i < strlen(new_pin); i++)
    {
        if (new_pin[i] < '0' || new_pin[i] > '9')
        {
            uart_puts("only digits \r\n");
            return 0;
        }
    }
    if (strlen(new_pin) != 4)
    {
        uart_puts("To long pin must be 4 digits \r\n");
        return 0;
    }
    uart_puts("Pass key uppdated ! \r\n");
    return 1;
}

void uppdate_pin(char *new_pin)
{
    strncpy(current_pin, new_pin, 4);
}

uint8_t check_current_pin(char *input_pin)
{
    if (memcmp(input_pin, current_pin, 4) == 0)
    {
        return PIN_CORRECT;
    }
    return PIN_INVALID;
}

// void save_pin_to_eeprom(char *code, size_t pin_size)
// {

//     for (uint8_t i = 0; i < pin_size; i++)
//     {
//         eeprom_write_byte((i + 0), code[i]);
//     }
// }

// void read_pin_from_eeprom(char *code, size_t pin_size)
// {
//     for (uint8_t i = 0; i < pin_size; i++)
//     {
//         code[i] = eeprom_read_byte(i + 0);
//     }
// }