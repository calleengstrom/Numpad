
#include "../include/pin_key.h"






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