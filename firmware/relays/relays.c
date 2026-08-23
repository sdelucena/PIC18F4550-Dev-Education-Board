/* 
 * File:   relays.c
 * Author: Samuel
 *
 * Created on 23 de Agosto de 2026, 13:55
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

// Relays use active-high logic
#define relay1Pin RB3       // Also controls red LED D4
#define relay2Pin RC0       // Also controls red LED D3

//----------------------------------------------------------------------------//
// FUNCTION DECLARATIONS                                                      //
void relays();

/*
 * 
 */
void main(void) { 
    
    //--------------------------------------------------------------------
    // I/O PORTs
    // Direction according to published schematics.
    TRISBbits.RB3 = 0;  // RB3 is an output.
    TRISCbits.RC0 = 0;  // RC0 is an output.
    
    relays();   // Endless loop.
       
}
// main()                                                                     // 
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Function: void relays()                                                    //                                                                            //
//
// Relays 1 and 2 and corresponding red LEDs use active-high logic 
//
void relays(){
    
    while(1){
        relay2Pin = 0;  // Turn relay2 and corresponding red LED off
    
        relay1Pin = 1;  // Turn relay1 and corresponding red LED on  
    
        __delay_ms(1500);
    
        relay1Pin = 0;  // Turn relay 1 and corresponding red LED off
    
        relay2Pin = 1;  // Turn relay2 and corresponding red LED on 
    
        __delay_ms(1500);
    }
}
// relays()                                                                   // 
////////////////////////////////////////////////////////////////////////////////
