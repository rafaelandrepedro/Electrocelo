#include <xc.h>
#include <stdio.h>
#include "main.h"

#include "mcc_generated_files/pin_manager.h"
#include "sm_common.h"
#include "outputs.h"
#include "inputs.h"
#include "sm_Main.h"
#include "sm_MenuConfiguration.h"
#include "sm_ControlGate.h"



extern sm_t main_stateMachine;
extern sm_t menuConfiguration_stateMachine;
extern sm_t controlGate_stateMachine;
extern volatile BUTTONS_STRUCT button_struct;
extern volatile varSystem var_sys;
extern volatile varSystem_NVM var_sys_NVM;
extern volatile timeslotSystem ts_system;
extern volatile RF_KEY_STRUCT rfCMD;

char temp;
char aux_in_auto_close;
void sm_execute_main( sm_t *psm ) {
    
    //>>> State transitions
    switch((sm_state_Main_t) psm->current_state)
    {
        case st_standBy:
        {
            if(programmer_enable==0)
                if(psm->last_event==ev_goto_MenuConfig)
                {
                    //psm->current_state = st_EditParameter;
                    psm->current_state = st_MenuConfiguration;  // rev1.149 - This was wrong. It was operational by luck because the value of st_EditParameter and st_MenuConfiguration are equal.
                }
                else if(psm->last_event==ev_MotorIsOpen)
                {
                    psm->current_state = st_MotorON;
                }
        }
        break;
        case st_MenuConfiguration:
        {
            if(psm->last_event==ev_goto_StandBy)
            {
                psm->current_state = st_standBy;
            }
        }
        break;
        case st_MotorON:
        {
            if(psm->last_event==ev_goto_StandBy)
            {
                psm->current_state = st_standBy;
            }
            //>>> rev1.149
            // Enable the menu access with the gate 
            else if(psm->last_event==ev_goto_MenuConfig)
            {
                psm->current_state = st_MenuConfiguration;
            }
            //<<< rev1.149
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
    sm_send_event(&main_stateMachine, ev_NULL);
    //<<< State transitions

    
    //>>> State implementations
    switch((sm_state_Main_t) psm->current_state)
    {
        case st_standBy:
        {
            if (button_struct.current==BTN_MENU && button_struct.timer>(TIME_1S*5))
            {
                load_New_Menu(E_Menu);
                sm_send_event(&main_stateMachine, ev_goto_MenuConfig);
                button_struct.processed=1;
                temp=0;
            }
            else if (button_struct.current==BTN_MENU && button_struct.timer>(TIME_1S*1))
            {
                //SetSegmentValue(dP,d0);
                
                SetSegmentValueMain(dP,d0); // rev 1.149
                temp=1;
            }
            else if(temp==1)
            {
                load_New_Menu(P_Menu);
                sm_send_event(&main_stateMachine, ev_goto_MenuConfig);
                button_struct.processed=1;
                temp=0;
            }
            else if (button_struct.current==BTN_CMD && button_struct.timer>(TIME_1S*6))
            {
                //SetSegmentValue(dd,dL);
                load_New_Menu(Del_Menu);
                sm_send_event(&main_stateMachine, ev_goto_MenuConfig);
                button_struct.processed=1;
                temp=0;
            }
            else if (button_struct.current==BTN_CMD && button_struct.timer>(TIME_1S))
            {
                //SetSegmentValue(d5,dU);
                SetSegmentValueMain(d5,dU); // rev 1.149
                temp=2;
            }
            else if(temp==2)
            {
                load_New_Menu(S_Menu);
                sm_send_event(&main_stateMachine, ev_goto_MenuConfig);
                button_struct.processed=1;
                temp=0;
            }
            else if(button_struct.current==BTN_DOWN && var_sys.FimCurso_CloseIsEnabled==NO)
            {
                var_sys.StartFromButton=YES;
                var_sys.StateMotor=InClose;
            }
            else if(button_struct.current==BTN_UP  && var_sys.FimCurso_OpenIsEnabled==NO)
            {
                var_sys.StartFromButton=YES;
                var_sys.StateMotor=InOpenFull;
            }
            else if(var_sys.StartFromButton==YES)
            {
                var_sys.StartFromButton=NO;
                var_sys.StateMotor = Stopped;
            }
            else if((rfCMD.currentType==TypeProgrammingModeFull||rfCMD.currentType==TypeProgrammingModeWalk ) && rfCMD.timer>=(TIME_1S*5))
            {
                load_New_Menu(S_Menu);
                sm_send_event(&main_stateMachine, ev_goto_MenuConfig);
                var_sys.ProgrammingDistanceIs=rfCMD.currentType;
                rfCMD.processed=1;
            }
            else if(ts_system.timeSinalizationDigit<=0)
            {
                if(var_sys.FimCurso_CloseIsEnabled == YES)
                        
                    {
                        //SetSegmentValue(dMinus,dMinus);
                        SetSegmentValueMain(dF,dC); // Rev 1.149
                    }
                else{
                            //SetSegmentValue(dMinus,dMinus);//Sempre que não existe sinilização activa muda para standby.
                SetSegmentValueMain(dMinus,dMinus);//Sempre que não existe sinilização activa muda para standby. (rev 1.149)
                }
                
            }
        }
        break;
        case st_MenuConfiguration:
        {
            sm_execute_menuConfiguration(&menuConfiguration_stateMachine);
        }
        break;
        case st_MotorON:
        {
            //>>> rev1.149 - Permit the menu access with the gate fully open.
            //>>> rev 1.153: DM - The menu cannot be accessed on the auto-close pause time.
            aux_in_auto_close = NO;
            if ( controlGate_stateMachine.current_state == st_Opened )
            {
                // The gate is on an opened position. Let's check if it is with auto-close feature.
                if ( var_sys_NVM.operationMode == ModoPassoPasso && var_sys.passoAPassoAutoClose == YES )
                {
                    aux_in_auto_close = YES;
                }
                else if ( var_sys_NVM.operationMode != ModoPassoPasso && var_sys.AutoCloseActive != 0 )
                {
                    aux_in_auto_close = YES;
                }
                else
                {
                    // Do nothing, no auto-close active, then we can access the menu and the learn process.
                }
            }
            //if(var_sys.StateMotor==Stopped && ( controlGate_stateMachine.current_state==st_Opened || controlGate_stateMachine.current_state==st_Closed || controlGate_stateMachine.current_state==st_Idle ) )
            if(var_sys.StateMotor==Stopped && ( (controlGate_stateMachine.current_state==st_Opened && aux_in_auto_close==NO) || controlGate_stateMachine.current_state==st_Closed || controlGate_stateMachine.current_state==st_Idle ) )
            {
                if (button_struct.current==BTN_MENU && button_struct.timer>(TIME_1S*5))
                {
                    load_New_Menu(E_Menu);
                    sm_send_event(&main_stateMachine, ev_goto_MenuConfig);
                    button_struct.processed=1;
                    temp=0;
                }
                else if (button_struct.current==BTN_MENU && button_struct.timer>(TIME_1S*1))
                {
                    //SetSegmentValue(dP,d0);
                    SetSegmentValueMain(dP,d0); // rev 1.149
                    temp=1;
                }
                else if(temp==1)
                {
                    load_New_Menu(P_Menu);
                    //sm_send_event(&main_stateMachine, ev_goto_MenuConfig);
                    button_struct.processed=1;
                    temp=0;
                    main_stateMachine.current_state = st_MenuConfiguration;
                    return;  // Do not run the bellow ifs.
                }
                else if (button_struct.current==BTN_CMD && button_struct.timer>(TIME_1S*6))
            {
                //SetSegmentValue(dd,dL);
                load_New_Menu(Del_Menu);
                sm_send_event(&main_stateMachine, ev_goto_MenuConfig);
                button_struct.processed=1;
                temp=0;
            }
            else if (button_struct.current==BTN_CMD && button_struct.timer>(TIME_1S))
            {
                //SetSegmentValue(d5,dU);
                SetSegmentValueMain(d5,dU); // rev 1.149
                temp=2;
            }
            else if(temp==2)
            {
                load_New_Menu(S_Menu);
                sm_send_event(&main_stateMachine, ev_goto_MenuConfig);
                button_struct.processed=1;
                temp=0;
                return;
            }
            }
            //<<< rev 1.153: DM - The menu cannot be accessed on the auto-close pause time.
            //<<< rev1.149 - Permit the menu access with the gate fully open.

            if( ts_system.timeSinalizationDigit<=0 && (button_struct.current!=BTN_MENU && button_struct.current!=BTN_CMD) )
            {
                if(var_sys.StateMotor==InClose )
                {
                   //SetSegmentValueIntermitent(dC,dL,TIME_1S);
                   SetSegmentValueIntermitentMain(dC,dL,TIME_500MS);   // Rev 1.149
                   ts_system.timeSinalizationDigit=TIME_200MS;

                    var_sys.showAP = NO;    // rev 1.149
                }
                else if(var_sys.StateMotor==InOpenWalk || var_sys.StateMotor==InOpenFull)
                {
                    //SetSegmentValueIntermitent(d0,dP,TIME_1S);
                    SetSegmentValueIntermitentMain(d0,dP,TIME_500MS);  // Rev 1.149
                    ts_system.timeSinalizationDigit=TIME_200MS;
                    
                    var_sys.showAP = NO;    // rev 1.149
                }
                else if(var_sys.StateMotor==Stopped && controlGate_stateMachine.current_state==st_Closed)
                {
                    sm_send_event(&main_stateMachine, ev_goto_StandBy);
                }
                else if(var_sys.StateMotor==Stopped && controlGate_stateMachine.current_state==st_Opened)
                {
                    //if(var_sys_NVM.operationMode!=ModoPassoPasso && var_sys.AutoCloseActive!=0 && var_sys.LastState==InOpenFull)
                    if
                    (
                        ( var_sys_NVM.operationMode!=ModoPassoPasso && var_sys.AutoCloseActive!=0 && (var_sys.LastState==InOpenFull || var_sys.LastState==InClose) ) ||
                        ( var_sys_NVM.operationMode==ModoPassoPasso && var_sys.passoAPassoAutoClose == YES && var_sys.LastState!=InOpenWalk && var_sys.AutoCloseActive != 0 )
                    )  // rev 1.149 - Para apresentar também quando estava a fechar e se inverte.
                    {
                        ts_system.timeSinalizationDigit=TIME_500MS;
                        //SetSegmentValueIntermitent(dA,dF,TIME_500MS);
                        
                        
                        //SetSegmentValueIntermitentMain(dA,dF,TIME_500MS);   // Rev 1.149
                        if ( var_sys.showAP == YES )
                        {
                            SetSegmentValueIntermitentMain(dA,dP,TIME_500MS);
                        }
                        else
                        {
                            SetSegmentValueIntermitentMain(dA,dF,TIME_500MS);
                        }
                    }
                    //else if(var_sys_NVM.operationMode!=ModoPassoPasso && var_sys.AutoCloseActive!=0 && var_sys.LastState==InOpenWalk)
                    else if
                    (
                        ( var_sys_NVM.operationMode!=ModoPassoPasso && var_sys.AutoCloseActive!=0 && var_sys.LastState==InOpenWalk ) || // rev 1.149 - O modo passo a passo passou a implementar tempo de pausa quando chega à posição de pausa (full ou pedonal)
                        ( var_sys_NVM.operationMode==ModoPassoPasso && var_sys.passoAPassoAutoClose == YES && var_sys.LastState==InOpenWalk )
                    )
                    {
                        ts_system.timeSinalizationDigit=TIME_500MS;
                        //SetSegmentValueIntermitent(dA,dP,TIME_500MS);
                        SetSegmentValueIntermitentMain(dA,dP,TIME_500MS);   // Rev 1.149
                    }
                    else if(var_sys.FimCurso_OpenIsEnabled == YES)
                        
                    {
                        //SetSegmentValue(dMinus,dMinus);
                        SetSegmentValueMain(dF,d0); // Rev 1.149
                    }
                    else 
                    {
                      SetSegmentValueMain(dMinus,dMinus);  
                    }
                }
                else
                {
                    //SetSegmentValue(dMinus,dMinus);
                    SetSegmentValueMain(dMinus,dMinus); // Rev 1.149
                }
            }
        }
        break;
    }
    //<<< State transitions.
}
