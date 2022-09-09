

#include <xc.h>
#include <stdio.h>
#include "main.h"

#include "sm_common.h"
#include "outputs.h"
#include "inputs.h"
#include "sm_MenuConfiguration.h"
#include "mcc_generated_files/pin_manager.h"

#include "sm_Main.h"
#include "controlMemory.h"
#include "sm_ControlGate.h"


menu_Struct menu_st;
extern sm_t menuConfiguration_stateMachine;
extern sm_t controlGate_stateMachine;
extern sm_t main_stateMachine;
extern volatile BUTTONS_STRUCT button_struct;
extern volatile timeslotSystem ts_system;
extern volatile varSystem_NVM var_sys_NVM;
extern volatile varSystem var_sys;
volatile edit_Parameter_st edit_Param;

static bool firstselectflag=true;

unsigned long tempCounter=998877;
unsigned int auxCounter=1000;

void sm_execute_menuConfiguration( sm_t *psm ) {

    //>>> State transitions
    switch((sm_state_Menu_t) psm->current_state)
    {
        case st_MainMenu:
        {
            if(psm->last_event==ev_ParameterIsSelected)
            {
                psm->current_state = st_EditParameter;
            }
            else if (psm->last_event==ev_showCounter)
            {
                psm->current_state = st_Counter;
            }
            else if (psm->last_event == ev_addRemotes)
            {
                psm->current_state = st_SelectRemote;
            }
            else if (psm->last_event == ev_SartLearning)
            {
                //>>> rev 1.153: DM - Não acede ao learn caso exista erro.
                psm->current_state = st_LearningMode;
//                if ( var_sys.WorkTimeMaxAlarmState != EmAlarme && var_sys.NumberOffErrors <= MaxOfErrors )
//                {
//                    psm->current_state = st_LearningMode;
//                }
                //<<< rev 1.153: DM - Não acede ao learn caso exista erro.
            }
        }
        break;
        case st_EditParameter:
        {
            if(psm->last_event==ev_ParameterIsEdited)
            {
                psm->current_state = st_SaveParameter;
            }
            else if(psm->last_event==ev_CancelEdition)
            {
                psm->current_state = st_MainMenu;
            }
        }
        break;
        case st_SaveParameter:
        {
            if(psm->last_event==ev_ParameterIsSaved)
            {
                psm->current_state = st_MainMenu;
            }
        }
        break;
        case st_Counter:
        {
            if(psm->last_event==ev_ParameterIsSaved)
            {
                psm->current_state = st_MainMenu;
            }
             else if(psm->last_event==ev_CancelEdition)
            {
                psm->current_state = st_MainMenu;
            }
        }
        break;
        case st_SelectRemote:
        {
            if(psm->last_event==ev_addRemotes)
            {
                psm->current_state = st_SaveRemotes;
            }
             else if(psm->last_event==ev_CancelEdition)
            {
                psm->current_state = st_MainMenu;
            }
        }
        break;
        case st_SaveRemotes:
        {
            if(psm->last_event==ev_NextRemote)
            {
                psm->current_state = st_SelectRemote;
            }
            if(psm->last_event==ev_ParameterIsSaved)
            {
                psm->current_state = st_MainMenu;
            }
        }
        break;
        case st_LearningMode:
        {
            if(psm->last_event==ev_ParameterIsSaved)
            {
                psm->current_state = st_MainMenu;
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
    sm_send_event(&menuConfiguration_stateMachine, ev_NULL);
    //<<< State transitions
    
    
    //>>> State implementations
    switch((sm_state_Menu_t) psm->current_state)
    {
        case st_MainMenu:
        {
            if(var_sys.ProgrammingDistanceIs==TypeProgrammingModeFull)
            {
                ts_system.timeoutMenu=10*TIME_1S;
                var_sys.DistanceProgrammingActive=YES;
                menu_st.parameterSelected=0;
                if (setValueToEdit(menu_st.actualMenu,menu_st.parameterSelected)) {

                     sm_send_event(&menuConfiguration_stateMachine, ev_addRemotes);
                     SetSegmentValueIntermitentMain(edit_Param.tempValue/10, edit_Param.tempValue-((edit_Param.tempValue/10)*10),TIME_1S);
                }
            }
            else if(var_sys.ProgrammingDistanceIs==TypeProgrammingModeWalk)
            {
                ts_system.timeoutMenu=10*TIME_1S;
                var_sys.DistanceProgrammingActive=YES;
                menu_st.parameterSelected=1;
                if (setValueToEdit(menu_st.actualMenu,menu_st.parameterSelected)) {

                     sm_send_event(&menuConfiguration_stateMachine, ev_addRemotes);
                     SetSegmentValueIntermitentMain(edit_Param.tempValue/10, edit_Param.tempValue-((edit_Param.tempValue/10)*10),TIME_1S);
                }
            }
            else if (button_struct.current==BTN_DOWN)
            {
                ts_system.timeoutMenu= TIMEOUT ;
                if(menu_st.parameterSelected==0)
                {
                    menu_st.parameterSelected=menu_st.menuSize-1;
                }
                else
                {
                    menu_st.parameterSelected--;
                }
                SetSegmentValueMain(menu_st.menuList[menu_st.parameterSelected].value_display1, menu_st.menuList[menu_st.parameterSelected].value_display2);
                button_struct.processed=1;
            }
            else if (button_struct.current==BTN_UP)
            {
                ts_system.timeoutMenu=TIMEOUT ;
                menu_st.parameterSelected++;
                if(menu_st.parameterSelected>=menu_st.menuSize)
                {
                    menu_st.parameterSelected=0;
                }
                SetSegmentValueMain(menu_st.menuList[menu_st.parameterSelected].value_display1, menu_st.menuList[menu_st.parameterSelected].value_display2);
                button_struct.processed=1;
            }
            else if( menu_st.actualMenu<S_Menu )
            {
                if (button_struct.current==BTN_MENU && button_struct.timer>(TIME_500MS) )
                {
                    ts_system.timeoutMenu=TIMEOUT ;
                                            
                    if (setValueToEdit(menu_st.actualMenu,menu_st.parameterSelected)) 
                    {

                         sm_send_event(&menuConfiguration_stateMachine, ev_ParameterIsSelected);
                         if((edit_Param.Value==(unsigned char*)&var_sys_NVM.TypeofMotor)||(edit_Param.Value==(unsigned char*)&var_sys_NVM.Direction_motor)){
                           SetSegmentValueMain(menu_st.menuList[edit_Param.tempValue].value_display1, menu_st.menuList[edit_Param.tempValue].value_display2); 

                         }
                         else{
                         SetSegmentValueMain(edit_Param.tempValue/10, edit_Param.tempValue-((edit_Param.tempValue/10)*10));
     
                         }
                         
                    }
                    button_struct.processed=1;
                }
                else if((ts_system.timeoutMenu<=0||button_struct.current==BTN_UPDOWN) && menu_st.actualMenu<=E_Menu)
                {
                    ts_system.timeoutMenu=0;
                    sm_send_event(&main_stateMachine, ev_goto_StandBy);
                    SetSegmentValueMain(dMinus,dMinus);
                    menu_st.lastMainParameterSelected = 0;
                    button_struct.processed=1;
                    ClearFlag_rfCMD();
                    
                }
                else if(ts_system.timeoutMenu<=0||button_struct.current==BTN_UPDOWN)
                {
                     
                    load_New_Menu(menu_st.lastMenu);
                    button_struct.processed=1;
                }
                else if(ts_system.timeoutMenu<=0 && menu_st.actualMenu>E_Menu)
                {
                     
                    load_New_Menu(menu_st.lastMenu);
                    button_struct.processed=1;
                }
            }
            else if (button_struct.current==BTN_CMD && button_struct.timer>TIME_500MS && menu_st.actualMenu!=Del_Menu )
            {
                    ts_system.timeoutMenu=TIMEOUT;
                    if (setValueToEdit(menu_st.actualMenu,menu_st.parameterSelected))
                    
                    {
                        sm_send_event(&menuConfiguration_stateMachine, ev_addRemotes);
                        SetSegmentValueIntermitentMain(edit_Param.tempValue/10, edit_Param.tempValue-((edit_Param.tempValue/10)*10),TIME_1S);
                    }
                    button_struct.processed=1;
            }
            else if(menu_st.actualMenu==Del_Menu && ts_system.timeSinalizationDigit==0)
            {
                var_sys_NVM.positionRemotesFull=0;//Limpa comandos Full
                var_sys_NVM.positionRemotesWalk=0;//Limpa Comandos Walk
                var_sys_NVM.OnlyRollingCode=NO;//Limpa a Flag de modo a aceitar todos os tipos de comandos.
                SaveNVM_VarSystem(pageMemoryCounters);
                sm_send_event(&main_stateMachine, ev_goto_StandBy);
                SetSegmentValueMain(dMinus,dMinus);
                button_struct.processed=1;
                ClearFlag_rfCMD();
                 ts_system.timeoutMenu=0;
            }
            else if(ts_system.timeoutMenu<=0||button_struct.current==BTN_UPDOWN)
            {
                 sm_send_event(&main_stateMachine, ev_goto_StandBy);
                 SetSegmentValueMain(dMinus,dMinus);
                 ClearFlag_rfCMD();
                 button_struct.processed=1;
                  ts_system.timeoutMenu=0;
            }
        }
        break;
        case st_EditParameter:
        {
            if (button_struct.current==BTN_DOWN)
            {
                ts_system.timeoutMenu=TIMEOUT;
                if(edit_Param.tempValue<=edit_Param.Min)
                {
                    edit_Param.tempValue=edit_Param.Max;
                }
                else
                {
                    edit_Param.tempValue--;
                }
                if ((edit_Param.Value==(unsigned char*)&var_sys_NVM.TypeofMotor)||(edit_Param.Value==(unsigned char*)&var_sys_NVM.Direction_motor)){
                SetSegmentValueMain(menu_st.menuList[edit_Param.tempValue].value_display1, menu_st.menuList[edit_Param.tempValue].value_display2);
                }
                else{
                  
                SetSegmentValueMain(edit_Param.tempValue/10, edit_Param.tempValue-((edit_Param.tempValue/10)*10));
                }
                button_struct.processed=1;
            }
            else if (button_struct.current==BTN_UP)
            {
                ts_system.timeoutMenu=TIMEOUT ;
                edit_Param.tempValue++;
                if(edit_Param.tempValue>edit_Param.Max)
                {
                     edit_Param.tempValue=edit_Param.Min;
                }
                if ((edit_Param.Value==(unsigned char*)&var_sys_NVM.TypeofMotor)||(edit_Param.Value==(unsigned char*)&var_sys_NVM.Direction_motor)){
                    SetSegmentValueMain(menu_st.menuList[edit_Param.tempValue].value_display1, menu_st.menuList[edit_Param.tempValue].value_display2);
                }
                else{
                   
                SetSegmentValueMain(edit_Param.tempValue/10, edit_Param.tempValue-((edit_Param.tempValue/10)*10));
                
                }
                button_struct.processed=1;
            }
            else if (button_struct.current==BTN_MENU && button_struct.timer>=(TIME_500MS))
            {
                ts_system.timeoutMenu=TIMEOUT ;
                //Guarda o valor no ponteiro anteriormente carregado.
                edit_Param.Value[0]=edit_Param.tempValue;
                sm_send_event(&menuConfiguration_stateMachine, ev_ParameterIsEdited);
                SetSegmentValueMain(dBar,d1);
                ts_system.timeSinalizationDigit=(TIME_1S*2);
                button_struct.processed=1;

            }
            else if(ts_system.timeoutMenu<=0|| (button_struct.current==BTN_UPDOWN ))
            {
                ts_system.timeoutMenu=TIMEOUT ;
                load_New_Menu(menu_st.actualMenu);
                sm_send_event(&menuConfiguration_stateMachine, ev_CancelEdition);
                button_struct.processed=1;
            }
        }
        break;
        case st_SaveParameter:
        {        
            if (ts_system.timeSinalizationDigit<=0)
            {
                ts_system.timeoutMenu=TIMEOUT ;
                //Guarda o Pagina respectiva ao tipo de Menu respectivo.
                if((menu_st.actualMenu==E_Menu && menu_st.parameterSelected==8)||(edit_Param.Value==(unsigned char*)&var_sys_NVM.TypeofMotor)) //Valida se reset da memoria
                {
                
                            
                    ResetDefaultMemory(var_sys_NVM.TypeofMotor);
  
                }
                else if(menu_st.actualMenu==E_Menu||menu_st.actualMenu==E0_SMenu)
                {
                    SaveNVM_VarSystem(pageMemoryE);
                }
                else
                {
                    if (menu_st.parameterSelected == 1 && edit_Param.Value[0] >=1 && menu_st.actualMenu == P2_SMenu )
                    {
                      var_sys_NVM.motorPower = 9;  
                    }

                      SaveNVM_VarSystem(pageMemoryE);
                      SaveNVM_VarSystem(pageMemoryP);  
                    
                   
                }
                sm_send_event(&menuConfiguration_stateMachine, ev_ParameterIsSaved);


                menu_st.parameterSelected++;
                if(menu_st.actualMenu<=E_Menu)
                {
                    menu_st.lastMainParameterSelected++;
                    load_New_Menu(menu_st.actualMenu);
                }
                else if ( menu_st.parameterSelected>=menu_st.menuSize )
                {
                    menu_st.lastMainParameterSelected++;
                    load_New_Menu(menu_st.lastMenu);
                }
                else
                {
                    load_New_Menu(menu_st.actualMenu);
                }
            }
        }
        break;
        case st_Counter:
        {
            if(ts_system.timeoutMenu<=0)
            {

                if(auxCounter<=0){
                    menu_st.lastMainParameterSelected++;
                    load_New_Menu(menu_st.actualMenu);
                    sm_send_event(&menuConfiguration_stateMachine, ev_ParameterIsSaved);
                }
                else
                {
                    ts_system.timeoutMenu=TIME_1S*3;
                    edit_Param.tempValue=(unsigned char)(tempCounter/auxCounter);
                    tempCounter=tempCounter-(tempCounter/auxCounter*auxCounter);
                    auxCounter=auxCounter/100;
                    SetSegmentValueIntermitentMain(edit_Param.tempValue/10, edit_Param.tempValue-((edit_Param.tempValue/10)*10),TIME_500MS);
                }
            }
        }
        break;
        case st_SelectRemote:
        {
            if(firstselectflag==true){
                edit_Param.tempValue=0;
                firstselectflag=false;
            }
            controlSelectRemote();
        }
        break;
        case st_SaveRemotes:
        {
            controlSaveRemote();
        }
        break;
        case st_LearningMode:
        {
            controlLearnDigit();
            if(var_sys.LearningIsEnabled==NO)
            {
                sm_send_event(&main_stateMachine, ev_goto_StandBy);
                sm_send_event(&menuConfiguration_stateMachine, ev_ParameterIsSaved);
                SetSegmentValueMain(dMinus,dMinus);
                SaveNVM_VarSystem(pageMemoryCounters);
                ClearFlag_rfCMD();
                ts_system.timeoutMenu=0;
            }
        }
        break;
    }
    //<<< State implementations
}

void load_New_Menu(menuLists_en Menu){
    ts_system.timeoutMenu=TIMEOUT ;
    char i=0;
    //Veririca se é um submenu e confirma se o menu que se pertende abrir é diferente do anterior.
    //Caso seja renicia o parametro sleccionado e guarda o que estava seleccionada
    if(menu_st.actualMenu!=Menu && Menu>E_Menu)
    {
        menu_st.parameterSelected=0;
    }
    else if( Menu<=E_Menu)
    {
       menu_st.parameterSelected = menu_st.lastMainParameterSelected;
    }


    menu_st.lastMenu=NULL;
    switch (Menu)
    {
        case P_Menu:
        {
            //menu_st.lastMenu=NULL;
            menu_st.actualMenu=P_Menu;
            menu_st.menuSize=10;//Size of Menu P.
            menu_st.lastMainParameterSelected=0;
            for (i=0;i<NUM_MENU_OPTIONS;i++)
            {
               menu_st.menuList[i].value_display1=dP;
               menu_st.menuList[i].value_display2=i;
            }
        }
        break;
        case E_Menu:
        {
            //menu_st.lastMenu=NULL;
            menu_st.actualMenu=E_Menu;
            menu_st.menuSize=10;//Size of Menu P
            menu_st.lastMainParameterSelected=0;
            for (i=0;i<NUM_MENU_OPTIONS;i++)
            {
               menu_st.menuList[i].value_display1=dE;
               menu_st.menuList[i].value_display2=i;
            }
        }
        break;
        case P0_SMenu:
        {
            menu_st.lastMenu=P_Menu;
            menu_st.actualMenu=P0_SMenu;
            menu_st.menuSize=4;//Size of Menu P
            menu_st.menuList[0].value_display1=dA;
            menu_st.menuList[0].value_display2=dU;
            menu_st.menuList[1].value_display1=dM;
            menu_st.menuList[1].value_display2=dA;
            menu_st.menuList[2].value_display1=d5;
            menu_st.menuList[2].value_display2=dy;
            menu_st.menuList[3].value_display1=dd;
            menu_st.menuList[3].value_display2=d1;
          break;  
        }
        case P1_SMenu:
        {
            menu_st.lastMenu=P_Menu;
            menu_st.actualMenu=P1_SMenu;
            menu_st.menuSize=2;//Size of Menu P
            menu_st.menuList[0].value_display1=dd;
            menu_st.menuList[0].value_display2=dA;
            menu_st.menuList[1].value_display1=dd;
            menu_st.menuList[1].value_display2=dF;
     

            
        }
        break;
        case P2_SMenu:
        {
            menu_st.lastMenu=P_Menu;
            menu_st.actualMenu=P2_SMenu;
            menu_st.menuSize=3;//Size of Menu P
            menu_st.menuList[0].value_display1=dF;
            menu_st.menuList[0].value_display2=d0;
            menu_st.menuList[1].value_display1=dF;
            menu_st.menuList[1].value_display2=d5;
            menu_st.menuList[2].value_display1=dF;
            menu_st.menuList[2].value_display2=dd;
        }
        break;
        case P4_SMenu:
        {
            menu_st.lastMenu=P_Menu;
            menu_st.actualMenu=P4_SMenu;
            menu_st.menuSize=2;//Size of Menu P
            menu_st.menuList[0].value_display1=dA;
            menu_st.menuList[0].value_display2=dF;
            menu_st.menuList[1].value_display1=dA;
            menu_st.menuList[1].value_display2=dP;
        }
        break;
        case P5_SMenu:
        {
            menu_st.lastMenu=P_Menu;
            menu_st.actualMenu=P5_SMenu;
            menu_st.menuSize=2;//Size of Menu P
            menu_st.menuList[0].value_display1=dL;
            menu_st.menuList[0].value_display2=dE;
            menu_st.menuList[1].value_display1=dH;
            menu_st.menuList[1].value_display2=dC;
        }
        break;
        case P6_SMenu:
        {
            menu_st.lastMenu=P_Menu;
            menu_st.actualMenu=P6_SMenu;
            menu_st.menuSize=4;//Size of Menu P
            menu_st.menuList[0].value_display1=dL;
            menu_st.menuList[0].value_display2=dA;
            menu_st.menuList[1].value_display1=dH;
            menu_st.menuList[1].value_display2=dA;
            menu_st.menuList[2].value_display1=dH;
            menu_st.menuList[2].value_display2=dL;
            menu_st.menuList[3].value_display1=d5;
            menu_st.menuList[3].value_display2=dt;            
            
        }
        break;
        case E0_SMenu:
        {
            menu_st.lastMenu=E_Menu;
            menu_st.actualMenu=E0_SMenu;
            menu_st.menuSize=2;//Size of Menu P
            menu_st.menuList[0].value_display1=dH;
            menu_st.menuList[0].value_display2=dP;
            menu_st.menuList[1].value_display1=dP;
            menu_st.menuList[1].value_display2=dL;
        }
        break;
        case E1_SMenu:
        {
            menu_st.lastMenu=E_Menu;
            menu_st.actualMenu=E1_SMenu;
            menu_st.menuSize=2;//Size of Menu P
            menu_st.menuList[0].value_display1=dr;
            menu_st.menuList[0].value_display2=dq;
            menu_st.menuList[1].value_display1=dr;
            menu_st.menuList[1].value_display2=dc;
        }
        break;
        case S_Menu:
        {
            //menu_st.lastMenu=NULL;
            menu_st.actualMenu=S_Menu;
            menu_st.parameterSelected=0;
            menu_st.menuSize=2;//Size of Menu P
            menu_st.menuList[0].value_display1=d5;
            menu_st.menuList[0].value_display2=dU;
            menu_st.menuList[1].value_display1=d5;
            menu_st.menuList[1].value_display2=dP;
        }
        break;
        case Del_Menu:
        {
            //menu_st.lastMenu=NULL;
            menu_st.actualMenu=Del_Menu;
            menu_st.menuSize=1;//Size of Menu P
            menu_st.menuList[0].value_display1=dd;
            menu_st.menuList[0].value_display2=dL;
            ts_system.timeSinalizationDigit=TIME_1S*3;
        }
        break;
        
        case TypeMotor_Menu:
        {
//            menu_st.lastMenu=P0_SMenu;
//            menu_st.actualMenu=TypeMotor_Menu;
            //menu_st.menuSize=3;//Size of Menu P
            menu_st.menuList[0].value_display1=d5;
            menu_st.menuList[0].value_display2=dC;
            menu_st.menuList[1].value_display1=d5;
            menu_st.menuList[1].value_display2=dE;
            menu_st.menuList[2].value_display1=db;
            menu_st.menuList[2].value_display2=dr;
        }
        break;
       case Direction_Menu:
        {
//            menu_st.lastMenu=P0_SMenu;
//            menu_st.actualMenu=TypeMotor_Menu;
            //menu_st.menuSize=3;//Size of Menu P
            menu_st.menuList[0].value_display1=dL;
            menu_st.menuList[0].value_display2=dE;
            menu_st.menuList[1].value_display1=dr;
            menu_st.menuList[1].value_display2=dt;

        }
        break;

    }


    if(menu_st.parameterSelected>=menu_st.menuSize)
    {
        menu_st.parameterSelected=0;
    }

    if(Menu==Del_Menu)
    {
        SetSegmentValueIntermitentMain(menu_st.menuList[ menu_st.parameterSelected].value_display1, menu_st.menuList[ menu_st.parameterSelected].value_display2,TIME_500MS);
    }
    else
    {
        SetSegmentValueMain(menu_st.menuList[ menu_st.parameterSelected].value_display1, menu_st.menuList[ menu_st.parameterSelected].value_display2);
    }

}

char setValueToEdit(menuLists_en menuType, char ParameterSelected ){
    char haveValueToEdit=0;
    
    
    switch (menuType)
    {
        case P_Menu:
        {
            menu_st.lastMainParameterSelected= menu_st.parameterSelected;
            edit_Param.Min=0;
            switch (ParameterSelected)
            {
                case 0:
                {
                    load_New_Menu(P0_SMenu);

                }
                break;
                case 1:
                {
                    load_New_Menu(P1_SMenu);
                }
                break;
                case 2:
                {
                    load_New_Menu(P2_SMenu);
                }
                break;
                case 3:
                {
                    edit_Param.Max=99;
                    //edit_Param.Min=0;
                    edit_Param.tempValue=var_sys_NVM.walkTime;
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.walkTime;
                    haveValueToEdit=1;
                }
                break;
                case 4:
                {
                    load_New_Menu(P4_SMenu);
                }
                break;
                case 5:
                {
                    load_New_Menu(P5_SMenu);
                }
                break;
                case 6:
                {
                    load_New_Menu(P6_SMenu);
                }
                break;
                case 7:
                {
                    edit_Param.Max=2;
                    //edit_Param.Min=0;
                    edit_Param.tempValue=var_sys_NVM.operationMode;
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.operationMode;
                    haveValueToEdit=1;
                }
                break;
                case 8:
                {
                    edit_Param.Max=3;
                    //edit_Param.Min=0;
                    edit_Param.tempValue=var_sys_NVM.flashLightMode;
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.flashLightMode;
                    haveValueToEdit=1;
                }
                break;
                case 9:
                {
                    edit_Param.Max=1;
                    //edit_Param.Min=0;
                    edit_Param.tempValue=var_sys_NVM.programmingDistance;
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.programmingDistance;
                    haveValueToEdit=1;
                }
                break;
            }
        }
        break;
        
        
        case E_Menu:
        {
            menu_st.lastMainParameterSelected= menu_st.parameterSelected;
            edit_Param.Max=1;
            edit_Param.Min=0;
            switch (ParameterSelected)
            {
                case 0:
                {
                    load_New_Menu(E0_SMenu);
                }
                break;
                case 1:
                {
                    
                    
                    load_New_Menu(E1_SMenu);

                }
                break;
                case 2:
                {
                    edit_Param.Max=99;
                    //edit_Param.Min=0;
                    edit_Param.tempValue=var_sys_NVM.ligthTime;
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.ligthTime;
                    haveValueToEdit=1;
                }
                break;
                case 3:
                {
                   edit_Param.Max=9;
                   edit_Param.Min=1;
                   edit_Param.tempValue=var_sys_NVM.folow_me;
                   edit_Param.Value=(unsigned char*)&var_sys_NVM.folow_me;
                   haveValueToEdit=1;
                } 
                break;
                case 4:
                {
//                   edit_Param.tempValue=var_sys_NVM.encoder;
//                   edit_Param.Value=(unsigned char*)&var_sys_NVM.encoder;
//                   haveValueToEdit=1;
                }
                break;
                case 5:
                {
                   edit_Param.tempValue=var_sys_NVM.electricBrake;
                   edit_Param.Value=(unsigned char*)&var_sys_NVM.electricBrake;
                   haveValueToEdit=1;
                }
                break;
                case 6:
                {
                    edit_Param.Max=9;
                    edit_Param.Min=1;
                    edit_Param.tempValue=var_sys_NVM.velocityDecelaration;
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.velocityDecelaration;
                    haveValueToEdit=1;
                }
                break;
                case 7:
                {
                    edit_Param.tempValue=0;
                    ts_system.timeoutMenu=0;

                    auxCounter=10000;
                    ts_system.timeBetweenSaveCounters=0;//Força um Save para o caso do var_sys_NVM.counterMoves não estar actualizado.
                    tempCounter=var_sys.actualCounterMoves;
                    sm_send_event(&menuConfiguration_stateMachine, ev_showCounter);
                }
                break;
                case 8:
                {
                    edit_Param.tempValue=0;
                    haveValueToEdit=1;
                    edit_Param.Value = 0;
                }
                break;
                case 9:
                {
                    edit_Param.Max=3;
                    edit_Param.Min=0;
                    edit_Param.tempValue=var_sys_NVM.flashRGBMode;
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.flashRGBMode;
                    haveValueToEdit=1;
                }
                break;
            }
        }
        break;
        case P0_SMenu:
          {
            switch (ParameterSelected)
            {
       
                case 0:
                {
                 sm_send_event(&menuConfiguration_stateMachine, ev_SartLearning);  
                 sm_send_event(&controlGate_stateMachine,ev_SartLearning );
                 var_sys.LearningIsEnabled=YES;
                 var_sys.programinAutomatic = Automatic;
                 SaveNVM_VarSystem(pageMemoryE);
                 
                 
                }
                break;
                case 1:
                {
                 sm_send_event(&menuConfiguration_stateMachine, ev_SartLearning);    
                 sm_send_event(&controlGate_stateMachine, ev_SartLearning);
                 var_sys.LearningIsEnabled=YES;
                 var_sys.programinAutomatic = Manual;
                 SaveNVM_VarSystem(pageMemoryE);           
                 
                    
                }
                break;
                 case 2:
                {
                 edit_Param.tempValue=var_sys_NVM.TypeofMotor;       
                 load_New_Menu(TypeMotor_Menu);
                 edit_Param.Value=(unsigned char*)&var_sys_NVM.TypeofMotor;
                 haveValueToEdit=1;
                 edit_Param.Max=2;
                 edit_Param.Min=0;
                 //edit_Param.tempValue= edit_Param.Value[0];
                }
                break;
                 case 3:
                {
                 edit_Param.tempValue=var_sys_NVM.Direction_motor;       
                 load_New_Menu(Direction_Menu);
                 edit_Param.Value=(unsigned char*)&var_sys_NVM.Direction_motor;
                 haveValueToEdit=1;
                 edit_Param.Max=1;
                 edit_Param.Min=0;
                 //edit_Param.tempValue= edit_Param.Value[0];
                }
                break;
            }
            

          }
        break;
        case P1_SMenu:
        {
            switch (ParameterSelected)
            {

                case 0:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.decelarationOpen;
                }
                break;
                case 1:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.decelarationClose;
                }
                break;
              
            }

                edit_Param.Max=45;
                edit_Param.Min=0;
            
           
            haveValueToEdit=1;
            edit_Param.tempValue= edit_Param.Value[0];
        }
        break;
        case P2_SMenu:
        {
            edit_Param.Max=9;
            edit_Param.Min=0;
            switch (ParameterSelected)
            {
                case 0:
                {
                      if (var_sys_NVM.motorSensitivity <2)
                      {
                        edit_Param.Min=0;
                      }
                      else
                      {
                        edit_Param.Min=9;  
                      }
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.motorPower;
                }
                break;
                case 1:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.motorSensitivity;
                }
                break;
                case 2:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.decelarationSensivity;
                }
                break;
            }
            haveValueToEdit=1;
            edit_Param.tempValue= edit_Param.Value[0];
        }
        break;
        case P4_SMenu:
        {
            switch (ParameterSelected)
            {
                case 0:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.autoTimeFullClose;
                }
                break;
                case 1:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.autoTimeWalkClose;
                }
                break;
            }
            edit_Param.Max=99;
            edit_Param.Min=0;
            haveValueToEdit=1;
            edit_Param.tempValue= edit_Param.Value[0];
        }
        break;
        case P5_SMenu:
        {
            switch (ParameterSelected)
            {
                case 0:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.photoCellIsON;
                }
                break;
                case 1:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.photoCellInOpen;
                }
                break;
            }
            edit_Param.Max=1;
            edit_Param.Min=0;
            haveValueToEdit=1;
            edit_Param.tempValue= edit_Param.Value[0];
        }
        break;
        case P6_SMenu:
        {
            switch (ParameterSelected)
            {
                case 0:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.securityBandIsON;
                }
                break;
                case 1:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.securityBandType;
                }
                break;
                case 2:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.securityBandInOpen;
                }
                break;
                case 3:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.Stopboton;
                }
                break;
                
            }
            
            
            edit_Param.Max=1;
            edit_Param.Min=0;
            haveValueToEdit=1;
            edit_Param.tempValue= edit_Param.Value[0];
        }
        break;
        case E0_SMenu:
        {
            switch (ParameterSelected)
            {
                case 0:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.homemPresente;
                      edit_Param.Max=2;
                      edit_Param.Min=0;
                }
                break;
                case 1:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.logicDigital;
                    edit_Param.Max=1;
                    edit_Param.Min=0;
                }
                break;
            }

            haveValueToEdit=1;
            edit_Param.tempValue= edit_Param.Value[0];
        }
        break;
        case E1_SMenu:
        {
            switch (ParameterSelected)
            {
                case 0:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.softStart;
                     edit_Param.Max=9;
                     edit_Param.Min=0;
                }
                break;
                case 1:
                {
                    edit_Param.Value=(unsigned char*)&var_sys_NVM.softstop;
                    edit_Param.Max=9;
                     edit_Param.Min=0;
                }
                break;
            }
           
            haveValueToEdit=1;
            edit_Param.tempValue= edit_Param.Value[0];
        }
         break;
        
        case S_Menu:
        {
            static unsigned char value=0;
            switch (ParameterSelected)
            {
                case 0:
                {
		    edit_Param.Value=&value;
                    for(unsigned char posindex=0; posindex <= *(unsigned char*)&var_sys_NVM.positionRemotesFull; posindex++)
                    {
                        value=posindex;
                        if(cmdMemoryIsEmpty(menu_st.parameterSelected, posindex))
                            break;
                    }
                    edit_Param.Max=*(unsigned char*)&var_sys_NVM.positionRemotesFull;
                }
                break;
                case 1:
                {
                    for(unsigned char posindex=0; posindex <= *(unsigned char*)&var_sys_NVM.positionRemotesWalk; posindex++)
                    {
                        value=posindex;
                        if(cmdMemoryIsEmpty(menu_st.parameterSelected, posindex))
                            break;
                    }
                    edit_Param.Max=*(unsigned char*)&var_sys_NVM.positionRemotesWalk;
                }
                break;
            }
            edit_Param.position=*edit_Param.Value;
            edit_Param.Min=0;
            haveValueToEdit=1;
            edit_Param.tempValue=*edit_Param.Value;
            InitReceiver();
        }
        break;
       
    }
    return haveValueToEdit;
}

void controlSelectRemote(void) {
    unsigned long tempSerial;
    char temp=getSerialCmd(&tempSerial);
    char validSerial;
    if(ts_system.timeoutMenu<=0 || button_struct.current==BTN_UPDOWN)//timeout
    {
        sm_send_event(&main_stateMachine, ev_goto_StandBy);
        sm_send_event(&menuConfiguration_stateMachine, ev_CancelEdition);
        var_sys.DistanceProgrammingActive=NO;
        var_sys.ProgrammingDistanceIs=NoCMD;
        SetSegmentValueMain(dMinus,dMinus);
        ClearFlag_rfCMD();
        button_struct.processed=1;
        ts_system.timeoutMenu = 0;
       
    }
    else if (button_struct.current==BTN_DOWN && edit_Param.Max!=0)//next down
    {
        ts_system.timeoutMenu=TIMEOUT ;
        if(edit_Param.tempValue<=edit_Param.Min)
        {
            edit_Param.tempValue=edit_Param.Max;
        }
        else
        {
            edit_Param.tempValue--;
        }
        if(cmdMemoryIsEmpty(menu_st.parameterSelected,edit_Param.tempValue)==1 || edit_Param.tempValue==edit_Param.Max)
        {
            SetSegmentValueIntermitentMain((edit_Param.tempValue-edit_Param.tempValue%10)/10, edit_Param.tempValue%10,TIME_1S);
        }
        else
        {
            SetSegmentValueMain((edit_Param.tempValue-edit_Param.tempValue%10)/10, edit_Param.tempValue%10);
        }
        button_struct.processed=1;
    }
    else if (button_struct.current==BTN_UP && edit_Param.Max!=0)//next up
    {
        ts_system.timeoutMenu=TIMEOUT ;
        edit_Param.tempValue++;
        if(edit_Param.tempValue>edit_Param.Max)
        {
             edit_Param.tempValue=edit_Param.Min;
        }
        if(cmdMemoryIsEmpty(menu_st.parameterSelected,edit_Param.tempValue)==1|| edit_Param.tempValue==edit_Param.Max)
        {
            SetSegmentValueIntermitentMain((edit_Param.tempValue-edit_Param.tempValue%10)/10, edit_Param.tempValue%10,TIME_1S);
        }
        else
        {
            SetSegmentValue((edit_Param.tempValue-edit_Param.tempValue%10)/10, edit_Param.tempValue%10);
        }
        button_struct.processed=1;
    }
    else if(edit_Param.Max>NUMBER_MAX_CMD &&edit_Param.tempValue>NUMBER_MAX_CMD )//full
    {
        if(menu_st.parameterSelected==0)
        {
            SetSegmentValueIntermitentMain(dL, dU,TIME_500MS);
        }
        else
        {
            SetSegmentValueIntermitentMain(dL, dP,TIME_500MS);
        }
    }
    else if(temp!=0xff&&(temp==0||temp==1|| temp ==2 || temp ==4 || temp==8))//Valida que a tecla recebida é das permitidas. temp000 é para teclas de comandos 12Bit
    {
        char pos;
        validSerial=validateRemoteSerialNumber(tempSerial,NO,&pos);

        TypeRemote_st typeRemote = getTypeRemote();
        if(validSerial==0&&(typeRemote==Keeloq_RollingCode || (var_sys_NVM.OnlyRollingCode==NO)))
        {
            saveNewSerial(menu_st.parameterSelected,tempSerial,edit_Param.tempValue);
            if(menu_st.parameterSelected==0&&edit_Param.tempValue==var_sys_NVM.positionRemotesFull&&var_sys_NVM.positionRemotesFull<99)
                var_sys_NVM.positionRemotesFull++;
            if(menu_st.parameterSelected==1&&edit_Param.tempValue==var_sys_NVM.positionRemotesWalk&&var_sys_NVM.positionRemotesWalk<99)
                var_sys_NVM.positionRemotesWalk++;
            sm_send_event(&menuConfiguration_stateMachine, ev_addRemotes);
            var_sys.DistanceProgrammingActive=NO;
            var_sys.ProgrammingDistanceIs=NoCMD;
            ts_system.timeSinalizationDigit=TIME_1S*2;
            SetSegmentValueIntermitentMain((edit_Param.tempValue-edit_Param.tempValue%10)/10, edit_Param.tempValue%10,TIME_200MS);
            if(edit_Param.Max==edit_Param.tempValue || edit_Param.Max==0 )
            {

                //Validação a verificar se aceita comandos 12BIT ou NO_ROLLINGCODE

                if(var_sys_NVM.positionRemotesFull==0 && var_sys_NVM.positionRemotesWalk==0 && typeRemote==Keeloq_RollingCode)
                {
//                    EUSART_Write_String((char*)"OR");
                    var_sys_NVM.OnlyRollingCode=YES;
                }
                //NO ELSE

                edit_Param.tempValue++;
                edit_Param.Value[0]=edit_Param.tempValue;
                SaveNVM_VarSystem(pageMemoryCounters);
            }


        }
    }
    else if(edit_Param.tempValue!=edit_Param.Max && (button_struct.current==BTN_CMD && button_struct.timer>=(TIME_1S*2)))
    {
        ts_system.timeoutMenu=TIMEOUT ;
        RemoveSerial(menu_st.parameterSelected,edit_Param.tempValue);
        SetSegmentValueIntermitentMain((edit_Param.tempValue-edit_Param.tempValue%10)/10, edit_Param.tempValue%10,TIME_1S);
        //SaveNVM_VarSystem(pageMemoryCounters);
    }
}

void controlSaveRemote(void){
     if (ts_system.timeSinalizationDigit<=0)
     {
         if(edit_Param.Max==0)
         {
             ts_system.timeoutMenu=10*TIME_1S;
             sm_send_event(&menuConfiguration_stateMachine, ev_NextRemote);
             SetSegmentValueIntermitentMain((edit_Param.tempValue-edit_Param.tempValue%10)/10, edit_Param.tempValue%10,TIME_1S);
         }
         else
         {
            sm_send_event(&main_stateMachine, ev_goto_StandBy);
            sm_send_event(&menuConfiguration_stateMachine, ev_ParameterIsSaved);
            SetSegmentValueMain(dMinus,dMinus);
            ClearFlag_rfCMD();
            ts_system.timeoutMenu = 0;
         }
     }

}

void controlLearnDigit(void)
{
    if(ts_system.timeSinalizationDigit<=0 )
    {
        ts_system.timeSinalizationDigit=TIME_100MS;
        if(var_sys.StateMotor==InClose)
        {
            SetSegmentValueLearn(Left);
        }
        else
        {
            SetSegmentValueLearn(Rigth);
        }
    }
}

