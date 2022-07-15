#include <xc.h>
#include <stdio.h>
#include "main.h"




#include "sm_common.h"
#include "sm_ControlGate.h"
#include "sm_ControlLearning.h"
#include "outputs.h"
#include "inputs.h"
#include "sm_MenuConfiguration.h"
#include "sm_Main.h"
#include "controlMemory.h"
#include "mcc_generated_files/eusart.h"

extern sm_t controlGate_stateMachine;
extern sm_t controlLearning_stateMachine;
extern volatile varSystem_NVM var_sys_NVM;
extern volatile varSystem var_sys;
extern volatile timeslotSystem ts_system;
volatile LearnStruct learn_st;
unsigned char control_limit_switch = 0;
extern volatile BUTTONS_STRUCT button_struct;
extern volatile RF_KEY_STRUCT rfCMD;


void sm_execute_ControlLearning(sm_t* psm){
 
   TypeCMD typeOpenOrder = GetOpenOrder();
    //>>> State transitions
    switch((sm_state_ControlLearning_t) psm->current_state)
    {
        case st_InitLearning:
        {
             if((psm->last_event==ev_GateClosed)&&(var_sys_NVM.decelarationSensivity != 0)&& (var_sys.programinAutomatic == 0))
            {
                psm->current_state = st_WaitLearnigOpen;
               // EUSART_Write_String("WaitLearnigOpen");
            }
            else if((psm->last_event==ev_GateClosed)&&(var_sys_NVM.decelarationSensivity == 0 || var_sys.programinAutomatic == 1))
            {
                psm->current_state = st_WaitForOpened; 
            }
            else if(psm->last_event==ev_GateOpened)
            {
                psm->current_state = st_WaitForClosed;
            }
        }
        break;
        case st_WaitForClosed:   // Esta maquina de estado foi alterada para que quando a sensibelidade estiver a "0" não faça programaçao de currente em abrandamento
        {
            if((psm->last_event==ev_GateClosed)&&(var_sys_NVM.decelarationSensivity != 0) && (var_sys.programinAutomatic == 0))
            {
                psm->current_state = st_WaitLearnigOpen;
                
            }
            else if((psm->last_event==ev_GateClosed)&&(var_sys_NVM.decelarationSensivity == 0 || var_sys.programinAutomatic == 1))
            {
                psm->current_state = st_WaitForOpened; 
            }
            else if(psm->last_event==ev_ErrorGate)
            {
                psm->current_state = st_InitLearning;
            }
        }
        break;
        case st_WaitLearnigOpen:
        {
            if(psm->last_event==ev_GateOpened)
            {
                psm->current_state = st_WaitLearnigClose;
            }
            else if(psm->last_event==ev_ErrorGate)
            {
                psm->current_state = st_InitLearning;
            }
        }
        break;
        case st_WaitLearnigClose:
        {
            if(psm->last_event==ev_GateClosed)
            {
                psm->current_state = st_WaitForOpened;
            }
            else if(psm->last_event==ev_ErrorGate)
            {
                psm->current_state = st_InitLearning;
            }
        }
        break;
        case st_WaitForOpened:
        {
            if(psm->last_event==ev_GateOpened)
            {
                psm->current_state = st_WaitForEndLearn;
            }
            else if(psm->last_event==ev_ErrorGate)
            {
                psm->current_state = st_InitLearning;
            }
        }
        break;
        case st_WaitForEndLearn:
        {
            if(psm->last_event==ev_GateClosed)
            {
                psm->current_state = st_InitLearning;
            }
            else if(psm->last_event==ev_ErrorGate)
            {
                psm->current_state = st_InitLearning;
            }
        }
        break;
        default:
        {
            while(1)
            {
                //asm("CLRWDT");  // DM: Make a WDT reset if the state machine is lost.
            }
        }
        break;
    }
    sm_send_event(&controlLearning_stateMachine, ev_NULL);
    //<<< State transitions.

    
    //>>> State implementations
    switch((sm_state_ControlGate_t) psm->current_state)
    {
        case st_InitLearning:
        {
            if(var_sys.FimCurso_CloseIsEnabled==YES)
            {
                control_limit_switch = 1;
                sm_send_event(&controlLearning_stateMachine, ev_GateClosed);
                var_sys.StateMotor=InOpenFull;
                clearLearningValue();
                 if ((var_sys_NVM.decelarationSensivity != 0) && (var_sys.programinAutomatic == 0)) // esta condiçao foi adicionada para que quando a sensibelidade no relanty esta 0 não fazer programaçao de currente
                         {
                ts_system.TimeLearningDecelaration=TIME_1S*15;
                ts_system.TimeWaitToGetCurrent=TIME_1S*6;
                ts_system.TimeWaitReleCapacitor = TIME_1S;
                var_sys.LearningDecelaration=YES;
                control_limit_switch = 0;
                 }
                else
                {
                var_sys.LearningDecelaration=NO;
                ts_system.TimeWaitToGetCurrent=TIME_1S*4;
                ts_system.TimeWaitReleCapacitor = TIME_1S;  
                control_limit_switch = 0;
                }
                
            }
            else
            {
                sm_send_event(&controlLearning_stateMachine, ev_GateOpened);
                var_sys.StateMotor          = InClose;
                var_sys.LearningDecelaration= YES;  // Seek the closed position with reduced speed.
            }
        }
        break; 
        case st_WaitForClosed:
        {
            if(((var_sys.FimCurso_CloseIsEnabled==YES)||(control_limit_switch == 1)) || ((button_struct.current == BTN_MENU ||typeOpenOrder == TypeFull) && var_sys.programinAutomatic == 1))
            {

                control_limit_switch = 1;
                var_sys.StateMotor=Stopped;
                if(ts_system.TimeWaitToNextState<=0)
                {
                    sm_send_event(&controlLearning_stateMachine, ev_GateClosed);
                    var_sys.StateMotor=InOpenFull;
                    clearLearningValue();
                        if ((var_sys_NVM.decelarationSensivity != 0) && (var_sys.programinAutomatic == 0)) // esta condiçao foi adicionada para que quando a sensibelidade no relanty esta 0 não fazer programaçao de currente
                        {
                        ts_system.TimeLearningDecelaration=TIME_1S*15;
                        ts_system.TimeWaitToGetCurrent=TIME_1S*6;
                        ts_system.TimeWaitReleCapacitor = TIME_1S;
                        var_sys.LearningDecelaration=YES;
                        control_limit_switch = 0;
                        }
                        else
                        {
                        var_sys.LearningDecelaration=NO;
                        ts_system.TimeWaitToGetCurrent=TIME_1S*4;
                        ts_system.TimeWaitReleCapacitor = TIME_1S;  
                        control_limit_switch = 0;
                        }
                }    
            }
            else if(var_sys.StateMotor==Stopped)
            {
                generateErrorLearnig();
            }
            else
            {
                ts_system.TimeWaitToNextState=(2*TIME_1S);
            }
        }
        break;
        case st_WaitLearnigOpen:
        {
            if((var_sys.FimCurso_OpenIsEnabled==YES) || (ts_system.TimeLearningDecelaration<=0)||(control_limit_switch == 1))
                
            {
                 control_limit_switch = 1;
                var_sys.StateMotor=Stopped;
            if(ts_system.TimeWaitToNextState<=0)
            {
               // EUSART_Write_String((char*)"fim de curso");
                sm_send_event(&controlLearning_stateMachine, ev_GateOpened);
                var_sys.StateMotor=InClose;
                ts_system.TimeLearningDecelaration=TIME_1S*5;
                ts_system.TimeWaitToGetCurrent=TIME_1S*5;
                ts_system.TimeWaitReleCapacitor = TIME_1S;
                control_limit_switch = 0;
            }
            }
            else if(var_sys.StateMotor==Stopped)
            {
                //EUSART_Write_String((char*)"errorlearning");
                generateErrorLearnig();
                
            }
            else
            {
                ts_system.TimeWaitToNextState=(2*TIME_1S);
                if (ts_system.TimeWaitReleCapacitor <=0)
                {
                if(ts_system.TimeWaitToGetCurrent>0)
                {
                    learn_st.openHistCurrent=calculateMean(learn_st.openHistCurrent,var_sys.ActualHistCurrent);
                }
                }
            }
        }
        break;
        case st_WaitLearnigClose:
        {
            if((var_sys.FimCurso_CloseIsEnabled==YES)||(control_limit_switch == 1))
            {
                control_limit_switch = 1;
                var_sys.StateMotor=Stopped;
                if(ts_system.TimeWaitToNextState<=0)
                {
                    sm_send_event(&controlLearning_stateMachine, ev_GateClosed);
                    var_sys.StateMotor=InOpenFull;
                    var_sys.LearningDecelaration=NO;
                    ts_system.TimeWaitToGetCurrent=TIME_1S*3;
                    ts_system.TimeWaitReleCapacitor = TIME_1S;
                    control_limit_switch = 0;
                    // sprintf(tempBuffer2,"tempo learning %d%d %d%d\r\n",learn_st.timeOpen,var_sys_NVM.learningTimeToClose);
                    //EUSART_Write_String(tempBuffer2);
                }
            }
            else if(var_sys.StateMotor==Stopped)
            {
                generateErrorLearnig();
            }
            else
            {
                ts_system.TimeWaitToNextState=(2*TIME_1S);
                if (ts_system.TimeWaitReleCapacitor <=0)
                {
                if(ts_system.TimeWaitToGetCurrent>0)
                {
                    learn_st.closeHistCurrent=calculateMean(learn_st.closeHistCurrent,var_sys.ActualHistCurrent);
                }
                }
            }
        }
        break;
        case st_WaitForOpened:
        {
            if(((var_sys.FimCurso_OpenIsEnabled==YES)||control_limit_switch == 1)||(var_sys.LearningDecelaration==YES && (button_struct.current == BTN_MENU ||typeOpenOrder == TypeFull) && var_sys.programinAutomatic == 1))
            {
              
                var_sys.Counter_Learning = 0;
                var_sys.LearningDecelaration = NO;
                control_limit_switch = 1;
                var_sys.StateMotor=Stopped;
                if(ts_system.TimeWaitToNextState<=0)
                {
                    sm_send_event(&controlLearning_stateMachine, ev_GateOpened);
                    var_sys.StateMotor=InClose;
                    ts_system.TimeWaitToGetCurrent=TIME_1S*4;
                    ts_system.TimeWaitReleCapacitor = TIME_1S;
                    control_limit_switch = 0;
                    
                    // sprintf(tempBuffer2,"tempo learning %d%d %d%d\r\n",learn_st.timeOpen,var_sys_NVM.learningTimeToClose);
                    // EUSART_Write_String(tempBuffer2);
                }
            }
            else if(var_sys.StateMotor==Stopped)
            {
                generateErrorLearnig();
            }
            else if((button_struct.current == BTN_MENU || typeOpenOrder == TypeFull) && var_sys.programinAutomatic == 1 && var_sys.LearningDecelaration== NO){
                var_sys.LearningDecelaration=YES;
    
               
                button_struct.processed = 1;
                ts_system.TimeWaitToGetCurrent=TIME_1S*4;
                
            }
            else if (var_sys.LearningDecelaration == YES){

                
                ts_system.TimeWaitToNextState=(2*TIME_1S);
 
                if(ts_system.TimeWaitToGetCurrent>0)
                {
                    learn_st.openHistCurrent=calculateMean(learn_st.openHistCurrent,var_sys.ActualHistCurrent);
                }
                
            }
            else
            {
                var_sys.Counter_Learning = 1;
                ts_system.TimeWaitToNextState=(2*TIME_1S);             
                
                if (ts_system.TimeWaitReleCapacitor <=0)
                {
                if(ts_system.TimeWaitToGetCurrent>0)
                {
                    learn_st.openCurrent=calculateMean(learn_st.openCurrent,var_sys.ActualCurrent);
                }
                }
            }
        }
        break;
        case st_WaitForEndLearn:
        {
            if((var_sys.FimCurso_CloseIsEnabled==YES)||( var_sys.LearningDecelaration==YES && (button_struct.current == BTN_MENU || typeOpenOrder == TypeFull) && var_sys.programinAutomatic == 1))
            {

              
                var_sys.Statedoorcontrol = st_Closed;
                var_sys.Counter_Learning = 0;
                var_sys.LearningDecelaration = NO;
                var_sys.StateMotor=Stopped;
                sm_send_event(&controlLearning_stateMachine, ev_GateClosed);
                sm_send_event(&controlGate_stateMachine, ev_LearningComplete);
                var_sys_NVM.learningTimeToClose=learn_st.timeClose;
                var_sys_NVM.learningTimeToOpen=learn_st.timeOpen;
                if (var_sys.programinAutomatic == 1){
                    var_sys_NVM.decelarationClose=learn_st.timeDecelerationClose ;
                    var_sys_NVM.decelarationOpen=learn_st.timeDecelerationOpen ; 
                                }
                else{
                    var_sys_NVM.decelarationClose=4 ;
                    var_sys_NVM.decelarationOpen=4 ;
                }
                var_sys_NVM.learningCurrentNormalClose=learn_st.closeCurrent;
                var_sys_NVM.learningCurrentNormalOpen=learn_st.openCurrent;
                var_sys_NVM.learningCurrentDecelarationOpen=learn_st.openHistCurrent;
                var_sys_NVM.learningCurrentDecelarationClose=learn_st.closeHistCurrent;
                SaveNVM_VarSystem(pageMemoryP);
                SaveNVM_VarSystem(pageMemoryLearningVars);
                SaveNVM_VarSystem(pageMemoryCounters);
                var_sys.LearningIsEnabled=NO;
                var_sys.PositionActual=0;
                var_sys.PositionIsLost = NO;
                
            }
            else if(var_sys.StateMotor==Stopped )
            {
                generateErrorLearnig();
            }
                else if((button_struct.current == BTN_MENU || typeOpenOrder == TypeFull)&& (var_sys.programinAutomatic == 1)){
                var_sys.LearningDecelaration=YES;

                button_struct.processed = 1;
                ts_system.TimeWaitToGetCurrent=TIME_1S*4;
                
            }
            else if (var_sys.LearningDecelaration == YES){

              
                 if(ts_system.TimeWaitToGetCurrent>0)
                {
                    learn_st.closeHistCurrent=calculateMean(learn_st.closeHistCurrent,var_sys.ActualHistCurrent);
                }
            }
            else
            {  
                var_sys.Counter_Learning = 1;
                ts_system.TimeWaitToNextState=(2*TIME_1S);
                
                 // EUSART_Write_String((char*)"autmatic");
                if (ts_system.TimeWaitReleCapacitor <=0)
                {
                if(ts_system.TimeWaitToGetCurrent>0)
                {
                    learn_st.closeCurrent=calculateMean(learn_st.closeCurrent,var_sys.ActualCurrent);         
                }
                }
            }
        }
        break;
        
    }
    //<<< State implementations

}

unsigned long calculateMean(unsigned long meanValue,unsigned long newValue)
{
    if(meanValue==0)
    {
        meanValue=newValue;
    }
    else
    {
        meanValue=(meanValue+newValue)/2;
    }
    return meanValue;
}

void generateErrorLearnig(void)
{
//    sm_send_event(&controlLearning_stateMachine, ev_ErrorGate);
//    sm_send_event(&controlGate_stateMachine, ev_ErrorLearning);
    var_sys.LearningIsEnabled=NO;

    sm_init(&menuConfiguration_stateMachine,st_MainMenu,HIST_NONE);
    sm_init(&main_stateMachine,st_standBy,HIST_NONE);
    sm_init(&controlGate_stateMachine,st_Idle,HIST_NONE);
    sm_init(&controlLearning_stateMachine,st_InitLearning,HIST_NONE);
}

void clearLearningValue(void)
{
    learn_st.timeOpen=0;
    learn_st.timeClose=0;
    learn_st.timeDecelerationOpen=0;
    learn_st.timeDecelerationClose=0;
    learn_st.openCurrent=0;
    learn_st.closeCurrent=0;
    learn_st.openHistCurrent=0;
    learn_st.closeHistCurrent=0;
    var_sys_NVM.learningCurrentNormalClose=0;
    var_sys_NVM.learningCurrentNormalOpen=0;
    var_sys_NVM.learningCurrentDecelarationClose=0;
    var_sys_NVM.learningCurrentDecelarationOpen=0;
}
