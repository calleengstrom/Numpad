#ifndef KEYPAD_H
#define KEYPAD_H

char keypad_get_key(void);
char keypad_get_key_debounced(void);
void keypad_init(void);
char key_pressed();
void wait_for_no_key();
#endif