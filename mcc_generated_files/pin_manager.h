/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F46K40
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set channel_current aliases
#define channel_current_TRIS                 TRISAbits.TRISA0
#define channel_current_LAT                  LATAbits.LATA0
#define channel_current_PORT                 PORTAbits.RA0
#define channel_current_WPU                  WPUAbits.WPUA0
#define channel_current_OD                   ODCONAbits.ODCA0
#define channel_current_ANS                  ANSELAbits.ANSELA0
#define channel_current_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define channel_current_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define channel_current_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define channel_current_GetValue()           PORTAbits.RA0
#define channel_current_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define channel_current_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define channel_current_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define channel_current_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define channel_current_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define channel_current_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define channel_current_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define channel_current_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set FimCurso_Close aliases
#define FimCurso_Close_TRIS                 TRISAbits.TRISA1
#define FimCurso_Close_LAT                  LATAbits.LATA1
#define FimCurso_Close_PORT                 PORTAbits.RA1
#define FimCurso_Close_WPU                  WPUAbits.WPUA1
#define FimCurso_Close_OD                   ODCONAbits.ODCA1
#define FimCurso_Close_ANS                  ANSELAbits.ANSELA1
#define FimCurso_Close_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define FimCurso_Close_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define FimCurso_Close_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define FimCurso_Close_GetValue()           PORTAbits.RA1
#define FimCurso_Close_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define FimCurso_Close_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define FimCurso_Close_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define FimCurso_Close_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define FimCurso_Close_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define FimCurso_Close_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define FimCurso_Close_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define FimCurso_Close_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set FimCurso_Open aliases
#define FimCurso_Open_TRIS                 TRISAbits.TRISA2
#define FimCurso_Open_LAT                  LATAbits.LATA2
#define FimCurso_Open_PORT                 PORTAbits.RA2
#define FimCurso_Open_WPU                  WPUAbits.WPUA2
#define FimCurso_Open_OD                   ODCONAbits.ODCA2
#define FimCurso_Open_ANS                  ANSELAbits.ANSELA2
#define FimCurso_Open_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define FimCurso_Open_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define FimCurso_Open_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define FimCurso_Open_GetValue()           PORTAbits.RA2
#define FimCurso_Open_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define FimCurso_Open_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define FimCurso_Open_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define FimCurso_Open_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define FimCurso_Open_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define FimCurso_Open_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define FimCurso_Open_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define FimCurso_Open_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set Zero_Crossing aliases
#define Zero_Crossing_TRIS                 TRISAbits.TRISA3
#define Zero_Crossing_LAT                  LATAbits.LATA3
#define Zero_Crossing_PORT                 PORTAbits.RA3
#define Zero_Crossing_WPU                  WPUAbits.WPUA3
#define Zero_Crossing_OD                   ODCONAbits.ODCA3
#define Zero_Crossing_ANS                  ANSELAbits.ANSELA3
#define Zero_Crossing_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define Zero_Crossing_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define Zero_Crossing_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define Zero_Crossing_GetValue()           PORTAbits.RA3
#define Zero_Crossing_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define Zero_Crossing_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define Zero_Crossing_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define Zero_Crossing_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define Zero_Crossing_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define Zero_Crossing_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define Zero_Crossing_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define Zero_Crossing_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set Photocell aliases
#define Photocell_TRIS                 TRISAbits.TRISA4
#define Photocell_LAT                  LATAbits.LATA4
#define Photocell_PORT                 PORTAbits.RA4
#define Photocell_WPU                  WPUAbits.WPUA4
#define Photocell_OD                   ODCONAbits.ODCA4
#define Photocell_ANS                  ANSELAbits.ANSELA4
#define Photocell_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define Photocell_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define Photocell_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define Photocell_GetValue()           PORTAbits.RA4
#define Photocell_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define Photocell_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define Photocell_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define Photocell_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define Photocell_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define Photocell_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define Photocell_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define Photocell_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set SecurityBar aliases
#define SecurityBar_TRIS                 TRISAbits.TRISA5
#define SecurityBar_LAT                  LATAbits.LATA5
#define SecurityBar_PORT                 PORTAbits.RA5
#define SecurityBar_WPU                  WPUAbits.WPUA5
#define SecurityBar_OD                   ODCONAbits.ODCA5
#define SecurityBar_ANS                  ANSELAbits.ANSELA5
#define SecurityBar_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define SecurityBar_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define SecurityBar_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define SecurityBar_GetValue()           PORTAbits.RA5
#define SecurityBar_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define SecurityBar_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define SecurityBar_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define SecurityBar_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define SecurityBar_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define SecurityBar_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define SecurityBar_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define SecurityBar_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set SecurityBar8K aliases
#define SecurityBar8K_TRIS                 TRISAbits.TRISA6
#define SecurityBar8K_LAT                  LATAbits.LATA6
#define SecurityBar8K_PORT                 PORTAbits.RA6
#define SecurityBar8K_WPU                  WPUAbits.WPUA6
#define SecurityBar8K_OD                   ODCONAbits.ODCA6
#define SecurityBar8K_ANS                  ANSELAbits.ANSELA6
#define SecurityBar8K_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define SecurityBar8K_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define SecurityBar8K_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define SecurityBar8K_GetValue()           PORTAbits.RA6
#define SecurityBar8K_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define SecurityBar8K_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define SecurityBar8K_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define SecurityBar8K_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define SecurityBar8K_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define SecurityBar8K_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define SecurityBar8K_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define SecurityBar8K_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set SELECT aliases
#define SELECT_TRIS                 TRISAbits.TRISA7
#define SELECT_LAT                  LATAbits.LATA7
#define SELECT_PORT                 PORTAbits.RA7
#define SELECT_WPU                  WPUAbits.WPUA7
#define SELECT_OD                   ODCONAbits.ODCA7
#define SELECT_ANS                  ANSELAbits.ANSELA7
#define SELECT_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define SELECT_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define SELECT_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define SELECT_GetValue()           PORTAbits.RA7
#define SELECT_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define SELECT_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define SELECT_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define SELECT_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define SELECT_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define SELECT_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define SELECT_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define SELECT_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set PUSH aliases
#define PUSH_TRIS                 TRISBbits.TRISB0
#define PUSH_LAT                  LATBbits.LATB0
#define PUSH_PORT                 PORTBbits.RB0
#define PUSH_WPU                  WPUBbits.WPUB0
#define PUSH_OD                   ODCONBbits.ODCB0
#define PUSH_ANS                  ANSELBbits.ANSELB0
#define PUSH_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define PUSH_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define PUSH_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define PUSH_GetValue()           PORTBbits.RB0
#define PUSH_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define PUSH_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define PUSH_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define PUSH_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define PUSH_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define PUSH_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define PUSH_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define PUSH_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set KeyFull aliases
#define KeyFull_TRIS                 TRISBbits.TRISB1
#define KeyFull_LAT                  LATBbits.LATB1
#define KeyFull_PORT                 PORTBbits.RB1
#define KeyFull_WPU                  WPUBbits.WPUB1
#define KeyFull_OD                   ODCONBbits.ODCB1
#define KeyFull_ANS                  ANSELBbits.ANSELB1
#define KeyFull_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define KeyFull_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define KeyFull_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define KeyFull_GetValue()           PORTBbits.RB1
#define KeyFull_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define KeyFull_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define KeyFull_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define KeyFull_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define KeyFull_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define KeyFull_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define KeyFull_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define KeyFull_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set KeyWalk aliases
#define KeyWalk_TRIS                 TRISBbits.TRISB2
#define KeyWalk_LAT                  LATBbits.LATB2
#define KeyWalk_PORT                 PORTBbits.RB2
#define KeyWalk_WPU                  WPUBbits.WPUB2
#define KeyWalk_OD                   ODCONBbits.ODCB2
#define KeyWalk_ANS                  ANSELBbits.ANSELB2
#define KeyWalk_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define KeyWalk_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define KeyWalk_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define KeyWalk_GetValue()           PORTBbits.RB2
#define KeyWalk_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define KeyWalk_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define KeyWalk_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define KeyWalk_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define KeyWalk_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define KeyWalk_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define KeyWalk_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define KeyWalk_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set DataRF aliases
#define DataRF_TRIS                 TRISBbits.TRISB3
#define DataRF_LAT                  LATBbits.LATB3
#define DataRF_PORT                 PORTBbits.RB3
#define DataRF_WPU                  WPUBbits.WPUB3
#define DataRF_OD                   ODCONBbits.ODCB3
#define DataRF_ANS                  ANSELBbits.ANSELB3
#define DataRF_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define DataRF_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define DataRF_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define DataRF_GetValue()           PORTBbits.RB3
#define DataRF_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define DataRF_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define DataRF_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define DataRF_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define DataRF_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define DataRF_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define DataRF_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define DataRF_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set KEY_UP aliases
#define KEY_UP_TRIS                 TRISBbits.TRISB4
#define KEY_UP_LAT                  LATBbits.LATB4
#define KEY_UP_PORT                 PORTBbits.RB4
#define KEY_UP_WPU                  WPUBbits.WPUB4
#define KEY_UP_OD                   ODCONBbits.ODCB4
#define KEY_UP_ANS                  ANSELBbits.ANSELB4
#define KEY_UP_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define KEY_UP_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define KEY_UP_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define KEY_UP_GetValue()           PORTBbits.RB4
#define KEY_UP_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define KEY_UP_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define KEY_UP_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define KEY_UP_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define KEY_UP_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define KEY_UP_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define KEY_UP_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define KEY_UP_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set KEY_MENU aliases
#define KEY_MENU_TRIS                 TRISBbits.TRISB5
#define KEY_MENU_LAT                  LATBbits.LATB5
#define KEY_MENU_PORT                 PORTBbits.RB5
#define KEY_MENU_WPU                  WPUBbits.WPUB5
#define KEY_MENU_OD                   ODCONBbits.ODCB5
#define KEY_MENU_ANS                  ANSELBbits.ANSELB5
#define KEY_MENU_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define KEY_MENU_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define KEY_MENU_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define KEY_MENU_GetValue()           PORTBbits.RB5
#define KEY_MENU_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define KEY_MENU_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define KEY_MENU_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define KEY_MENU_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define KEY_MENU_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define KEY_MENU_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define KEY_MENU_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define KEY_MENU_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set KEY_DOWN aliases
#define KEY_DOWN_TRIS                 TRISBbits.TRISB6
#define KEY_DOWN_LAT                  LATBbits.LATB6
#define KEY_DOWN_PORT                 PORTBbits.RB6
#define KEY_DOWN_WPU                  WPUBbits.WPUB6
#define KEY_DOWN_OD                   ODCONBbits.ODCB6
#define KEY_DOWN_ANS                  ANSELBbits.ANSELB6
#define KEY_DOWN_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define KEY_DOWN_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define KEY_DOWN_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define KEY_DOWN_GetValue()           PORTBbits.RB6
#define KEY_DOWN_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define KEY_DOWN_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define KEY_DOWN_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define KEY_DOWN_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define KEY_DOWN_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define KEY_DOWN_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define KEY_DOWN_SetAnalogMode()      do { ANSELBbits.ANSELB6 = 1; } while(0)
#define KEY_DOWN_SetDigitalMode()     do { ANSELBbits.ANSELB6 = 0; } while(0)

// get/set KEY_CMD aliases
#define KEY_CMD_TRIS                 TRISBbits.TRISB7
#define KEY_CMD_LAT                  LATBbits.LATB7
#define KEY_CMD_PORT                 PORTBbits.RB7
#define KEY_CMD_WPU                  WPUBbits.WPUB7
#define KEY_CMD_OD                   ODCONBbits.ODCB7
#define KEY_CMD_ANS                  ANSELBbits.ANSELB7
#define KEY_CMD_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define KEY_CMD_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define KEY_CMD_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define KEY_CMD_GetValue()           PORTBbits.RB7
#define KEY_CMD_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define KEY_CMD_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define KEY_CMD_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define KEY_CMD_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define KEY_CMD_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define KEY_CMD_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define KEY_CMD_SetAnalogMode()      do { ANSELBbits.ANSELB7 = 1; } while(0)
#define KEY_CMD_SetDigitalMode()     do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set Dig2 aliases
#define Dig2_TRIS                 TRISCbits.TRISC0
#define Dig2_LAT                  LATCbits.LATC0
#define Dig2_PORT                 PORTCbits.RC0
#define Dig2_WPU                  WPUCbits.WPUC0
#define Dig2_OD                   ODCONCbits.ODCC0
#define Dig2_ANS                  ANSELCbits.ANSELC0
#define Dig2_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define Dig2_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define Dig2_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define Dig2_GetValue()           PORTCbits.RC0
#define Dig2_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define Dig2_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define Dig2_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define Dig2_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define Dig2_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define Dig2_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define Dig2_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define Dig2_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set Dig1 aliases
#define Dig1_TRIS                 TRISCbits.TRISC1
#define Dig1_LAT                  LATCbits.LATC1
#define Dig1_PORT                 PORTCbits.RC1
#define Dig1_WPU                  WPUCbits.WPUC1
#define Dig1_OD                   ODCONCbits.ODCC1
#define Dig1_ANS                  ANSELCbits.ANSELC1
#define Dig1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define Dig1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define Dig1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define Dig1_GetValue()           PORTCbits.RC1
#define Dig1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define Dig1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define Dig1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define Dig1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define Dig1_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define Dig1_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define Dig1_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define Dig1_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set RGBO1 aliases
#define RGBO1_TRIS                 TRISCbits.TRISC2
#define RGBO1_LAT                  LATCbits.LATC2
#define RGBO1_PORT                 PORTCbits.RC2
#define RGBO1_WPU                  WPUCbits.WPUC2
#define RGBO1_OD                   ODCONCbits.ODCC2
#define RGBO1_ANS                  ANSELCbits.ANSELC2
#define RGBO1_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RGBO1_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RGBO1_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RGBO1_GetValue()           PORTCbits.RC2
#define RGBO1_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RGBO1_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define RGBO1_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define RGBO1_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define RGBO1_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define RGBO1_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define RGBO1_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define RGBO1_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RGBO2 aliases
#define RGBO2_TRIS                 TRISCbits.TRISC5
#define RGBO2_LAT                  LATCbits.LATC5
#define RGBO2_PORT                 PORTCbits.RC5
#define RGBO2_WPU                  WPUCbits.WPUC5
#define RGBO2_OD                   ODCONCbits.ODCC5
#define RGBO2_ANS                  ANSELCbits.ANSELC5
#define RGBO2_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RGBO2_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RGBO2_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RGBO2_GetValue()           PORTCbits.RC5
#define RGBO2_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RGBO2_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RGBO2_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define RGBO2_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define RGBO2_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define RGBO2_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define RGBO2_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define RGBO2_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSELC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSELC7 = 0; } while(0)

// get/set Seg1 aliases
#define Seg1_TRIS                 TRISDbits.TRISD0
#define Seg1_LAT                  LATDbits.LATD0
#define Seg1_PORT                 PORTDbits.RD0
#define Seg1_WPU                  WPUDbits.WPUD0
#define Seg1_OD                   ODCONDbits.ODCD0
#define Seg1_ANS                  ANSELDbits.ANSELD0
#define Seg1_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define Seg1_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define Seg1_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define Seg1_GetValue()           PORTDbits.RD0
#define Seg1_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define Seg1_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define Seg1_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define Seg1_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define Seg1_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define Seg1_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define Seg1_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define Seg1_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set Seg2 aliases
#define Seg2_TRIS                 TRISDbits.TRISD1
#define Seg2_LAT                  LATDbits.LATD1
#define Seg2_PORT                 PORTDbits.RD1
#define Seg2_WPU                  WPUDbits.WPUD1
#define Seg2_OD                   ODCONDbits.ODCD1
#define Seg2_ANS                  ANSELDbits.ANSELD1
#define Seg2_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define Seg2_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define Seg2_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define Seg2_GetValue()           PORTDbits.RD1
#define Seg2_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define Seg2_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define Seg2_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define Seg2_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define Seg2_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define Seg2_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define Seg2_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define Seg2_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set Seg3 aliases
#define Seg3_TRIS                 TRISDbits.TRISD2
#define Seg3_LAT                  LATDbits.LATD2
#define Seg3_PORT                 PORTDbits.RD2
#define Seg3_WPU                  WPUDbits.WPUD2
#define Seg3_OD                   ODCONDbits.ODCD2
#define Seg3_ANS                  ANSELDbits.ANSELD2
#define Seg3_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define Seg3_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define Seg3_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define Seg3_GetValue()           PORTDbits.RD2
#define Seg3_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define Seg3_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define Seg3_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define Seg3_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define Seg3_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define Seg3_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define Seg3_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define Seg3_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set Seg4 aliases
#define Seg4_TRIS                 TRISDbits.TRISD3
#define Seg4_LAT                  LATDbits.LATD3
#define Seg4_PORT                 PORTDbits.RD3
#define Seg4_WPU                  WPUDbits.WPUD3
#define Seg4_OD                   ODCONDbits.ODCD3
#define Seg4_ANS                  ANSELDbits.ANSELD3
#define Seg4_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define Seg4_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define Seg4_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define Seg4_GetValue()           PORTDbits.RD3
#define Seg4_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define Seg4_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define Seg4_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define Seg4_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define Seg4_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define Seg4_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define Seg4_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define Seg4_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set Seg6 aliases
#define Seg6_TRIS                 TRISDbits.TRISD4
#define Seg6_LAT                  LATDbits.LATD4
#define Seg6_PORT                 PORTDbits.RD4
#define Seg6_WPU                  WPUDbits.WPUD4
#define Seg6_OD                   ODCONDbits.ODCD4
#define Seg6_ANS                  ANSELDbits.ANSELD4
#define Seg6_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define Seg6_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define Seg6_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define Seg6_GetValue()           PORTDbits.RD4
#define Seg6_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define Seg6_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define Seg6_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define Seg6_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define Seg6_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define Seg6_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define Seg6_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define Seg6_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set Seg5 aliases
#define Seg5_TRIS                 TRISDbits.TRISD5
#define Seg5_LAT                  LATDbits.LATD5
#define Seg5_PORT                 PORTDbits.RD5
#define Seg5_WPU                  WPUDbits.WPUD5
#define Seg5_OD                   ODCONDbits.ODCD5
#define Seg5_ANS                  ANSELDbits.ANSELD5
#define Seg5_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define Seg5_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define Seg5_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define Seg5_GetValue()           PORTDbits.RD5
#define Seg5_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define Seg5_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define Seg5_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define Seg5_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define Seg5_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define Seg5_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define Seg5_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define Seg5_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set Seg7 aliases
#define Seg7_TRIS                 TRISDbits.TRISD6
#define Seg7_LAT                  LATDbits.LATD6
#define Seg7_PORT                 PORTDbits.RD6
#define Seg7_WPU                  WPUDbits.WPUD6
#define Seg7_OD                   ODCONDbits.ODCD6
#define Seg7_ANS                  ANSELDbits.ANSELD6
#define Seg7_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define Seg7_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define Seg7_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define Seg7_GetValue()           PORTDbits.RD6
#define Seg7_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define Seg7_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define Seg7_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define Seg7_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define Seg7_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define Seg7_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define Seg7_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define Seg7_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set TRIAC aliases
#define TRIAC_TRIS                 TRISDbits.TRISD7
#define TRIAC_LAT                  LATDbits.LATD7
#define TRIAC_PORT                 PORTDbits.RD7
#define TRIAC_WPU                  WPUDbits.WPUD7
#define TRIAC_OD                   ODCONDbits.ODCD7
#define TRIAC_ANS                  ANSELDbits.ANSELD7
#define TRIAC_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define TRIAC_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define TRIAC_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define TRIAC_GetValue()           PORTDbits.RD7
#define TRIAC_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define TRIAC_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define TRIAC_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define TRIAC_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define TRIAC_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define TRIAC_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define TRIAC_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define TRIAC_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

// get/set RelayOpen aliases
#define RelayOpen_TRIS                 TRISEbits.TRISE0
#define RelayOpen_LAT                  LATEbits.LATE0
#define RelayOpen_PORT                 PORTEbits.RE0
#define RelayOpen_WPU                  WPUEbits.WPUE0
#define RelayOpen_OD                   ODCONEbits.ODCE0
#define RelayOpen_ANS                  ANSELEbits.ANSELE0
#define RelayOpen_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define RelayOpen_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define RelayOpen_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define RelayOpen_GetValue()           PORTEbits.RE0
#define RelayOpen_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define RelayOpen_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define RelayOpen_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define RelayOpen_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define RelayOpen_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define RelayOpen_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define RelayOpen_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define RelayOpen_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set RelayClose aliases
#define RelayClose_TRIS                 TRISEbits.TRISE1
#define RelayClose_LAT                  LATEbits.LATE1
#define RelayClose_PORT                 PORTEbits.RE1
#define RelayClose_WPU                  WPUEbits.WPUE1
#define RelayClose_OD                   ODCONEbits.ODCE1
#define RelayClose_ANS                  ANSELEbits.ANSELE1
#define RelayClose_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define RelayClose_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define RelayClose_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define RelayClose_GetValue()           PORTEbits.RE1
#define RelayClose_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define RelayClose_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define RelayClose_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define RelayClose_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define RelayClose_SetPushPull()        do { ODCONEbits.ODCE1 = 0; } while(0)
#define RelayClose_SetOpenDrain()       do { ODCONEbits.ODCE1 = 1; } while(0)
#define RelayClose_SetAnalogMode()      do { ANSELEbits.ANSELE1 = 1; } while(0)
#define RelayClose_SetDigitalMode()     do { ANSELEbits.ANSELE1 = 0; } while(0)

// get/set RelayFlashlight aliases
#define RelayFlashlight_TRIS                 TRISEbits.TRISE2
#define RelayFlashlight_LAT                  LATEbits.LATE2
#define RelayFlashlight_PORT                 PORTEbits.RE2
#define RelayFlashlight_WPU                  WPUEbits.WPUE2
#define RelayFlashlight_OD                   ODCONEbits.ODCE2
#define RelayFlashlight_ANS                  ANSELEbits.ANSELE2
#define RelayFlashlight_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define RelayFlashlight_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define RelayFlashlight_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define RelayFlashlight_GetValue()           PORTEbits.RE2
#define RelayFlashlight_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define RelayFlashlight_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define RelayFlashlight_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define RelayFlashlight_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define RelayFlashlight_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define RelayFlashlight_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define RelayFlashlight_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define RelayFlashlight_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/