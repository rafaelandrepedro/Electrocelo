
//
//******************************************************************************


/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdio.h>
#include <stdlib.h>

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "mcc_generated_files/i2c1_master.h"
#include "mcc_generated_files/pin_manager.h"
#include "main.h"
#include "inputs.h"
#include "outputs.h"
#include "controlMemory.h"
#include "controlCurrent.h"
#include "sm_common.h"
#include "sm_MenuConfiguration.h"
#include "sm_Main.h"
#include "sm_ControlGate.h"
#include "sm_ControlLearning.h"

#include "eusartpackage.h"
#include "eusartparser.h"


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/
/* i.e. uint8_t <variable_name>; */

volatile timeslotSystem ts_system;
volatile varSystem_NVM var_sys_NVM;
volatile varSystem var_sys;
volatile display_st dispStruct;
volatile BUTTONS_STRUCT button_struct;
volatile RF_KEY_STRUCT rfCMD;
sm_t menuConfiguration_stateMachine;
sm_t main_stateMachine;
sm_t controlGate_stateMachine;
sm_t controlLearning_stateMachine;
char lastKey;
extern PowerControlStruct powerControl_st;




/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{



   // asm("CLRWDT");

    dispStruct.display_grp.value_display1=dMinus;
    dispStruct.display_grp.value_display1=dMinus;
    dispStruct.intermitentFreq=0;
    dispStruct.upFase=1;

    
    SYSTEM_Initialize();    
    WWDT_SoftEnable();

    // Enable the Global Interrupts
      INTERRUPT_GlobalInterruptEnable();


     INTERRUPT_PeripheralInterruptEnable();
     

    IOCBP3=1;
    IOCBN3=1;
    

//    EUSART1_Write('n');
   


    InitReceiver();
    loadNVM_VarSystem();

    WWDT_TimerClear();

    SetSegmentValue(dMinus,dMinus);
    ts_system.ts_TimeSlot1ms = TIME_100MS;
    while ( ts_system.ts_TimeSlot1ms > 0 )
    {
        if ( ts_system.ts_TimeSlotMain<=0 )
        {
            WWDT_TimerClear();
            ts_system.ts_TimeSlotMain = MAIN_TIMESLOT;
            
            ts_system.ts_TimeSlot1ms--;
            readInputs();//Actaliza o estados das entradas
        }
    }
    //<<< rev1.149:

    
//    EUSART1_Write('i');
//    EUSART1_Write('n');
    sm_init(&menuConfiguration_stateMachine,st_MainMenu,HIST_NONE);
    sm_init(&main_stateMachine,st_standBy,HIST_NONE);
    sm_init(&controlGate_stateMachine,st_Idle,HIST_NONE);
    sm_init(&controlLearning_stateMachine,st_InitLearning,HIST_NONE);

    ts_system.Debug_TS=TIME_1S;
    
    var_sys.ADCZeroOffset               = ZERO_VALUE_ADC;
    ts_system.TimeStopADCZeroOffsetCalc = (5*TIME_1S);  // DM: Do not acquire de ADC Offset fot at least 5 seconds.
    ts_system.TimeStopElectricBrake     = 0;    // rev 1.156

    //char tempBuffer[30];
    var_sys.StateMotor = Stopped;
    
    #ifdef  TEST_RESET
    var_sys.showReset = false;
    #endif

    while(1)
    {
        //uint8_t a=EUSART1_Read();
        //EUSART1_Write(a);
        //EUSART1_Write('A');
        struct package_t package;
        if(EUSART1_is_rx_ready()){
            package=read_package();
            eusartparser(&package);
        }
        //eusartparser(&package);

        if ( ts_system.ts_TimeSlotMain<=0 )
        {
             ts_system.ts_TimeSlotMain = MAIN_TIMESLOT;
            WWDT_TimerClear();
   
            if(var_sys.StateVersion<4)  // If there is no debug on the Reset information.
  
            {
                ShowVersion();
            }
            else
            {
                
                readbutton();   // Read the pressed buttons on the controller hardware.

                readRFButtons();// Read the pressed RF buttons.
               lastKey=getKeyPressed();//Lé a  ultima tecla pressionada. 
                
                readInputs();//Actaliza o estados das entradas
                ControlInputs();//Confirma o estado das saídas e força a paragem do motor.
                ControlCurrent();//Controla os cosumos do motor e gera alarmes quandos limites são superados
                controlVelocity();//Controla a velocidade do motor de acordo com a posição e parametros configurados
                ControlMotor();//Controla o estado e a direcção do motor.
                ControlLights();//Controla o pirilampo e o RGB
                ControlCounterMoves();//Controla o guardar do numero de manobras.

                sm_execute_main(&main_stateMachine);//Gere o que é presentado no LCD e navegação entre menus
                sm_execute_ControlGate(&controlGate_stateMachine);// Gere o estado do motor e as trasições entre estados.


                if(lastKey!=0xff)//Verifica se alguma tecla foi pressionado e limpa a tecla pressionada
                {
                    //getSerialCmd(&serialTemp);
                      InitReceiver();  

                  
                }
            }           
        }
    }

}

void controlTimeslots(void)
{
	decrementTimeslot((int*)&ts_system.Debug_TS);
    decrementTimeslot((int*)&ts_system.timewaitFlashRGB);
    decrementTimeslot((int*)&ts_system.timeFreqDigit);
    decrementTimeslot((int*)&ts_system.timeSinalizationDigit);
    decrementTimeslot((int*)&ts_system.timeoutMenu);
    decrementTimeslot((int*)&ts_system.timeOpenWalk);
    decrementTimeslot((int*)&ts_system.timeWaitToClose);
    decrementTimeslot((int*)&ts_system.TimeLastCommand);
    decrementTimeslot((int*)&ts_system.timeSoftStart);
    decrementTimeslot((int*)&ts_system.TimeChargeCondesador);
    //decrementTimeslot((int*)&ts_system.timeForNextDecelaration);
    decrementTimeslot((int*)&ts_system.timeFreqRGB);
    decrementTimeslot((int*)&ts_system.timeFreqFlashligth);
        
    decrementTimeslot((int*)&ts_system.TimeWaitToNextState);
    //decrementTimeslot((int*)&ts_system.TimeDecelaration);
    decrementTimeslot((int*)&ts_system.timeBetweenSaveCounters);
    decrementTimeslot((int*)&ts_system.TimeElectricBrake);
    decrementTimeslot((int*)&ts_system.TimeCurrentAlarm);
   // decrementTimeslot((int*)&ts_system.TimeMaxMotorIsON);
    decrementTimeslot((int*)&ts_system.TimeStopedBeforeDecelaration);
    decrementTimeslot((int*)&ts_system.TimeCurrentWaitForAlarm);
    decrementTimeslot((int*)&ts_system.TimeInversionStart);
    decrementTimeslot((int*)&ts_system.TimeReleCapacitor);
    decrementTimeslot((int*)&ts_system.TimeWaitReleCapacitor);
 
    

    //decrementTimeslot((int*)&ts_system.InvertionTimeClosingFromOpen);
    if ( ( var_sys_NVM.electricBrake==0 ) || ( ts_system.TimeElectricBrake<=0 ) ) // rev 1.150
    {
        // With the eletric brake active, this time will not be decremented, so
        // that is not affected by the brake time.
        decrementTimeslot((int*)&ts_system.InvertionTimeClosingFromOpen);
    }
    
    decrementTimeslot((int*)&ts_system.TimeWaitToGetCurrent);
    decrementTimeslot((int*)&ts_system.TimeLearningDecelaration);
    decrementTimeslot((int*)&ts_system.TimeTransitionDecelaration);

    decrementTimeslot((int*)&ts_system.timewaitBeforeSoftStart);
    decrementTimeslot((int*)&ts_system.TimeShowVersion);
    
    decrementTimeslot((int*)&ts_system.TimeStopADCZeroOffsetCalc);

    decrementTimeslot((int*)&ts_system.TimeStopElectricBrake);  // rev 1.156

    //Uso esta condição porque o TimeOnFlashLight é um long.
    if (ts_system.TimeOnFlashLigth>0)
    {
        ts_system.TimeOnFlashLigth--;
    }
}

void decrementTimeslot(int * ts)
{
    if (ts[0]>0)
    {
        ts[0]--;
    }
}

void ShowVersion(void)
{
    if(ts_system.TimeShowVersion<=0)
    {
     
            if(var_sys.StateVersion==0)
            {
                SetSegmentValue((VERSION_ERIS/10)%10,(VERSION_ERIS/1)%10);//Show Version "u1"
            }
            else if(var_sys.StateVersion==1)
            {
                SetSegmentValue(dr, (REVISION_ERIS/100)%10);//Show Revision parte Centenas "r1"
            }
            else if(var_sys.StateVersion==2)
            {
                SetSegmentValue((REVISION_ERIS/10)%10,(REVISION_ERIS/1)%10);//Show Revision parte dezenas e unidade "37"
            }
             else if (var_sys.StateVersion==3)
            {
               SetSegmentValue(dr, d2);//Show Revision parte Centenas "r1" 
                // Do nothing!
            }
            else
            {
                // Do nothing!
            }
       

        var_sys.StateVersion++;
        ts_system.TimeShowVersion=TIME_1S;
    }
}

