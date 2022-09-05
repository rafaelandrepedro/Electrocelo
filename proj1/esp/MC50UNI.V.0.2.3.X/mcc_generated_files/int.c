
/**
  Section: Included Files
*/

#include <xc.h>
#include "int.h"
#include "pin_manager.h"
//#include "../main.h"
//#include "../outputs.h"
//#include "../inputs.h"
/**
  Section: Global Variables Definitions
*/

//extern volatile timeslotSystem ts_system;

/**
  Section: INT APIs
*/

//void INT_Initialize(void)
//{
//    //Set the INT interrupt
//
//    // Set the rising or falling edge detection corresponding to the current pin state.
//    if ( Encoder_GetValue() == 0 )
//    {
//        OPTION_REGbits.INTEDG = 1;  // The pin is low, detect rising edge.
//    }
//    else
//    {
//        OPTION_REGbits.INTEDG = 0;  // The pin is high, detect falling edge.
//    }
//    
//    INTCONbits.INTF = 0;    // Clear the previous interrupt flags.
//    
//    INTCONbits.INTE = 1;    // Enable the external interrupt on pin RB0 (encoder).
//}

/**
  End of File
*/
