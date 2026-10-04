/* 
 * File:   4_digit_7seg_display.c
 * Author: Samuel
 * LV62 PIC18F4550 Dev-Education Board
 *
 * The display consists of four independent HEF4543
 * BCD-to-7-segment latch/decoder/drivers.
 *
 * BCD data:
 *     RD3 RD2 RD1 RD0
 *      D   C   B   A
 *
 * Latch control:
 *     RD7 -> Thousands
 *     RD6 -> Hundreds
 *     RD5 -> Tens
 *     RD4 -> Units
 *
 * Latch Disable:
 *     0 = disabled / normal state
 *     1 = enable latch update
 *
 * To write a digit:
 *     1. Put its BCD value on RD3..RD0.
 *     2. Set the corresponding latch control to 1.
 *     3. Wait 100 us.
 *     4. Return the latch control to 0.
 *
 * The example implements a four-digit counter with
 * a resolution of 1/4 second.
 * 
 * Demonstration of the 4 digit 7 segment display.
 *
 * MPLAB X IDE v6.20
 * XC8 (v3.10)
 * 
 * Created on October 3rd, 2026.
 */

//----------------------------------------------------------------------------//
// CONFIGURATION
//----------------------------------------------------------------------------//

//   HID BOOTLOADER: Before programming this application, set 'File' / 'Project 
//   Properties' / 'XC8 Linker' / 'Option categories' / 'Additional options'
//   / 'Codeoffset' 0x1000

#pragma config PBADEN = OFF


//----------------------------------------------------------------------------//
// INCLUDES
//----------------------------------------------------------------------------//

#include <xc.h>


//----------------------------------------------------------------------------//
// DEFINES
//----------------------------------------------------------------------------//

#undef _XTAL_FREQ
#define _XTAL_FREQ 48000000UL


/* -------------------------------------------------------------------------- */
/* Digit definitions                                                          */
/* -------------------------------------------------------------------------- */

#define THOUSANDS   0
#define HUNDREDS    1
#define TENS        2
#define UNITS       3


/* -------------------------------------------------------------------------- */
/* Function prototypes                                                        */
/* -------------------------------------------------------------------------- */

void displayInit(void);
void displayDigit(unsigned char digit, unsigned char value);
void displayNumber(unsigned int number);


/* -------------------------------------------------------------------------- */
/* Main                                                                       */
/* -------------------------------------------------------------------------- */

int main(void)
{
    unsigned int counter = 0; 

    displayInit();

    displayNumber(counter);

    while (1)
    {
        __delay_ms(250);

        counter++;

        if (counter > 9999)
            counter = 0;

        displayNumber(counter);
    }

    return 0;
}


void displayInit (void)
{
    unsigned int counter = 0;

    //--------------------------------------------------------------------//
    // DIGITAL I/O CONFIGURATION
    //--------------------------------------------------------------------//
    
    /*
     * All analog-capable pins are configured as digital I/O.
     * (Configure the ADC pins as digital I/O)
     */
    ADCON1 = 0x0F;

   /*
    * PORTD:
    *
    * RD7..RD4: Latch Disable controls
    * RD3..RD0: BCD data bus
    */
    TRISD = 0b00000000;

    /*
     * All latch controls are normally LOW.
     */
    LATD = 0b00000000; 

    /*
     * Initialize the display.
     */
    displayNumber(counter);
}


/* -------------------------------------------------------------------------- */
/* Write one digit                                                            */
/* -------------------------------------------------------------------------- */

void displayDigit(unsigned char digit, unsigned char value)
{
    /*
     * Put the BCD value on RD3..RD0.
     *
     * Only values 0..9 are valid BCD digits.
     */

    LATD = value & 0x0F;
    
    
    /*
     * Select the appropriate HEF4543 latch.
     *
     * Latch Disable is normally LOW.
     * A HIGH pulse allows the new BCD value to be latched.
     */
    switch (digit)
    {
        case THOUSANDS:
            LATDbits.LATD7 = 1;
            __delay_us(100);
            LATDbits.LATD7 = 0;
            break;

        case HUNDREDS:
            LATDbits.LATD6 = 1;
            __delay_us(100);
            LATDbits.LATD6 = 0;
            break;

        case TENS:
            LATDbits.LATD5 = 1;
            __delay_us(100);
            LATDbits.LATD5 = 0;
            break;

        case UNITS:
            LATDbits.LATD4 = 1;
            __delay_us(100);
            LATDbits.LATD4 = 0;
            break;

        default:
            /*
             * Invalid digit number.
             * Do nothing.
             */
            break;
    }
}


/* -------------------------------------------------------------------------- */
/* Display a four-digit number                                                */
/* -------------------------------------------------------------------------- */

void displayNumber(unsigned int number)
{

    /*
     * Extract the four decimal digits.
     */

    unsigned char thousands = 0;
    while(number >= 1000){
        number -= 1000;
        thousands++;
    }
    
    unsigned char hundreds = 0;
    while(number >= 100){
        number -= 100;
        hundreds++;
    }
    
    unsigned char tens = 0;
    while(number >= 10){
        number -= 10;
        tens++;
    }
    
    unsigned char units = number;
    
    
    /*
     * Write one digit at a time.
     *
     * RD3..RD0 carries only the BCD value
     * of the digit currently being written.
     */
    displayDigit(THOUSANDS, thousands);
    displayDigit(HUNDREDS,  hundreds);
    displayDigit(TENS,      tens);
    displayDigit(UNITS,     units);
}
