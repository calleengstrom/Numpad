#include "../include/protocol.h"
#include "../include/uart.h"
#include <string.h>
#include <stdio.h>

uint8_t valid_check_protocol(char *new_pin)
{
    if ((strncmp(new_pin, "NEW PIN", 7) == 0))
    {
        return PROTOCOL_NEW_PIN;
    }
    else if (strncmp(new_pin, "RESET1", 7) == 0)
    {
        uart_puts("TRIGGER RESET ?\r\n");
        return PROTOCOL_RESET_1;
    }
    else{
        uart_puts("TRIGGER UNKNOW ?\r\n");
        return UNKOWN_PROTOCOL;
}
}
