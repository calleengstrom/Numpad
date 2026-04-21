#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "../include/keypad.h"

/*
    4x4 keypad
    Rader:    PD2, PD3, PD4, PD5   -> outputs
    Kolumner: PB0, PB1, PB2, PB3   -> inputs with pull-up

    Layout:
    1 2 3 A
    4 5 6 B
    7 8 9 C
    * 0 # D
*/

static const char keypad_map[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void keypad_init(void)
{
    /* PD2-PD5 som utgångar */
    DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);

    /* Alla rader HIGH initialt */
    PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);

    /* PB0-PB3 som ingångar */
    DDRB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3));

    /* Aktivera pull-up på kolumner */
    PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3);
}

static void keypad_set_all_rows_high(void)
{
    PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);
}

static void keypad_set_row_low(uint8_t row)
{
    keypad_set_all_rows_high();

    switch (row)
    {
        case 0:
            PORTD &= ~(1 << PD2);
            break;
        case 1:
            PORTD &= ~(1 << PD3);
            break;
        case 2:
            PORTD &= ~(1 << PD4);
            break;
        case 3:
            PORTD &= ~(1 << PD5);
            break;
        default:
            break;
    }
}

static uint8_t keypad_read_column(void)
{
    if (!(PINB & (1 << PB0))) return 0;
    if (!(PINB & (1 << PB1))) return 1;
    if (!(PINB & (1 << PB2))) return 2;
    if (!(PINB & (1 << PB3))) return 3;

    return 0xFF;
}

char keypad_get_key(void)
{
    uint8_t row;
    uint8_t col;

    for (row = 0; row < 4; row++)
    {
        keypad_set_row_low(row);

        /* kort stabiliseringstid */
        _delay_us(5);

        col = keypad_read_column();
        if (col != 0xFF)
        {
            return keypad_map[row][col];
        }
    }

    return 0;
}

char keypad_get_key_debounced(void)
{
    char key = keypad_get_key();

    if (key != 0)
    {
        _delay_ms(20);

        if (key == keypad_get_key())
        {
            /* vänta tills knappen släpps */
            while (keypad_get_key() != 0)
            {
                _delay_ms(5);
            }

            return key;
        }
    }

    return 0;
}

uint8_t key_pressed(){
    return keypad_get_key_debounced();
}