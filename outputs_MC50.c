
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "inputs.h"
#include "sm_common.h"
#include "sm_ControlGate.h"
#include "mcc_generated_files/pin_manager.h"
#include "outputs.h"
#include "controlMemory.h"
#include "sm_Main.h"


extern sm_t controlGate_stateMachine;
extern volatile display_st dispStruct;
extern volatile timeslotSystem ts_system;
extern volatile varSystem var_sys;
extern volatile varSystem_NVM var_sys_NVM;
extern sm_t main_stateMachine;
extern volatile BUTTONS_STRUCT button_struct;

PowerControlStruct powerControl_st;
char zeroCrossingLength;
char zeroCrossingWaitTime[2]={25,25};   // DM: By default the zero crossing happens 25x100us after the signal goes to "1".
char zeroCrossingWaitTimeIdx = 0;
char zeroCrossing=0;
char waitZeroPeak=0;
char StateTRIAC=0;



electricalBrakeStruct brakeElectric_st;

unsigned char   difTime;
stateMotor_enum stateMotor;
unsigned char   temppower;
unsigned char   fullmotorPower;



volatile unsigned char DispTable[dSize] ={DISPLAY0,DISPLAY1,DISPLAY2,DISPLAY3,
                                         DISPLAY4,DISPLAY5,DISPLAY6,DISPLAY7,
                                         DISPLAY8,DISPLAY9,DISPLAYA,DISPLAYB,
                                         DISPLAYC,DISPLAYd,DISPLAYE,DISPLAYF,
                                         DISPLAYP,DISPLAYH,DISPLAYL,DISPLAYU,
                                         DISPLAYr,DISPLAYt,DISPLAYu,DISPLAYM,DISPLAYMINUS,DISPLAYBAR,
                                         A,B,C,D,E,F,DISPLAYBLANK,DISPLAYy,DISPLAYb,DISPLAYc,DISPLAYo}; //Indica o valor desejado para aparecer no display

void refreshSegment(void)
{
    
    
    if (dispStruct.intermitentFreq==0||dispStruct.upFase==1)
    {
        if (dispStruct.lastDisplay==disp2_e)
        {
            Dig2_SetLow();
            Segments_Set(DispTable[dispStruct.display_grp.value_display1]);
            Dig1_SetHigh();
            dispStruct.lastDisplay=disp1_e;
        }
        else
        {
            Dig1_SetLow();
            Segments_Set(DispTable[dispStruct.display_grp.value_display2]);
            Dig2_SetHigh();
            dispStruct.lastDisplay=disp2_e;
        }
    }
    else
    {
        
        Dig2_SetLow();
        Dig1_SetLow();
    }


    if(ts_system.timeFreqDigit<=0 && dispStruct.intermitentFreq!=0)
    {
        ts_system.timeFreqDigit=dispStruct.intermitentFreq;
        if(dispStruct.upFase==1)
        {
            dispStruct.upFase = 0;
        }
        else
        {
            dispStruct.upFase = 1;
        }
    }
}

void Segments_Set(char value)
{
   LATD &= 0x80;
   LATD |= value;
}
void RGB_Set(char value)
{
   LATC &= 0xdb ;
   LATC |= value;
   SELECT_SetLow(); 
}
void SetSegmentValueMain(char d1, char d2)  // Works always (rev 1.149)
{
    dispStruct.display_grp.value_display1=d1;
    dispStruct.display_grp.value_display2=d2;
    dispStruct.intermitentFreq=0;
    dispStruct.upFase=0;
}

void SetSegmentValue(char d1, char d2)      // Only works when the system is out of the menu. (rev 1.149)
{
    // rev 1.149 - Do not run when the system is on the configuration menu.
    //if ( main_stateMachine.current_state != st_MenuConfiguration )
    //{
        dispStruct.display_grp.value_display1=d1;
        dispStruct.display_grp.value_display2=d2;
        dispStruct.intermitentFreq=0;
        dispStruct.upFase=0;
    //}
}

void SetSegmentValueLearn(Direction_en direction)
{
    dispStruct.intermitentFreq=0;
    dispStruct.upFase=0;
    switch (direction)
    {
        case Rigth:
            if(dispStruct.display_grp.value_display1==sA && dispStruct.display_grp.value_display2==dBlank)
            {
               dispStruct.display_grp.value_display1=dBlank;
               dispStruct.display_grp.value_display2=sA;
            }
            else if(dispStruct.display_grp.value_display1==dBlank && dispStruct.display_grp.value_display2==sD)
            {
               dispStruct.display_grp.value_display1=sD;
               dispStruct.display_grp.value_display2=dBlank;
            }
            else if(dispStruct.display_grp.value_display1==sF)
            {
               dispStruct.display_grp.value_display1=sA;
               dispStruct.display_grp.value_display2=dBlank;
            }
            else if(dispStruct.display_grp.value_display1==dBlank)
            {
               dispStruct.display_grp.value_display2++;
            }
            else if(dispStruct.display_grp.value_display2==dBlank)
            {
               dispStruct.display_grp.value_display1++;
            }
            else
            {
               dispStruct.display_grp.value_display1=sA;
               dispStruct.display_grp.value_display2=dBlank;
            }
        break;
        case Left:
            if(dispStruct.display_grp.value_display2==sA && dispStruct.display_grp.value_display1==dBlank)
            {
               dispStruct.display_grp.value_display1=sA;
               dispStruct.display_grp.value_display2=dBlank;
            }
            else if(dispStruct.display_grp.value_display2==dBlank && dispStruct.display_grp.value_display1==sD)
            {
               dispStruct.display_grp.value_display1=dBlank;
               dispStruct.display_grp.value_display2=sD;
            }
            else if(dispStruct.display_grp.value_display1==sA)
            {
               dispStruct.display_grp.value_display1=sF;
            }
            else if(dispStruct.display_grp.value_display1==dBlank)
            {
               dispStruct.display_grp.value_display2--;
            }
            else if(dispStruct.display_grp.value_display2==dBlank)
            {
               dispStruct.display_grp.value_display1--;
            }
            else
            {
               dispStruct.display_grp.value_display1=sA;
               dispStruct.display_grp.value_display2=dBlank;
            }
        break;
    }

}

void SetSegmentValueIntermitentMain(char d1, char d2,int time)  // Works allways (rev 1.149)
{
    dispStruct.display_grp.value_display1=d1;
    dispStruct.display_grp.value_display2=d2;
    dispStruct.intermitentFreq=time;
    //dispStruct.upFase=1;
}

void SetSegmentValueIntermitent(char d1, char d2,int time)      // Only works when the systema is out of the menu. (rev 1.149)
{
    // rev 1.149 - Do not run when the system is on the configuration menu.
    if ( main_stateMachine.current_state != st_MenuConfiguration && (ts_system.timeoutMenu == 0 && button_struct.timer < TIME_1S))
    {
        dispStruct.display_grp.value_display1=d1;
        dispStruct.display_grp.value_display2=d2;
        dispStruct.intermitentFreq=time;
        //dispStruct.upFase=1;
    }
}

void controlMotorForce()
{     
//    unsigned char difTime;
 
    difTime=GetMotorPower();
    if(powerControl_st.decelarationActive==YES)
    {
        if(ts_system.TimeStopedBeforeDecelaration>0)
        {
            StateTRIAC=0;
        }
        else if(powerControl_st.actualCycle<powerControl_st.decelarationCyclesOff)// && var_sys_NVM.decelarationType == 0 )
        {
            //StateTRIAC=0;
            difTime=powerControl_st.decelarationPower;
            //>>> We cannot guarantee the minimum triac time of AtrasoNaVelocidade because the speed will be always the same.
            //>>> This minimum time alone makes the engine run fast.
            //difTime+=AtrasoNaVelocidade;    // Between 1*2+24=26 and, 9*2+24=42
            //<<< We cannot guarantee the minimum triac time of AtrasoNaVelocidade because the speed will be always the same.
            //<<< This minimum time alone makes the engine run fast.
        }
//        else if(powerControl_st.actualCycle<powerControl_st.decelarationCyclesOff && var_sys_NVM.decelarationType == 1){
//            StateTRIAC=0;
//        }
    }


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>> Zero crossing detection and triac OFF Guarantee before zero crossing.
    if(Zero_Crossing_GetValue()==1 && zeroCrossing==0)
    {
        // Passing here means that the transition from 0 to 1 of the zero crossing
        // singnal has been detected. It keeps passing here waiting a certain amount of
        // time so that it guarantees to signal the zero crossing at the zero voltage.
        // This amount of time is calibrated at real time, counting the time that
        // the signal is '1' and dividing it by 2. This time counts when the signal is '1',
        // stops if it is '0' and calculates the neu wait time when the passage
        // from '0' to '1' is detected.
        // I have implemented two zeroCrossingWaitTime, one for each zero crossing,
        // one for -V to +V and another for +V to -V. This had to be implemented this way,
        // because the zero crossing pulses were not simetric, giving slightly different wait times.
        
        //RA7_SetHigh();   // DM: DEBUG!
        
        if ( waitZeroPeak == 0 )
        {
            // This is the first time that the pin is at '1', calculate the new wait time.
            zeroCrossingWaitTime[zeroCrossingWaitTimeIdx] = (zeroCrossingLength>>1); // DM: Divide by 2 to obtain the new wait time for the zero crossing.
            if ( zeroCrossingWaitTimeIdx == 0 )
            {
                zeroCrossingWaitTimeIdx = 1;
            }
            else
            {
                zeroCrossingWaitTimeIdx = 0;
            }
            // And start the new time count.
            zeroCrossingLength = 0;
        }

        if ( (difTime<=TimeToTurnOffTriac) || (ts_system.TimeElectricBrake>0) )
        {
            TRIAC_SetLow();     // This way we guarantee that the triac has an OFF order when the zero cross happens.
            var_sys.TriacON=NO; // This will ensure that the ON order doesn't goes into the next semi-cycle.
        }

        
        waitZeroPeak++;
        //if ( waitZeroPeak > 25 )
        if ( waitZeroPeak > zeroCrossingWaitTime[zeroCrossingWaitTimeIdx] )  // DM: Comparing with the calibrated wait time.
        //if ( waitZeroPeak > zeroCrossingWaitTime[0] )  // DM: Comparing with the calibrated wait time.
        {
            //RA7_SetHigh();   // DM: DEBUG!
            if ((var_sys.Control50or60hz >= 90)&&(var_sys.Control50or60hz <= 105)){
                var_sys.Torquerelanty = 1;
            }  
            else
            {
               var_sys.Torquerelanty = 0; 
            }
                        
            ts_system.ts_TimeSlotTRIAC=TimeToTurnOffTriac;  
            var_sys.Control50or60hz = 0;
            StateTRIAC=1;
            zeroCrossing=1;
            powerControl_st.actualCycle++;
//            if(powerControl_st.actualCycle>=(powerControl_st.decelarationCyclesOff+powerControl_st.decelarationCyclesOn))
//            {
//                powerControl_st.actualCycle=0;
//            }
            // rev 1.149 - Improvement of the electric brake. It will put a half rectified wave on both directions (DC voltage supply).
            if ( var_sys_NVM.electricBrake==1 && ts_system.TimeElectricBrake>0 )    // If the electric brake is active, it will apply a half rectified wave.
            {
                // We will use a 2 semi-cycles counting to do this.
                if ( powerControl_st.actualCycle>=2 )
                {
                    powerControl_st.actualCycle=0;
                }
            }
            else    // Otherwise it will make a 3 semi-cycles period for velocity control on the deceleration time.
            {
                if ( powerControl_st.actualCycle>=(powerControl_st.decelarationCyclesOff+powerControl_st.decelarationCyclesOn) )
                {
                    powerControl_st.actualCycle=0;
                }
            }
        }

//        //Sincroniza a aquisição da ADC com a passagem por 0.
//        syncIdxAdcAquisition();
    }
    
   
    
    else if(Zero_Crossing_GetValue()==0 && zeroCrossing!=0)
    {
        //RA7_SetLow();   // DM: DEBUG!
        zeroCrossing=0;
        waitZeroPeak=0;
        
    }
    
    
    if ( Zero_Crossing_GetValue()!=0 )
    {
        // The zero crossing signal from the TCLT1600 is on, count his duration.
        zeroCrossingLength++;
    }
    
   var_sys.Control50or60hz ++; // analisar a frequencia se é 50 ou 60 hz
   
   
    //<<< Zero crossing detection and triac OFF Guarantee before zero crossing
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    //>>> Implementation of the ignition phase of the triac for power control.
    //stateMotor_enum stateMotor=VerifyElectricalBrake(var_sys.StateMotor);
    stateMotor = VerifyElectricalBrake(var_sys.StateMotor);
    // rev 1.149 - Improvement of the electric brake. It will put a half rectified wave on both directions (DC voltage supply).
    if ( var_sys_NVM.electricBrake==1 && ts_system.TimeElectricBrake>0 && ts_system.TimeStopElectricBrake<=0 )  // rev 1.156
    {
        // Operation on the electric brake time. It has to apply a half rectified wave on both directions.
        if(stateMotor !=0 && StateTRIAC==1 && ts_system.ts_TRIACWait<=0 && powerControl_st.actualCycle==0 && ts_system.TimeElectricBrake<(TimeElectricalBrake-(5*TIME_100MS)) )
        {
           TRIAC_SetHigh();
           ts_system.ts_TRIACWait=-(25*DelayTRIACWait_20MS);//VALOR NEGATIVO - Inicializa a waitTRIAC para esperar sempre 20 milisegundos apos o ultimo ligar do triac para desligar o Relé
           var_sys.TriacON=YES;
           StateTRIAC=0;
        }
    }
    else
    {
        // Normal operation.
        if(stateMotor !=0 && ts_system.ts_TimeSlotTRIAC<difTime && StateTRIAC==1 && ts_system.ts_TRIACWait<=0 && var_sys.InStoping==NO)
        {
           TRIAC_SetHigh();
           ts_system.ts_TRIACWait=-DelayTRIACWait_20MS;//VALOR NEGATIVO - Inicializa a waitTRIAC para esperar sempre 20 milisegundos apos o ultimo ligar do triac para desligar o Relé
           var_sys.TriacON=YES;
           StateTRIAC=0;
        }
    }

    if (((ts_system.ts_TimeSlotTRIAC <= Timesecurityturnoofftriac )&& ts_system.TimeElectricBrake<0) || (stateMotor==0))
    {
//        if ( difTime <= TimeToTurnOffTriac )
//        {
        
//        EUSART_Write_String("DESLIGA O TRIAC \n");
//        EUSART_Write(ts_system.ts_TimeSlotTRIAC);
            TRIAC_SetLow();     // This way we guarantee that the triac has an OFF order when the zero cross happens.
            var_sys.TriacON=NO; // This will ensure that the ON order doesn't goes into the next semi-cycle.
//        }
    }
    //<<< Implementation of the ignition phase of the triac for power control.
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    
    
//    //stateMotor_enum stateMotor=VerifyElectricalBrake(var_sys.StateMotor);
//    stateMotor = VerifyElectricalBrake(var_sys.StateMotor);
    //Decrementa ou incrementa a variavel de de controlo para que os Relés não liguem ou desliguem com tensão do triac activa.
    if(stateMotor !=0 && ts_system.ts_TRIACWait>0)
    {
        ts_system.ts_TRIACWait--;
    }
    else if(stateMotor ==0 && ts_system.ts_TRIACWait<0)
    {
        ts_system.ts_TRIACWait++;
    }

}unsigned char  GetMotorPower()  // foi alterado por causo do softstop 
{
//    unsigned char temppower;
    unsigned char defineatraso;
//    unsigned char fullmotorPower;
    
    
    //Em decelaração a velocidade é definida noutro parametro e não sofre influencia do velocityFactor
    if(powerControl_st.decelarationActive==YES)
    {
       temppower=(var_sys_NVM.motorPower*VelocidadeMinima);
    }
    else
    {
        fullmotorPower=(var_sys_NVM.motorPower*VelocidadeMinima);
     
        if(var_sys.velocityFactor>0)
        {
            if(var_sys.velocityFactor>fullmotorPower)
            {
                temppower=1;
            }
            else
            {
        
                temppower =fullmotorPower-var_sys.velocityFactor;
            }
        }
        else if ((var_sys.velocityFactor <=0)&&(var_sys.velocityFactorstop <=0))
        {
            temppower =fullmotorPower;
            
            // Guarantee that for the full power the triac is full ON after the softstart.
            if ( var_sys_NVM.motorPower>8 )
            {
                temppower = TimeToTurnOffTriac-AtrasoNaVelocidade+1;
            }
        }
        else if ((var_sys.velocityFactorstop > 0)){  //V1.156 barreira_br 2016.11.25

     
           
                temppower = var_sys.velocityFactorstop;//10;

        }
    }
    if ((var_sys.velocityFactorstop > 0)&&(var_sys.velocityFactor <= 0 )){ //V1.156 barreira_br 2016.11.25
    defineatraso = AtrasoNaVelocidadeStop;    
    }
    else
    {
    defineatraso = AtrasoNaVelocidade;    
    }
    
    return temppower+defineatraso;  
}   


void ControlDecelarationFactor()
{
    powerControl_st.decelarationCyclesOn=1;
    powerControl_st.decelarationCyclesOff=2;
    powerControl_st.decelarationPower=var_sys_NVM.velocityDecelaration*var_sys.Torquerelanty;
}

bool getStateOpenPosition(stateMotor_enum stateMotor)
{
    bool state=false;
    if(var_sys.PositionIsLost==YES)
    {
        state=true;
    }
    else if((var_sys_NVM.learningTimeToOpen>(unsigned long)(var_sys_NVM.walkTime*TIME_1S)) && stateMotor==InOpenWalk)
    {
        if(var_sys_NVM.walkTime<(var_sys_NVM.decelarationOpen/2))
        {
            state= true;
        }
        else  if(var_sys.PositionActual>((signed long)(var_sys_NVM.walkTime*TIME_1S) - TIME_1S*2))//+var_sys.errorOpening
        {
            state= true;
        }
        else
        {
            state= false;
        }
    }
    else if( stateMotor==InOpenWalk ||  stateMotor==InOpenFull)
    {
         if((var_sys_NVM.learningTimeToOpen)<(((unsigned long)var_sys_NVM.decelarationOpen*TIME_500MS)))//+var_sys.errorOpening
        {
            state= true;
        }
        else if(var_sys.PositionActual>(getTimeDecelaration(stateMotor)))
        {
            state= true;
        }
        else
        {
            state= false;
        }
    }
    return state;
}

bool getStateClosePosition(stateMotor_enum stateMotor)
{
    bool state=false;
    if(var_sys.PositionIsLost==YES)
    {
        state=true;
    }
    else if(stateMotor==InClose)
    {
      if(var_sys.PositionActual<getTimeDecelaration(InClose))
      {
            state=true;
      }
    }
    return state;
}

void controlVelocity(void)
{

    //Quando estamos a fazer o learning da desacelaração
    if(var_sys.LearningIsEnabled==YES && var_sys.LearningDecelaration==YES)
    {
        if(powerControl_st.decelarationActive==NO)
        {
            ts_system.TimeStopedBeforeDecelaration=TIME_500MS;
            ts_system.TimeCurrentWaitForAlarm=TIME_1S;
        }
        ControlDecelarationFactor();
        powerControl_st.decelarationActive=YES;
        var_sys.velocityFactor=0;   
    }
    //Quando estamos a fazer o learning sem decelaração
    else if(var_sys.LearningIsEnabled==YES || var_sys.StartFromButton==YES)
    {
        var_sys.velocityFactor=0;
        powerControl_st.decelarationActive=NO;
    }
    //Valido quando a desacelaração no fecho está activa
    else if(var_sys.StateMotor==InClose && ((((signed long)var_sys.PositionActual)<(getTimeDecelaration(InClose)) || var_sys.PositionIsLost==YES) && ((var_sys_NVM.decelarationClose != 0 && var_sys.AutoInversionActiveStop == NO) || ((var_sys.velocityFactorstop <= 0) && var_sys_NVM.softstop >0))))
    {

            if ((powerControl_st.decelarationActive==NO) && (var_sys.AutoInversionActiveStop==NO ))
                {
                    
                    //ts_system.TimeStopedBeforeDecelaration=TIME_500MS;
                    ts_system.TimeCurrentWaitForAlarm=TIME_1S;
                    
                    if (var_sys_NVM.softstop > 0){
                        var_sys.AutoInversionActive = NO;
                        var_sys.AutoInversionActiveStop = YES;
                        InitSoftStop(); //V1.156 barreira_br 2016.11.25
                          
                    }
                    else
                    {
                        ts_system.TimeStopedBeforeDecelaration=TIME_500MS;
                        ControlDecelarationFactor();
                        powerControl_st.decelarationActive=YES;
                        var_sys.velocityFactor=0;   
                         var_sys.AutoInversionActiveStop = NO;
                    }
                }
           
                if ((var_sys.velocityFactorstop <= 0)&&(var_sys.AutoInversionActiveStop == YES) && (var_sys_NVM.softstop > 0))
                {
                ts_system.TimeStopedBeforeDecelaration=TIME_100MS;        
                var_sys.AutoInversionActiveStop = NO;
                ControlDecelarationFactor();
                powerControl_st.decelarationActive=YES;
                var_sys.velocityFactor=0;
                }
            
}
    //Valido quando a desacelaração na abertura está activa
    else if((getStateOpenPosition(var_sys.StateMotor)==true)&& ((var_sys_NVM.decelarationOpen != 0 && var_sys.AutoInversionActiveStop == NO) || (var_sys.velocityFactorstop <= 0) && var_sys_NVM.softstop > 0))
    {
        
            if ((powerControl_st.decelarationActive==NO) && (var_sys.AutoInversionActiveStop==NO ))
        {

            //ts_system.TimeStopedBeforeDecelaration=TIME_500MS;
            ts_system.TimeCurrentWaitForAlarm=TIME_1S;

            if (var_sys_NVM.softstop > 0){
                var_sys.AutoInversionActive = NO;
                var_sys.AutoInversionActiveStop = YES;
                InitSoftStop(); //V1.156 barreira_br 2016.11.25
            }else{
                ts_system.TimeStopedBeforeDecelaration=TIME_500MS;
                 var_sys.AutoInversionActiveStop = NO;
                ControlDecelarationFactor();
                powerControl_st.decelarationActive=YES;
                var_sys.velocityFactor=0;   
                 
            }
        }        
        if ((var_sys.velocityFactorstop <= 0)&&(var_sys.AutoInversionActiveStop == YES) && (var_sys_NVM.softstop > 0))
        {
        ts_system.TimeStopedBeforeDecelaration=TIME_100MS;        
        var_sys.AutoInversionActiveStop = NO;
        ControlDecelarationFactor();
        powerControl_st.decelarationActive=YES;
        var_sys.velocityFactor=0;
        }
          
    }
    else if (var_sys.velocityFactorstop>0 && var_sys.StateMotor !=Stopped )
    {
        var_sys.velocityFactorstop=(var_sys.velocityFactorstop)- var_sys.SoftStopDecrementControl;
        powerControl_st.decelarationActive=NO;
        
      
    }
    //controlo do soft start.
    else if(var_sys.velocityFactor>0 && var_sys.StateMotor !=Stopped )
    {
        var_sys.velocityFactor=(var_sys.velocityFactor)-var_sys.SoftStartDecrementControl;
        powerControl_st.decelarationActive=NO;
        
       
    }
    //Velocidade a topo.
    else
    {
         var_sys.velocityFactorstop = 0;
         var_sys.velocityFactor=0;
         powerControl_st.decelarationActive=NO;
    }
}

signed long getTimeDecelaration(stateMotor_enum state)
{
    
    if(state==InClose)
    {
        if (var_sys_NVM.TypeofMotor != 2)
        {return (signed long)((signed long)var_sys_NVM.decelarationClose*TIME_500MS);}
        else{return (signed long)((signed long)var_sys_NVM.decelarationClose*TIME_50MS*4);}
   }
    else
    {
        if (var_sys_NVM.TypeofMotor != 2)
        {return (signed long)((signed long)var_sys_NVM.learningTimeToOpen-(((signed long)var_sys_NVM.decelarationOpen*TIME_500MS)));}
        else{return (signed long)((signed long)var_sys_NVM.learningTimeToOpen-(((signed long)var_sys_NVM.decelarationOpen*TIME_50MS*4)));}
    }
}

stateMotor_enum VerifyElectricalBrake(stateMotor_enum actualState)
{
    stateMotor_enum tempState;
    tempState=actualState;
    if(var_sys_NVM.electricBrake==1 && actualState==Stopped && ts_system.TimeStopElectricBrake<=0)  // rev 1.156
    {
        if(actualState!=brakeElectric_st.lastState && brakeElectric_st.ElectricBrakeIsActive==NO )
        {
            brakeElectric_st.ElectricBrakeIsActive=YES;
//            EUSART_Write_String("Travão Electrico\r\n");
            ts_system.TimeElectricBrake=TimeElectricalBrake;
           
        }
        else if(brakeElectric_st.ElectricBrakeIsActive==YES &&  ts_system.TimeElectricBrake>0)
        {
            tempState=InOpenFull;
//            if(brakeElectric_st.lastState==InClose && RelayClose_GetValue()==0)
//            {
//                tempState=InOpenFull;
//            }
//            else if((brakeElectric_st.lastState==InOpenFull || brakeElectric_st.lastState==InOpenWalk)&& RelayOpen_GetValue()==0)
//            {
//                tempState=InClose;
//            }
//            else
//            {
//                tempState=Stopped;
//            }
        }
        else
        {
            brakeElectric_st.lastState=Stopped;
            brakeElectric_st.ElectricBrakeIsActive=NO;
        }

    }
    else
    {
        brakeElectric_st.lastState=actualState;
        brakeElectric_st.ElectricBrakeIsActive=NO;
    }

    return tempState;
}

void ControlMotor (void)
{
    /// Confirma que o tempo de funcionamento do motor não é
    /// superior a 10 Segundos sobre o valor de inicialização do sistema.
    if((var_sys.TimeMaxMotorIsON<=0) && (var_sys.WorkTimeMaxAlarmState!=Clear) && (var_sys.LearningIsEnabled==NO) && (var_sys.PositionIsLost==NO)){
        var_sys.StateMotor = Stopped;
        var_sys.WorkTimeMaxAlarmState=EmAlarme;
        //EUSART_Write_String((char*)"Alarmecontrolmotor");
       // EUSART_Write(var_sys.LearningIsEnabled);
    }
    /// Limpa a flag a active sempre que o motor para caso este não entre em alarme.
    /// A flag EmAlarme vai ser limpa no State Idle da sm_ControlGate Bloqueando o sistema.
    else if(var_sys.WorkTimeMaxAlarmState==Active && var_sys.StateMotor == Stopped)
    {
         var_sys.WorkTimeMaxAlarmState=Clear;
    }

    //Esta verifica o estado do motor de acordo com o ElectricalBrake
    stateMotor_enum stateMotor=VerifyElectricalBrake(var_sys.StateMotor);
    if(stateMotor == Stopped )//Espera pelo que o triac esteja desligado a mais de 20 milisegundos
    {
        var_sys.InStoping = YES;//Para gantir que nao volta a ligar
        if(ts_system.ts_TRIACWait>=0)
        {
            RelayClose_SetLow();
            RelayOpen_SetLow();
            var_sys.Activatecounter = stoped ;
        }
    }
//    else if ( (var_sys_NVM.electricBrake==1) && (brakeElectric_st.ElectricBrakeIsActive==YES) && (var_sys.StateMotor==Stopped) && (stateMotor!=Stopped) && (ts_system.TimeElectricBrake>0) )  // rev 1.149
//    {
//        // Turn on both relays on the eletric brake time.
//        RelayClose_SetHigh();
//        RelayOpen_SetHigh();
//    }
    else if ( (var_sys_NVM.electricBrake==1) && (brakeElectric_st.ElectricBrakeIsActive==YES) && (var_sys.StateMotor==Stopped) && (stateMotor!=Stopped) && (ts_system.TimeElectricBrake>0) && (ts_system.TimeStopElectricBrake<=0) )  // rev 1.149  // rev 1.156
    {
        // Now we have to check if the triac off time previous to turning on the
        // other relay (so that both relays are on) has elapsed.
        if ( ts_system.TimeElectricBrake<(TimeElectricalBrake-(2*TIME_100MS)) )
        {
            // The time with previous rotation relay on with opositive relay off and triac off
            // has elapsed, now we can turn on the opositive relay.
            
            // Turn on both relays on the eletric brake time.
            RelayClose_SetHigh();
            RelayOpen_SetHigh();
            var_sys.Activatecounter = stoped ;
            
        }
        else
        {
            // Do nothing, maintain the relays on the previous state, so that we
            // implement a time with the triac off after turning on the other relay.
        }
    }
    //else if(((stateMotor == InOpenFull) || (stateMotor == InOpenWalk)) && ((var_sys.FimCurso_OpenIsEnabled == NO) &&  (RelayClose_GetValue()==0)))
    else if(((stateMotor == InOpenFull) || (stateMotor == InOpenWalk)) && ((var_sys.FimCurso_OpenIsEnabled == NO))) // rev 1.149
    {
        if((RelayClose_GetValue()==0 && var_sys_NVM.Direction_motor == 0)||(RelayOpen_GetValue()==0 && var_sys_NVM.Direction_motor == 1))
        {
            if((RelayOpen_GetValue()==0 && var_sys_NVM.Direction_motor == 0)||(RelayClose_GetValue()==0 && var_sys_NVM.Direction_motor == 1)) 
            {
                var_sys.InStoping = NO;
                ts_system.ts_TRIACWait=DelayTRIACWait_20MS;
                ts_system.TimeChargeCondesador=TIME_1S;
                if (var_sys.FimCurso_CloseIsEnabled == YES|| var_sys.Statedoorcontrol == st_Closed ){
                var_sys.TimeMaxMotorIsON=((unsigned int)var_sys_NVM.velocityDecelaration+((unsigned int)var_sys_NVM.decelarationOpen)*TIME_500MS)+var_sys_NVM.learningTimeToOpen + TIME_1S*4;
                //var_sys.WorkTimeMaxAlarmState=Active;
         
                
                }
                var_sys.Statedoorcontrol = st_Opening;
               
                
            }
            if (var_sys_NVM.Direction_motor == 0){RelayOpen_SetHigh();}
            else{RelayClose_SetHigh();}
            var_sys.Activatecounter = open ;   // increases every main timeslot (currently 50ms).
          
        }

           if (var_sys_NVM.Direction_motor == 0){RelayClose_SetLow();}
           else{RelayOpen_SetLow();}
        
    }
    //else if((stateMotor == InClose) && (var_sys.FimCurso_CloseIsEnabled == NO)&&(RelayOpen_GetValue()==0))
    else if((stateMotor == InClose) && (var_sys.FimCurso_CloseIsEnabled == NO))  // rev 1.149
    {
        if((RelayOpen_GetValue()==0 && var_sys_NVM.Direction_motor == 0)||(RelayClose_GetValue()==0 && var_sys_NVM.Direction_motor == 1))
        {
            if((RelayClose_GetValue()==0 && var_sys_NVM.Direction_motor == 0)||(RelayOpen_GetValue()==0 && var_sys_NVM.Direction_motor == 1))
            {
                var_sys.InStoping = NO;
                ts_system.ts_TRIACWait=DelayTRIACWait_20MS;
                ts_system.TimeChargeCondesador=TIME_1S;
                if (var_sys.FimCurso_OpenIsEnabled == YES|| var_sys.Statedoorcontrol == st_Opened){
                var_sys.TimeMaxMotorIsON=((unsigned int)var_sys_NVM.velocityDecelaration+(unsigned int)var_sys_NVM.decelarationClose*TIME_500MS)+var_sys_NVM.learningTimeToClose + TIME_1S*4;
                //var_sys.WorkTimeMaxAlarmState=Active;
                }
                var_sys.Statedoorcontrol = st_Closing;

            }
            if (var_sys_NVM.Direction_motor == 0){RelayClose_SetHigh();}
            else{RelayOpen_SetHigh();}
            var_sys.Activatecounter = close ;   // decreases every main timeslot (currently 50ms).
            
        }
           if (var_sys_NVM.Direction_motor == 0){RelayOpen_SetLow();}
           else{RelayClose_SetLow();}
    }
}

void ControlLights(void)
{
    if(var_sys.DistanceProgrammingActive==YES)
    {
        setFlashLigth_ON(TIME_1S);
    }
    else if(controlGate_stateMachine.current_state==st_Idle )
    {
        var_sys.ControlReleCapacitorOpen = 0; 
        var_sys.ControlReleCapacitorClose = 0;
        if (var_sys_NVM.flashLightMode !=3){
           RelayFlashlight_SetLow(); 
        }
        else{
           RelayFlashlight_SetHigh();  
        }
        
    }
    
    if (((var_sys.preflashingcontrol == YES || controlGate_stateMachine.current_state==st_Opened) && (ts_system.timeWaitToClose >0) && (ts_system.timeWaitToClose <= 3 * TIME_1S)) && var_sys_NVM.flashRGBMode == rgb_pre){
        setRGB_ON(BLUE,TIME_200MS);
  
    }  
    
//----------------------------------------Porta em Fecho-----------------------------------------------------------    
    else if(var_sys.StateMotor == InClose)  // v.156_ol
    {
        var_sys.ControlReleCapacitorOpen = 0; 
        
        
        if (var_sys.ControlReleCapacitorClose==0 && var_sys_NVM.flashRGBMode==rgb_capacitor)//&&(var_sys.LearningIsEnabled ==NO)) // foi adicionado esta variavel para controlar o segundo relé no começo do fecho
        {
         ts_system.TimeReleCapacitor = TIME_1S*2;   
            setRGB_ON(YELLOW,0);
         var_sys.ControlReleCapacitorClose = 1;
        }
        if(ts_system.TimeReleCapacitor<=0 && var_sys_NVM.flashRGBMode==rgb_capacitor)
        {
            
            //RGBO_YOff(); // Transcorrido o tempo o relé volta a desligar 
        }
        
        if(var_sys_NVM.flashRGBMode==rgb_pisca && ts_system.TimeReleCapacitor<=0)
          
        {
            setRGB_ON(RED,TIME_200MS +TIME_50MS);
        }
        else
        {
            setRGB_ON(RED,0);  
        }
        
        if(var_sys_NVM.flashLightMode==fixo)
        {
            //setFlashLigth_ON(TIME_1S*2);
            setFlashLigth_ON(TIME_500MS);      //rev1.149 blink fast closing and slow openning
           
        }
        else{
            setFlashLigth_ON(0);
        }

    }
    //------------------------------Porta Fechada---------------------------------------------------------
    else if(var_sys.StateMotor == Stopped && controlGate_stateMachine.current_state==st_Closed)
    {
        if(var_sys.preflashingcontrol != YES){
            SELECT_SetHigh();
        }

                   
                       
        if(var_sys_NVM.flashRGBMode==rgb_pisca)
        {
            if (var_sys_NVM.TypeofMotor == br || var_sys_NVM.TypeofMotor == SE)setRGB_ON(YELLOW,0);                                                                   //  Teste por central faze reset
            else setRGB_ON(YELLOW,TIME_1S*2);   
        }       
        else if (var_sys_NVM.flashRGBMode != rgb_capacitor) setRGB_ON(YELLOW,0);

        if (var_sys_NVM.flashLightMode != electroiman)//Controla Pirilampo
        {    
        if (ts_system.TimeOnFlashLigth>0) 
        {
            setFlashLigth_ON(0);
        }
        else
        {
            RelayFlashlight_SetLow();
            ts_system.timeFreqFlashligth=0;
        }
        }
    }
    
 //_----------------------------------------Porta parada-----------------------------------------------------------------------   
    else if(var_sys.StateMotor == Stopped)
    {
        if (( var_sys_NVM.autoTimeFullClose==0 && var_sys.StateMotor == InOpenFull)||((var_sys_NVM.autoTimeWalkClose==0) && var_sys_NVM.walkTime >0 && var_sys.StateMotor == InOpenWalk))
        {
            // Desliga pirilampo e RGB quando o portão está parado
            // e não existe fecho automático.
            var_sys.ControlReleCapacitorOpen = 0; //sempre que a porta para seja em qualquer ponto faz um reset ás variaveis
            var_sys.ControlReleCapacitorClose = 0;

            
            
            if (var_sys_NVM.flashLightMode != electroiman && var_sys_NVM.flashLightMode != condominio ){
              RelayFlashlight_SetLow();  
            }
              
        }
        else
        {
            if(var_sys_NVM.flashRGBMode==rgb_pisca)
            {
                setRGB_ON(BLUE,TIME_1S);
                  // rev 1.151 - Color corrected.
            }
            else
            {
                setRGB_ON(BLUE,0);
                  // rev 1.151 - Color corrected.
            }

            if(var_sys_NVM.flashLightMode==pisca ||var_sys_NVM.flashLightMode==electroiman)
            {
                 RelayFlashlight_SetLow();
            }
            else if (var_sys_NVM.flashLightMode == fixo || var_sys_NVM.flashLightMode == condominio)
            {
                setFlashLigth_ON(0);
            }
            

        }
        
        
    }
//-----------------------------------------Activa o Rele do condensador a Abrir -------------------------------------------------------------    
    else 
    {
        //Controla RGB
        var_sys.ControlReleCapacitorClose=0;   // porta está a abrir então coloca a variavel com tempo pré determinado
        if (var_sys.ControlReleCapacitorOpen==0 && var_sys_NVM.flashRGBMode==rgb_capacitor)//&&(var_sys.LearningIsEnabled ==NO))   // v.156_ol
        {
         ts_system.TimeReleCapacitor = TIME_1S*2;   
         //RGBO_YOn();
         var_sys.ControlReleCapacitorOpen = 1;
        }
        if(ts_system.TimeReleCapacitor <=0 && var_sys_NVM.flashRGBMode==rgb_capacitor)// transcorrido o tempo o relé desliga
        {
        //RGBO_YOff();
        }
//------------------------------------------Porta Aberta---------------------------------------------------        
        if (controlGate_stateMachine.current_state==st_Opened) 
        {
            // Desliga pirilampo e RGB quando o portão está parado
            // e não existe fecho automático.
            var_sys.ControlReleCapacitorOpen = 0; //sempre que a porta para seja em qualquer ponto faz um reset ás variaveis
            var_sys.ControlReleCapacitorClose = 0;
           // RGBO_ROff();
            //RGBO_GOff();
            if (var_sys_NVM.autoTimeFullClose != 0 || ((var_sys_NVM.autoTimeWalkClose!=0) && var_sys_NVM.walkTime >0)|| var_sys_NVM.operationMode==2)
            {
                   setRGB_ON(BLUE,0);
            }
            else
            {
               // RGBO_BOff();
                
                
            }
            //RGBO_YOff();
            RelayFlashlight_SetLow();
        }
        
//----------------------___________________--------------------Porta a Abrir---------------------------------------------------         
        else
        {
            
        
            if(var_sys_NVM.flashRGBMode==rgb_pisca)
            {
                setRGB_ON(GREEN,TIME_500MS); // rev 1.151 - Color corrected.
            }
            else
            {
                setRGB_ON(GREEN,0); // rev 1.151 - Color corrected.
                
            }

            if(var_sys_NVM.flashLightMode==fixo)
            {

                //setFlashLigth_ON(TIME_1S);
                setFlashLigth_ON(TIME_1S);    //rev1.149 blink fast closing and slow openning
            }
            else if (var_sys_NVM.flashLightMode == pisca || var_sys_NVM.flashLightMode == condominio)
            {
                setFlashLigth_ON(0);
            }

            if (var_sys_NVM.flashLightMode == electroiman)
            {
            RelayFlashlight_SetLow();

            }
        }
    }


}

void setRGB_ON(RGBY_enum RGBLigth,int Freq)
{

    SELECT_SetHigh(); 
     
//    if (var_sys_NVM.flashRGBMode != rgb_capacitor){
//    //RGBO_YOff();
//    }

    if(Freq==0 ||  var_sys.upFaseRGB==1)
    {

        switch (RGBLigth)
        {
            case RED:
                RGB_Set(RGBO_ROn);
            break;
            case GREEN:
              
                RGB_Set(RGBO_GOn); // rev 1.151
            break;
            case BLUE:
                //RGBO3_SetLow();
                RGB_Set(RGBO_BOn); // rev 1.151
            break;
            case YELLOW:
                //RGBO4_SetLow();
                RGB_Set(RGBO_YOn); // rev 1.151
            break;

        }
    }

    if(ts_system.timeFreqRGB<=0 && Freq!=0)
    {
        ts_system.timeFreqRGB=Freq;
        if(var_sys.upFaseRGB==1)
        {
            var_sys.upFaseRGB=0;
        }
        else
        {
            var_sys.upFaseRGB=1;
            
        }
    }
    //RelayFlashlight_Toggle();
}

void setFlashLigth_ON(int Freq)
{
    if(Freq==0 ||  var_sys.upFaseFlashligth==1)
    {
        RelayFlashlight_SetHigh();
    }
    else
    {
        RelayFlashlight_SetLow();
    }

    if(ts_system.timeFreqFlashligth<=0 && Freq!=0)
    {
        ts_system.timeFreqFlashligth=Freq;
        var_sys.upFaseFlashligth ^= (1 << 0);
    }
}
