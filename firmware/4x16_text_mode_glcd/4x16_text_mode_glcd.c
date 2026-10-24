/*
 * File:   4x16_text_mode_glcd.c
 * Author: Samuel
 *
 * Board: LV62
 *
 * MCU: PIC18F4550-I/PT (TQFP-44)
 * Compiler: XC8 (v3.10)
 *
 * Created on October 24, 2026
 */


#include <xc.h>


#pragma config PBADEN = OFF


#undef _XTAL_FREQ
#define _XTAL_FREQ 48000000UL

#define GLCD_RST RE0
#define GLCD_ENABLE RE1
#define GLCD_RS RE2

#define CONTROL 0
#define DATA 1


const char boardIdentification1[] = "  === LV62 ===";
const char boardIdentification2[] = "   PIC18F4550";
const char boardIdentification3[] = "Development &";
const char boardIdentification4[] = "Education Board";

void glcdCommand(unsigned char command);
void glcdData(unsigned char data);
void glcdWriteString(unsigned char lineNumber, const char *string);
void glcdInit(void);
void backlightPwmInit(void);


void main(void) {

    ADCON1 = 0x0F;              // Configure analog-capable pins as digital I/O

    TRISD = 0b00000000;         // RD3-RD0 carry data nibbles to GLCD D7-D4.
    TRISEbits.GLCD_RST = 0;     // RE0: GLCD reset output.
    TRISEbits.GLCD_ENABLE = 0;  // RE1: GLCD enable output.
    TRISEbits.GLCD_RS = 0;      // RE2: GLCD register-select output.

    __delay_ms(100);            // Allow the GLCD supply voltage to stabilize.

    GLCD_ENABLE = 0;            // Keep the GLCD enable signal low.

    glcdInit();

    __delay_ms(50);


    while (1) {


        glcdWriteString(1, boardIdentification1);

        __delay_ms(1250);

        glcdWriteString(2, boardIdentification2);

        __delay_ms(1500);

        glcdWriteString(3, boardIdentification3);

        __delay_ms(1500);

        glcdWriteString(4, boardIdentification4);

        __delay_ms(1500);

        glcdCommand(0x01);

        __delay_ms(1500);

    }

}


////////////////////////////////////////////////////////////////////////////////
// Send a command to the GLCD over the 4-bit data bus.                         //
// In 4-bit mode, each byte is sent as a high nibble followed by a low nibble. //
// PIC RD3-RD0 connect to the GLCD D7-D4 inputs.                               //
////////////////////////////////////////////////////////////////////////////////
void glcdCommand(unsigned char command){

    unsigned char gctemp1uc,gctemp2uc;

    gctemp1uc = command;
    gctemp2uc = command;

    // Write the high nibble:
    GLCD_RS = CONTROL;
    __delay_us(20);                 // Allow the register-select signal to settle.

    gctemp1uc = gctemp1uc & 0xF0;
    gctemp1uc = gctemp1uc>>4;       // The nibble is placed on PIC PORTD bits RD3-RD0.

    GLCD_ENABLE = 1;
    PORTD = gctemp1uc;
    __delay_us(5);                  // Enable pulse width.
    GLCD_ENABLE = 0;
    __delay_us(5);
    
    // Write the low nibble:
    gctemp2uc = gctemp2uc & 0x0F;   // The nibble is placed on PIC PORTD bits RD3-RD0.

    GLCD_ENABLE = 1;
    PORTD = gctemp2uc;
    __delay_us(5);                  // Enable pulse width.
    GLCD_ENABLE = 0;
    __delay_us(5);
}
////////////////////////////////////////////////////////////////////////////////
    
    
////////////////////////////////////////////////////////////////////////////////
// Send a data byte to the GLCD over the 4-bit parallel bus.                  //
//                                                                            //
// In 4-bit mode, each byte is sent as a high nibble followed by a low nibble. //
// PIC RD3-RD0 connect to the GLCD D7-D4 inputs.                               //
////////////////////////////////////////////////////////////////////////////////
void glcdData(unsigned char data){

    unsigned char gdtemp1uc,gdtemp2uc;

    gdtemp1uc = data;
    gdtemp2uc = data;

    // Write the high nibble:
    GLCD_RS = DATA;
    __delay_us(20);                 // Allow the register-select signal to settle.

    gdtemp1uc = gdtemp1uc & 0xF0;
    gdtemp1uc = gdtemp1uc>>4;       // The nibble is placed on PIC PORTD bits RD3-RD0.

    GLCD_ENABLE = 1;
    PORTD = gdtemp1uc;
    __delay_us(5);                  // Enable pulse width.
    GLCD_ENABLE = 0;
    __delay_us(5);                  // Data hold time.

    // Write the low nibble:
    gdtemp2uc = gdtemp2uc & 0x0F;   // The nibble is placed on PIC PORTD bits RD3-RD0.

    GLCD_ENABLE = 1;
    PORTD = gdtemp2uc;
    __delay_us(5);                  // Enable pulse width.
    GLCD_ENABLE = 0;
    __delay_us(5);                  // Data hold time.
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Write a null-terminated string to a selected display line.                 //
// The function writes up to 20 characters and pads shorter strings with spaces.//
// ST7920 text-mode DDRAM addresses select the four display lines.              //
////////////////////////////////////////////////////////////////////////////////
void glcdWriteString(unsigned char lineNumber, const char *string){

    unsigned char w;

    // Select the DDRAM address for the requested display line.
    switch (lineNumber) {
    case 1: glcdCommand(0x80); break;
    case 2: glcdCommand(0x90); break;
    case 3: glcdCommand(0x88); break;
    case 4: glcdCommand(0x98); break;
    default: return;  // Ignore invalid line numbers.
    }


    GLCD_RS = DATA;

    for (w = 0; w < 16; w++) {
        if (string[w] != '\0') {
            glcdData(string[w]);
        } else {
            break;
        }
    }

    while (w < 16) {   
        glcdData(' ');
        w++;
    }
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Initialize the ST7920 controller for 4-bit text mode.                      //
////////////////////////////////////////////////////////////////////////////////
void glcdInit(void){

    // Initialize the ST7920 controller.

    GLCD_RST = 0;            // Assert GLCD reset.
    __delay_ms(80);          // Allow the required startup time for 4-bit interfacing.
    GLCD_RST = 1;

    __delay_ms(50);          // Allow the controller to complete its startup sequence.

    glcdCommand(0b00100000); // Function Set: 4-bit interface, basic instruction set.
    __delay_us(200);         // Wait for the controller to process the instruction.

    glcdCommand(0b00100000); // Function Set: 4-bit interface, basic instruction set.
    __delay_us(200);         // Wait for the controller to process the instruction.

    glcdCommand(0b00001100); // Display Control: display on, cursor off, and cursor blink off.
    __delay_us(200);         // Wait for the controller to process the instruction.

    glcdCommand(0b00000001); // Clear the display.
    __delay_ms(20);          // Clear-display commands require a longer delay.

    glcdCommand(0b00000110); // Entry Mode: increment the address; do not shift the display.
    __delay_us(200);         // Wait for the controller to process the instruction.

    glcdCommand(0b00000010); // Return Home moves the cursor to the origin.

    backlightPwmInit();      // Turn on the GLCD backlight at near-maximum brightness.
}
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Configure CCP2 PWM to control the GLCD backlight brightness.               //
////////////////////////////////////////////////////////////////////////////////
void backlightPwmInit(void){

    PR2 = 0xFF;             // Set the PWM period register.
    CCPR2L = 0xF0;          // Set the backlight duty cycle near maximum.
    TRISCbits.RC1 = 0;      // Configure RC1/CCP2 as an output.
    T2CON = 0b00000010;     // Configure Timer2 prescaler; keep Timer2 off initially.
    TMR2ON = 1;
    CCP2CON = 0b00111100;   // Select PWM mode and set the duty-cycle LSBs.
}
//////////////////////////////////////////////////////////////////////////////// 
