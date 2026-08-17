/* 
 * File:   buzzer.c
 * Author: Samuel
 *
 * Created on 16 de Agosto de 2026, 22:09
 */

//----------------------------------------------------------------------------//
// #PRAGMAS                                                                   //
#pragma config PBADEN=OFF

//----------------------------------------------------------------------------//
// #INCLUDES                                                                  //   
#include <xc.h>

//----------------------------------------------------------------------------//
// #DEFINES                                                                   //
#undef _XTAL_FREQ
#define _XTAL_FREQ 48000000UL

#define buzzerPin RB4

//----------------------------------------------------------------------------//
// FUNCTION DECLARATIONS                                                      //
void buzzer();

/*
 * 
 */
int main(void) {

    buzzerPin = 1;     // Turn buzzer off (Buzzer uses active-low logic).  
    
    //--------------------------------------------------------------------
    // I/O PORTs
    // Direction according to published schematics.
    TRISBbits.RB4 = 0;  // RB4 is an output.
    
    while(1){
    
        buzzer();
        
        __delay_ms(500); 
    }
    
    return (EXIT_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
// Function: void bbuzzer()                                                   //                                                                            //
//                                                                            //
void buzzer(){
    
    unsigned char i;
    
    for(i=0;i<40;i++){
        buzzerPin = 0;
        __delay_ms(2); 

        buzzerPin = 1;
        __delay_ms(1);
    }   
}
// buzzer()                                                                   // 
////////////////////////////////////////////////////////////////////////////////
