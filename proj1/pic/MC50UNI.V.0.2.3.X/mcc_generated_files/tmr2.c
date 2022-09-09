/**
  TMR2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr2.c

  @Summary
    This is the generated driver implementation file for the TMR2 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for TMR2.
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "tmr2.h"
#include"../controlCurrent.h"
#include"../outputs.h"
#include"../sm_ControlLearning.h"
#include"../main.h"



extern sm_t menuConfiguration_stateMachine;
extern volatile LearnStruct learn_st;
char Counterchoose = 0;

extern volatile timeslotSystem      ts_system;
extern volatile varSystem           var_sys;
extern          PowerControlStruct  powerControl_st;
extern volatile varSystem_NVM       var_sys_NVM;

/**
  Section: Global Variables Definitions
*/

void (*TMR2_InterruptHandler)(void);

/**
  Section: TMR2 APIs
*/

void TMR2_Initialize(void)
{
    // Set TMR2 to the options selected in the User Interface

    // T2CS FOSC; 
    T2CLKCON = 0x02;

    // T2PSYNC Not Synchronized; T2MODE Software control; T2CKPOL Falling Edge; T2CKSYNC Not Synchronized; 
    T2HLT = 0x40;

    // T2RSEL T2CKIPPS pin; 
    T2RST = 0x00;

    // PR2 199; 
    T2PR = 0xC7;

    // TMR2 0; 
    T2TMR = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR4bits.TMR2IF = 0;

    // Enabling TMR2 interrupt.
    PIE4bits.TMR2IE = 1;

    // Set Default Interrupt Handler
    TMR2_SetInterruptHandler(TMR2_DefaultInterruptHandler);

    // T2CKPS 1:32; T2OUTPS 1:10; TMR2ON on; 
    T2CON = 0xD9;
}

void TMR2_ModeSet(TMR2_HLT_MODE mode)
{
   // Configure different types HLT mode
    T2HLTbits.MODE = mode;
}

void TMR2_ExtResetSourceSet(TMR2_HLT_EXT_RESET_SOURCE reset)
{
    //Configure different types of HLT external reset source
    T2RSTbits.RSEL = reset;
}

void TMR2_Start(void)
{
    // Start the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 1;
}

void TMR2_StartTimer(void)
{
    TMR2_Start();
}

void TMR2_Stop(void)
{
    // Stop the Timer by writing to TMRxON bit
    T2CONbits.TMR2ON = 0;
}

void TMR2_StopTimer(void)
{
    TMR2_Stop();
}

uint8_t TMR2_Counter8BitGet(void)
{
    uint8_t readVal;

    readVal = TMR2;

    return readVal;
}

uint8_t TMR2_ReadTimer(void)
{
    return TMR2_Counter8BitGet();
}

void TMR2_Counter8BitSet(uint8_t timerVal)
{
    // Write to the Timer2 register
    TMR2 = timerVal;
}

void TMR2_WriteTimer(uint8_t timerVal)
{
    TMR2_Counter8BitSet(timerVal);
}

void TMR2_Period8BitSet(uint8_t periodVal)
{
   PR2 = periodVal;
}

void TMR2_LoadPeriodRegister(uint8_t periodVal)
{
   TMR2_Period8BitSet(periodVal);
}

void TMR2_ISR(void)
{

    // clear the TMR2 interrupt flag
    PIR4bits.TMR2IF = 0;
    
          //  if (var_sys_NVM.motorSensitivity != 0 || var_sys_NVM.decelarationSensivity!=0)
           //     {                 
                ReadADC(); 
               // }

            refreshSegment();

            if(ts_system.ts_TimeSlotMain>0)
                {
                ts_system.ts_TimeSlotMain--;    // DM: Currentlly decrements every 1ms.
                }
            
            if (ts_system.ts_TimeSlot50ms > 0)
                {
                ts_system.ts_TimeSlot50ms--;
                }
            else
                {
                ts_system.ts_TimeSlot50ms = 50; 


                     /* Block Executed every 50ms */
                    controlTimeslots();

                      if (Counterchoose == 0)
                               {
                                   Counterchoose = 1;
                               }
                               else
                               {
                                   Counterchoose = 0;
                               }
                           if (var_sys.LearningIsEnabled==NO)
                           { 
                               
                         
                               if (var_sys.TimeMaxMotorIsON > 0 && var_sys.Activatecounter != stoped)
                               {
 
                                    var_sys.TimeMaxMotorIsON--;     
                               
                               }
                               
                              /* Block Executed every 50ms */
                               if (var_sys.Activatecounter == open)
                               { 
                                   {   
                                      
                                        if (powerControl_st.decelarationActive==YES)
                                        {
                                            if(Counterchoose ==1){
                                              var_sys.PositionActual++;
                                            }
                                        }
                                        else
                                        {
                                            var_sys.PositionActual++;
                                        }

                                    }
                                }
                               
                               
                               else if (var_sys.Activatecounter == close)   
                               {                                        
                                       if (powerControl_st.decelarationActive==YES)
                                        {
                                            if(Counterchoose ==1){
                                              var_sys.PositionActual--;
                                            }
                                        }
                                        else
                                        {
                                            var_sys.PositionActual--;
                                        }
                                }
  
                           }   

                           else
                           {
                               if (var_sys.Counter_Learning ==1)
                               {

                                    if (var_sys.Activatecounter == open)
                                    {

                                        if (var_sys.LearningDecelaration ==1)
                                           {
//                                               if(Counterchoose ==1)
//                                               {
//                                                 learn_st.timeOpen++;  
//                                               }                 
                                      
                                           } 
                                           else
                                           {
                                             learn_st.timeOpen++;  
                                           }
                                    }
                                    else if (var_sys.Activatecounter == close) 
                                    {

                                        if (var_sys.LearningDecelaration ==1)
                                            {
//                                                 if(Counterchoose ==1)
//                                                 {
//                                                   learn_st.timeClose++;  
//                                                 }
                                            } 
                                            else
                                            {
                                               learn_st.timeClose++;  
                                            }
                                     }
                                }

                                    
                                if (var_sys.LearningDecelaration ==1 && var_sys.programinAutomatic == 1) 
                                {
                                    
                                        
                                       if ( ts_system.ts_TimeSlot500ms > 0)
                                           {
                                               ts_system.ts_TimeSlot500ms--;
                                           }

                                        else
                                         {
                                            ts_system.ts_TimeSlot500ms = 10;  // Restart the 500ms count.  

                                            if ( var_sys.Activatecounter ==open )
                                               {
                                                 learn_st.timeDecelerationOpen++;
                                                 learn_st.timeOpen++;
                                                 
                                               }    

                                            else if ( var_sys.Activatecounter ==close )
                                               {
                                                 learn_st.timeDecelerationClose++;  
                                                 learn_st.timeClose++; 
                                               } 
                                         }
                                }
                            }
                }    


    if(TMR2_InterruptHandler)
    {
        TMR2_InterruptHandler();
    }
}


void TMR2_SetInterruptHandler(void (* InterruptHandler)(void)){
    TMR2_InterruptHandler = InterruptHandler;
}

void TMR2_DefaultInterruptHandler(void){
    // add your TMR2 interrupt custom code
    // or set custom function using TMR2_SetInterruptHandler()
}

/**
  End of File
*/