
#ifndef KEYBOARD_6KEY_H
#define KEYBOARD_6KEY_H

/*
 * LV62 six-key ADC keyboard driver.
 *
 * ADC input: RA2 / AN2
 * Buzzer:    RB4, active LOW
 */

#define KEY_NONE    0
#define KEY_ENTER   1
#define KEY_ESCAPE  2
#define KEY_UP      3
#define KEY_DOWN    4
#define KEY_RIGHT   5
#define KEY_LEFT    6

void keyboardInit(void);
unsigned char keyboardRead(void);

#endif
