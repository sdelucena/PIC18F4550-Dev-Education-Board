/* 
 * File:   optocoupled_inputs.c
 * Author: Samuel
 * 
 * LV62 PIC18F4550 Dev-Education Board
 *
 * Demonstration of the two optocoupled digital inputs.
 *
 * Input 1: RB0/AN12/INT0  - active LOW
 * Input 2: RB2/AN8/INT2   - active LOW
 *
 * Relay 1: RB3
 * Relay 2: RC0
 *
 * The optocoupled inputs are intended for isolated 12/24 Vdc
 * field signals.
 * 
 * MPLAB X IDE v6.20
 * XC8 (v3.10)
 * 
 * Created on September 22, 2026.
 */

//----------------------------------------------------------------------------//
// CONFIGURATION
//----------------------------------------------------------------------------//

// ⚠ HID BOOTLOADER: Before programming this application, set 'File' → 'Project 
//   Properties' → 'XC8 Linker' → 'Option categories' → 'Additional options'
//   → 'Codeoffset' 0x1000

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

#define input1Pin       RB0
#define input2Pin       RB2

#define INPUT_ACTIVE    0
#define INPUT_INACTIVE  1


//----------------------------------------------------------------------------//
// FUNCTION DECLARATIONS
//----------------------------------------------------------------------------//

void relay1On(void);
void relay1Off(void);
void relay2On(void);
void relay2Off(void);


//----------------------------------------------------------------------------//
// MAIN
//----------------------------------------------------------------------------//

int main(void)
{
    //--------------------------------------------------------------------//
    // DIGITAL I/O CONFIGURATION
    //--------------------------------------------------------------------//

    // Configure the ADC pins as digital I/O.
    ADCON1 = 0x0F;

    // Optocoupled inputs
    TRISBbits.RB0 = 1;
    TRISBbits.RB2 = 1;

    // Relay control outputs
    TRISBbits.RB3 = 0;
    TRISCbits.RC0 = 0;

    //--------------------------------------------------------------------//
    // INITIAL RELAY STATE
    //--------------------------------------------------------------------//

    relay1Off();
    relay2Off();

    //--------------------------------------------------------------------//
    // MAIN LOOP
    //--------------------------------------------------------------------//
    
    while(1)
    {
        // Input 1 is active LOW
        if (input1Pin == INPUT_ACTIVE)
        {
            relay1On();
        }
        else
        {
            relay1Off();
        }

        // Input 2 is active LOW
        if (input2Pin == INPUT_ACTIVE)
        {
            relay2On();
        }
        else
        {
            relay2Off();
        }
    }

    return 0;
}


//----------------------------------------------------------------------------//
// RELAY 1
//----------------------------------------------------------------------------//

void relay1On(void)
{
    LATBbits.LATB3 = 1;
}

void relay1Off(void)
{
    LATBbits.LATB3 = 0;
}


//----------------------------------------------------------------------------//
// RELAY 2
//----------------------------------------------------------------------------//

void relay2On(void)
{
    LATCbits.LATC0 = 1;
}

void relay2Off(void)
{
    LATCbits.LATC0 = 0;
}
