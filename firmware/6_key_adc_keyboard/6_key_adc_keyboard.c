
/*
 * File:   6_key_adc_keyboard.c
 *
 * LV62 PIC18F4550 Dev-Education Board
 *
 * Demonstration of the reusable six-key ADC keyboard.
 */

#include <xc.h>
#include "keyboard_6key.h"

#pragma config PBADEN = OFF

int main(void)
{
    unsigned char key;

    keyboardInit();

    while (1)
    {
        key = keyboardRead();

        switch (key)
        {
            case KEY_ENTER:
                /* Accept menu selection. */
                break;

            case KEY_ESCAPE:
                /* Return to previous menu. */
                break;

            case KEY_UP:
                /* Move selection up. */
                break;

            case KEY_DOWN:
                /* Move selection down. */
                break;

            case KEY_RIGHT:
                /* Move right. */
                break;

            case KEY_LEFT:
                /* Move left. */
                break;

            case KEY_NONE:
            default:
                break;
        }
    }

    return 0;
}
