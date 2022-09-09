#ifndef _INT_H
#define _INT_H

/**
  Section: Included Files
*/

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

#define TMR1_INTERRUPT_TICKER_FACTOR    1
#define TMR1_RELOAD_VALUE               0xFC0C

/**
  Section: TMR1 APIs
*/

/**
  @Summary
    Initializes the INT interrupt

  @Description
    This routine initializes the INT pin interrupt.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

  @Example
    <code>
    main()
    {
        // Initialize TMR1 module
        INT_Initialize();

        // Do something else...
    }
    </code>
*/
//void INT_Initialize(void);


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif // _INT_H
/**
 End of File
*/
