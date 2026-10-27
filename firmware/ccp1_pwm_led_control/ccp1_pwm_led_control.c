/*
 *
 * Project name: ccp1_pwm_led_control
 * File:         ccp1_pwm_led_control.c
 * Author: Samuel
 * Board:  LV62
 * Device: PIC18F4550
 * Clock:  48 MHz
 * IDE:      MPLAB X 6.20
 * Compiler: XC8 v3.10
 * 
 * Created on 27 de Outubro de 2026, 18:31
 * 
 * Demonstration:
 *   CCP1 generates a PWM signal on RC2. The firmware cycles through
 *   five duty-cycle settings: 0%, 25%, 50%, 75%, and 100%.
 *
 * Hardware:
 *   - RC2/CCP1 drives the on-board orange LED through its resistor.
 *   - The LV62 jumper can connect CCP1 to the BUK9614 MOSFET gate.
 *
 * IMPORTANT:
 *   In MPLAB X, set XC8 Linker -> Code Offset to 0x1000 to preserve
 *   the LV62 HID bootloader.
 * 
 * As with the previous LV62 examples, remember to set XC8 Linker ? Code
 *    Offset = 0x1000 to preserve the HID bootloader.
 * 
 */


#include <xc.h>

#pragma config PBADEN = OFF

#define _XTAL_FREQ 48000000UL

#define PWM_PERIOD_COUNTS (4UL * (PR2 + 1UL))

#define PWM_PR2_VALUE       74U

static void pwm1_init(void);
static void pwm1_setDutyPercent(unsigned char percent);

void main(void)
{
    static const unsigned char dutySteps[] = {0, 25, 50, 75, 100};
    unsigned char i;

    /*
     * RC2 is the CCP1/PWM output pin on the PIC18F4550.
     * Keep the LV62 CCP1-to-MOSFET jumper connected if testing the
     * external MOSFET output. The on-board LED is also driven by RC2.
     */
    TRISCbits.RC2 = 0;

    pwm1_init();

    while (1)
    {
        /*
         * sizeof(array) returns its total size in bytes.
         * Dividing by the size of one element gives the element count,
         * so this loop still works if dutySteps is later resized.
         */
        for (i = 0; i < (sizeof(dutySteps) / sizeof(dutySteps[0])); i++)
        {
            pwm1_setDutyPercent(dutySteps[i]);
            __delay_ms(1000);
        }
    }
}


static void pwm1_init(void)
{
    /*
     * Configure Timer2 while it is stopped.
     *
     * T2CON = 0x01:
     *   TMR2ON = 0: Timer2 off during setup
     *   T2CKPS = 01: prescaler 1:4
     *   Postscaler = 1:1
     */
    T2CON = 0x01;

    /*
     * PWM frequency = Fosc / [4 * (PR2 + 1) * Timer2 prescaler]
     *               = 48 MHz / [4 * (74 + 1) * 4]
     *               = 40 kHz.
     */
    PR2 = PWM_PR2_VALUE;

    /* Start with a zero duty-cycle value. */
    CCPR1L = 0;

    /*
     * CCP1CON = 0x0C selects PWM mode (CCP1M = 1100).
     * DC1B1:DC1B0, the two low-order duty-cycle bits, start at 00.
     */
    CCP1CON = 0x0C;

    /* Clear the Timer2 interrupt flag before starting the timer. */
    PIR1bits.TMR2IF = 0;

    /* Start Timer2; CCP1 PWM operation can now run. */
    T2CONbits.TMR2ON = 1;
}


static void pwm1_setDutyPercent(unsigned char percent)
{
    unsigned int duty10;

    /* Limit the requested percentage to the valid range. */
    if (percent > 100U)
    {
        percent = 100U;
    }

    /*
     * Convert the requested percentage to the 10-bit PWM duty value.
     * PWM_PERIOD_COUNTS is 4 * (PR2 + 1), or 300 for PR2 = 74.
     *
     * Example: at 50%, duty10 = (300 * 50) / 100 = 150.
     */
    duty10 = (unsigned int)
        ((PWM_PERIOD_COUNTS * (unsigned long)percent) / 100UL);

    /*
     * The 10-bit duty value is split across two registers:
     *   - CCPR1L receives bits 9:2 (the upper eight bits).
     *   - CCP1CONbits.DC1B receives bits 1:0 (the lower two bits).
     *
     * DC1B is a two-bit field (DC1B1:DC1B0), not a single bit.
     */
    CCPR1L = (unsigned char)(duty10 >> 2);
    CCP1CONbits.DC1B = (unsigned char)(duty10 & 0x03U);
}
