#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <string.h>
#include "../include/uart.h"
#include "../include/commando_eeprom.h"
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

uint8_t check_old_pin(char *old_pin_input,char *current_pin){
    return(strncmp(old_pin_input,current_pin,5) == 0);
        
    
}

uint8_t valid_check_new_pin(char *new_pin){
    
    for (size_t i = 0; i < strlen(new_pin); i++)
    {
        if (new_pin[i] < '0' || new_pin[i] >  '9')
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


void uppdate_pin(char *new_pin,char *current_pin){
    strncpy(current_pin,new_pin,5);
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
    // }