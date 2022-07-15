
#include <xc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/adcc.h"
#include "outputs.h"
#include "controlCurrent.h"



extern volatile varSystem_NVM       var_sys_NVM;
extern volatile varSystem           var_sys;
extern volatile timeslotSystem      ts_system;
extern          PowerControlStruct  powerControl_st;

unsigned int ADC_array [Samples_ADC];
volatile unsigned int SumEnergyADCHist_array [Samples_EnergyADCHist];
volatile unsigned int ADC_zero_array[Samples_ADC];

volatile unsigned char idxAdcAquisition;
volatile unsigned char idxSaveEnergyADCHist;
volatile unsigned char idxAdcZeroAquisition;
volatile unsigned char numberOfErrorCurrent;

//char    tempBuffer[50];
//unsigned char    tempBuffer[5];
//unsigned char    ltempBuffer[5];
volatile unsigned int  erroranterior;

/******************************************************************************/
/* This function fills in a circular way the ADC_array buffer, thus, heving   */
/* the last 30ms os current conversions (called by an 1ms interrupt)          */
/******************************************************************************/
void ReadADC(void)
{
     if (!ADCON0bits.GO_nDONE)//
     {  
        if ( idxAdcAquisition >= Samples_ADC )
        {
            idxAdcAquisition=0;
        }
         
        ADC_array[idxAdcAquisition] = ((unsigned int)((ADRESH << 8) + ADRESL)>>6); 
        ADCC_GetSingleConversion(0x00);
   	    idxAdcAquisition++;
        
     }   
    
}

/******************************************************************************/
/* Returns the energy sum of the ADC_array (the last 30ms of energy)          */
/* This energy will be used to control the motor current on normal speed phase*/
/******************************************************************************/
unsigned int sumEnergyADC(void)
{
    unsigned char   i;
//    unsigned int    media = 0;
    unsigned int    sumE = 0;
    unsigned int    auxValue = 0;
    
//    //>>> DM: DEBUG
//    //sprintf(tempBuffer, "ADC Zero=%d\r\n", ADC_array[0]);
//    //EUSART_Write_String( (char*)&tempBuffer[0]);
//    EUSART_Write_String( (char*)"ADC Zero:\r\n");
//    //<<< DM: DEBUG
    
    for ( i=0 ; i<(Samples_ADC) ; i++ )
    {
//        if ( ADC_array[i] > ZERO_VALUE_ADC )
//        {
//            auxValue = ( ADC_array[i] - ZERO_VALUE_ADC );//Subtrai o valor central da onda ao valor lido
//        }
//        else
//        {
//           auxValue = ( ZERO_VALUE_ADC - ADC_array[i] );//subtrai o valor da corrente ao  valor central da onda
//        }

        if ( ADC_array[i] > var_sys.ADCZeroOffset )
        {
            auxValue = ( ADC_array[i] - var_sys.ADCZeroOffset );//Subtrai o valor central da onda ao valor lido
        }
        else
        {
           auxValue = ( var_sys.ADCZeroOffset - ADC_array[i] );//subtrai o valor da corrente ao  valor central da onda
        }
        sumE += auxValue;// adiciona o valor calculado anteriormente ao somatorio de energia
        

    }

    return sumE;
}

/******************************************************************************/
/* Returns the new ADC Zero Offset Value. This value is the mean of the last  */
/* 30ms (30 samples) of ADC samples while the motor is stopped                */
/******************************************************************************/
void refreshADCZeroOffset(void)
{
    unsigned char   i;
    unsigned int    media = 0;

    
    if ( var_sys.StateMotor == Stopped )
    {
        if ( ts_system.TimeStopADCZeroOffsetCalc <= 0 )
        {
            ts_system.TimeStopADCZeroOffsetCalc = TIME_1S;  // Calculate the new zero every second.
            
    //        //>>> DM: DEBUG
    //        //sprintf(tempBuffer, "ADC Zero=%d\r\n", ADC_array[0]);
    //        //EUSART_Write_String( (char*)&tempBuffer[0]);
    //        EUSART_Write_String( (char*)"ADC Zero:\r\n");
    //        //<<< DM: DEBUG

            for ( i=0 ; i<(Samples_ADC) ; i++ )
            {
    //            //>>> DM: DEBUG
    //            sprintf(tempBuffer, "%d\r\n", ADC_array[i]);
    //            EUSART_Write_String( (char*)&tempBuffer[0]);
                media += ADC_array[i];
    //            //<<< DM: DEBUG
            }

            media = media/Samples_ADC;
            if ( (media>(ZERO_VALUE_ADC-20)) && (media<(ZERO_VALUE_ADC+20)) )
            {
                //var_sys.ADCZeroOffset = media;
            }
            else
            {
                //var_sys.ADCZeroOffset = ZERO_VALUE_ADC;
                media = ZERO_VALUE_ADC;
            }
            
            //>>> An array was created to have a mean of 30 times the mean calculated above.
            if ( idxAdcZeroAquisition >= Samples_ADC )
            {
                idxAdcZeroAquisition = 0;
            }
            ADC_zero_array[idxAdcZeroAquisition] = media;
            idxAdcZeroAquisition++;

            // calculate the mean of the 30 means.
            media = 0;
            for ( i=0 ; i<(Samples_ADC) ; i++ )
            {
//                //>>> DM: DEBUG
//                sprintf(tempBuffer, "%d\r\n", ADC_zero_array[i]);
//                EUSART_Write_String( (char*)&tempBuffer[0]);
//                //<<< DM: DEBUG
                
                media += ADC_zero_array[i];
            }
            media = media/Samples_ADC;

            var_sys.ADCZeroOffset = media;
            //<<< An array was created to have a mean of 30 times the mean calculated above.
    
//            //>>> DM: DEBUG
//            sprintf(tempBuffer, "\r\n%d\r\n\r\n", var_sys.ADCZeroOffset);
//            EUSART_Write_String( (char*)&tempBuffer[0]);
//            //<<< DM: DEBUG
        }
    }
    else
    {
        // Do nothing!
    }
}

/******************************************************************************/
/* Save a history of the last 10 energy sums in a circular buffer             */
/* This history will be used to control the motor current on the deceleration */
/* phase, because the deceleration is made cutting wave semi-cycles           */
/******************************************************************************/
void saveEnergyADCHist(unsigned int valueToSave)
{
    if(idxSaveEnergyADCHist>=Samples_EnergyADCHist)
    {
        idxSaveEnergyADCHist=0;
    }

    SumEnergyADCHist_array[idxSaveEnergyADCHist]=valueToSave;
    idxSaveEnergyADCHist++;
}

/******************************************************************************/
/* Returns the energy sum of the SumEnergyADCHist_array (the last 10*30ms of  */
/* energy).                                                                   */
/* This history will be used to control the motor current on the deceleration */
/* phase, because the deceleration is made cutting wave semi-cycles           */
/******************************************************************************/
unsigned long sumHIST(void)
{
    unsigned char i;
    unsigned long sumH = 0;
    unsigned int max=0;
    unsigned int min=0xFFFF;


    for( i = 0; i<(Samples_EnergyADCHist); i++)
    {
        sumH=sumH+SumEnergyADCHist_array[i];

        //Selecciona o valor Maior
        if(SumEnergyADCHist_array[i]>max)
        {
            max=SumEnergyADCHist_array[i];
        }

        //Selecciona o valor Menor
        if(SumEnergyADCHist_array[i]<min)
        {
            min=SumEnergyADCHist_array[i];
        }
    }
    //Remover o valor menor e o maior do sumatorio.
    sumH = sumH - ( max+min );

    return sumH;
}

/******************************************************************************/
/* This routine will update the ActualCurrent and ActualHistCurrent to        */
/* implement the motor current control                                        */
/******************************************************************************/
void refreshCurrent(void)
{
    //var_sys.ActualCurrent=sumEnergyADC(&ADC_array[0]);
   
    //var_sys.ActualCurrent=sumEnergyADC();
    if ( (var_sys_NVM.electricBrake==1) && (ts_system.TimeElectricBrake>0) ) // rev 1.150 - On the electric brake active time, the current cannot be considered for learning purposes.
    {
        // Do nothing. The considered current will be the last valid value.
    }
    else
    {
        // The electric brake is not active. The current can be considered.
        var_sys.ActualCurrent=sumEnergyADC();
    }

    saveEnergyADCHist(var_sys.ActualCurrent);

    var_sys.ActualHistCurrent=sumHIST();
}

/******************************************************************************/
/* This routine returns the energy value to consider a overcurrent            */
/* The routine returns this value taking into account if:                     */
/*   1. The motor is in the soft start phase                                  */
/*   2. The motor is in the wait before soft start phase                      */
/*   3. The motor is in the deceleration phase or full speed                  */
/*   4. The motor is opening or closing                                       */
/*   5. The motor sesitivity configured by the installer for both the full    */
/*      speed phase and the deceleration phase                                */
/*   6. The current limits saved on the learning procedure                    */
/******************************************************************************/
unsigned long getCurrentComparator()
{
    unsigned int tempOffset=0;
    
    
    if(ts_system.timeSoftStart>0)
    {
        ts_system.timewaitBeforeSoftStart=TIME_1S;
        //ts_system.TimeStopEncoder = TIME_100MS;
        tempOffset=1200;
    }
    else if(ts_system.timewaitBeforeSoftStart>0)
    {
        tempOffset=1200;
    }
    else
    {
        tempOffset=0;
    }

    if(powerControl_st.decelarationActive==NO)
    {
        if(var_sys.StateMotor==InClose)
        {
            var_sys.ActualComparatorCurrent=var_sys_NVM.learningCurrentNormalClose;
        }
        else
        {
            var_sys.ActualComparatorCurrent=var_sys_NVM.learningCurrentNormalOpen;
        }

        if(var_sys.ActualComparatorCurrent<=100||(var_sys.ActualComparatorCurrent>(510*Samples_ADC)))
        {
             var_sys.ActualComparatorCurrent=(510*Samples_ADC);
        }
        else
        {
            unsigned char x=var_sys_NVM.motorSensitivity;
            //var_sys.ActualComparatorCurrent=var_sys.ActualComparatorCurrent+(OFFSET_CURRENT_INIT+(OFFSET_CURRENT*(10-var_sys_NVM.motorSensitivity)));
            
            //após uma analise à curva de variação da currente optei por uma variação não linear de forma a obter
            //uma variação menor para senbilidades altas e um variação elevada para a outra metada da escala.
            //Y=10x^2-202x+1100;
           var_sys.ActualComparatorCurrent=var_sys.ActualComparatorCurrent+((FactorX2*(x*x))+(FactorX*x)+FactorB);
        }
    }
    else
    {
        if(var_sys.StateMotor==InClose)
        {
            var_sys.ActualComparatorCurrent=var_sys_NVM.learningCurrentDecelarationClose;
        }
        else
        {
            var_sys.ActualComparatorCurrent=var_sys_NVM.learningCurrentDecelarationOpen ;
        }

        if(var_sys.ActualComparatorCurrent<=5000)
        {
            var_sys.ActualComparatorCurrent=5000;
        }
        else
        {
            var_sys.ActualComparatorCurrent=var_sys.ActualComparatorCurrent-(OFFSET_CURRENT_HIST_INIT+(OFFSET_CURRENT_HIST*(10-var_sys_NVM.decelarationSensivity)));
        } 
    }


    return var_sys.ActualComparatorCurrent+tempOffset;
}

/******************************************************************************/
/* This process verifies if an obstacle is present on the moving gate and     */
/* takes the necessary actions.                                               */
/* The process reaction time is 100ms (two passages whit the overcurrent      */
/* condition), but in sum there is a blind time implemented to take into      */
/* account velocity changes (ignore).                                          */
/******************************************************************************/
void ControlCurrent(void)
{

    refreshCurrent();   // Refresh the energy sums to compare with the limit values.
    
    //>>> Refresh of the ADC Zero Offset value every 1 second with the motor stopped.
    // On the sm_ControlGate is also guaranteed that TimeStopADCZeroOffsetCalc
    // is initialized with 5 seconds when the motor is moving, so that, the motor
    // is stopped at least for 5 seconds before the ADC Offset is refreshed.
    refreshADCZeroOffset();
    //<<< Refresh of the ADC Zero Offset value every 1 second with the motor stopped.
    
    var_sys.velocityActual          = GetMotorPower();          // Read the current motor speed, tha depends if it is in soft start or not and of the motor power defined by the installer.
    var_sys.ActualComparatorCurrent = getCurrentComparator();   // Gets the current limit for the current moving situation.
    
    if(var_sys.StateMotor == Stopped)
    {
        // If the motor is stopped
        numberOfErrorCurrent=0;
        var_sys.CurrentAlarmIsOn=NO;
        var_sys.InvertionCurrentOpening=NO;
        var_sys.InvertionCurrentClosing=NO;
        ts_system.TimeTransitionDecelaration=TIME_1S;
    }
    
    else if(powerControl_st.decelarationActive==NO)
    {

//            itoa (tempBuffer,var_sys.ActualCurrent,10);
//            EUSART_Write_String((char*)tempBuffer);
//            EUSART_Write_String("A");
//            ltoa (ltempBuffer,var_sys.ActualComparatorCurrent,10);
//            EUSART_Write_String((char*)ltempBuffer);
//            EUSART_Write_String("G");   
        ts_system.TimeTransitionDecelaration=TIME_1S;
        if (( var_sys.ActualCurrent>var_sys.ActualComparatorCurrent ) && (ts_system.TimeChargeCondesador<=0)&&var_sys_NVM.motorSensitivity!=0 && ts_system.TimeReleCapacitor<=0)
        {
             if (numberOfErrorCurrent >=1)
             {
                 if(erroranterior > var_sys.ActualCurrent )
                 {
                   numberOfErrorCurrent = 0;
                 }
                 else
                 {
                   numberOfErrorCurrent++; 
                 }
                 erroranterior = var_sys.ActualCurrent;
             }
             else
             { 
             numberOfErrorCurrent++;
             erroranterior = var_sys.ActualCurrent;
             }
//          EUSART_Write_String("-----");
//            numberOfErrorCurrent++;
            if(ts_system.TimeCurrentWaitForAlarm<=0&&numberOfErrorCurrent>1)
            {
                var_sys.StateMotor = Stopped;
                ts_system.TimeCurrentAlarm= TIME_1S*10;
                var_sys.CurrentAlarmIsOn=YES;
            }

            //sprintf(tempBuffer3,"Stop current %d;%d",var_sys.ActualCurrent,var_sys.ActualComparatorCurrent);
            //EUSART_Write_String(tempBuffer3);
        }
        else
        {
            numberOfErrorCurrent=0;
            var_sys.CurrentAlarmIsOn=NO;
            var_sys.InvertionCurrentOpening=NO;
            var_sys.InvertionCurrentClosing=NO;
            

        }
    }
    else
    {
        if( ( var_sys.ActualHistCurrent<var_sys.ActualComparatorCurrent ) && (ts_system.TimeChargeCondesador<=0)&&ts_system.TimeTransitionDecelaration<=0&&var_sys_NVM.decelarationSensivity!=0)
        {
            //EUSART_Write('E');
            numberOfErrorCurrent++;
            if(ts_system.TimeCurrentWaitForAlarm<=0&&numberOfErrorCurrent>2)
            {
                var_sys.StateMotor = Stopped;
                ts_system.TimeCurrentAlarm= TIME_1S*10;
                var_sys.CurrentAlarmIsOn=YES;
            }

        }
        else
        {
            numberOfErrorCurrent=0;
            var_sys.CurrentAlarmIsOn=NO;
            var_sys.InvertionCurrentOpening=NO;
            var_sys.InvertionCurrentClosing=NO;

        }
    }
}

