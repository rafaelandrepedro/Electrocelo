#include <xc.h>
#include <stdio.h>
#include "main.h"


#include "mcc_generated_files/eusart.h"

#include "sm_common.h"
#include "sm_ControlGate.h"
#include "mcc_generated_files/pin_manager.h"
#include "outputs.h"
#include "inputs.h"
#include "sm_ControlLearning.h"
#include "sm_Main.h"
#include "sm_MenuConfiguration.h"

extern sm_t controlGate_stateMachine;
extern sm_t main_stateMachine;
extern sm_t menuConfiguration_stateMachine;
extern sm_t controlLearning_stateMachine;
extern volatile varSystem var_sys;
extern volatile varSystem_NVM var_sys_NVM;
extern volatile timeslotSystem ts_system;
extern volatile RF_KEY_STRUCT rfCMD;
extern volatile BUTTONS_STRUCT button_struct;
char Abertura_pedonal = 0;
char aux_i=0;

void OpenFullOrder(void) {
    //EUSART_Write_String("\r\nAbre Full");
    
    var_sys.StateMotor = InOpenFull;
    sm_send_event(&controlGate_stateMachine, ev_OpenGate);
    var_sys.LastState = InOpenFull;
    InitSoftStart();
           

    
    
}
void WaitPreFlash(void)
{
  
    if ((var_sys_NVM.flashRGBMode == rgb_pre) && (var_sys.preflashingcontrol == YES) && (ts_system.timewaitFlashRGB <=0) && (aux_i == 0))
        {
            ts_system.timewaitFlashRGB = TIME_1S *3;  
            aux_i=1;
            
        }   
    if ((ts_system.timewaitFlashRGB <= 0) && (aux_i==1 ))  
        {
        
//            {if (var_sys.FimCurso_CloseIsEnabled == YES)
                var_sys.preflashingcontrol = NO;
                OpenFullOrder();
                InitFullAutoTime();
                sm_send_event(&main_stateMachine, ev_MotorIsOpen);
                aux_i=0;
                

        }
}
void CloseOrder(void) {
    //EUSART_Write_String("\r\nClose gate");
    var_sys.StateMotor = InClose;
    sm_send_event(&controlGate_stateMachine, ev_CloseGate);
    var_sys.LastState = InClose;
    InitSoftStart();
}

void OpenWalkOrder(void) {
    int diffTime = ((int) var_sys_NVM.walkTime * TIME_1S) - var_sys.PositionActual ;
    //EUSART_Write(var_sys_NVM.walkTime);
    if (diffTime > 0) {
        //EUSART_Write_String("\r\nAbre Walk");
        sm_send_event(&controlGate_stateMachine, ev_OpenGate);
        if (var_sys.Statedoorcontrol == st_Closed){
           ts_system.timeOpenWalk = diffTime; 
        }
        else{
            ts_system.timeOpenWalk = diffTime + TIME_1S;    
        }
        var_sys.StateMotor = InOpenWalk;
        var_sys.Timewalkisactived = YES;
        
    } 
    else 
    {
        //só para descontar o erro criado na paragem sem ele andar efectivamente.
       // setPositionInvertionInOpening();
    }
    var_sys.LastState = InOpenWalk;
    InitSoftStart();
}

void StopOrder(void) {
    
    
   var_sys.StateMotor = Stopped;   
   sm_send_event(&controlGate_stateMachine, ev_StopGate);
}

void InitWalkAutoTime(void) {
    //ts_system.timeWaitToClose=var_sys_NVM.autoTimeWalkClose*TIME_1S;
    ts_system.timeWaitToClose = ((int) var_sys_NVM.autoTimeWalkClose * TIME_1S);
    var_sys.AutoCloseActive = var_sys_NVM.autoTimeWalkClose;
}

void InitFullAutoTime(void) {
    //if (var_sys_NVM.operationMode != ModoPassoPasso && var_sys_NVM.homemPresente != 1) {  // rev 1.149 - modo Passo a passo passa a ter auto close quando chega ao local de pausa (full ou walk)
    if (var_sys_NVM.homemPresente == 0) {
        ts_system.timeWaitToClose = ((int) var_sys_NVM.autoTimeFullClose * TIME_1S);
        var_sys.AutoCloseActive = var_sys_NVM.autoTimeFullClose;
    }
}

void VerifyFollowMe(StateEnum securityClose) {
    // The photocell cannot actuate in close an open at the same time,
    // it can cause accidents. (Sr. Simões Electrocelos 08-01-2016)
    if (var_sys_NVM.folow_me != 0 && var_sys_NVM.photoCellInOpen == 0) //Confirma as condições que garatem o estado follow me activo.
    {
        if (securityClose == YES && var_sys.StateFollowIsOn == NO) {
            var_sys.StateFollowIsOn = YES; //Activa a FLAG StateFollowIsOn Isso vai ser usado qu
        }
    }
}

void sm_execute_ControlGate(sm_t *psm) {
    TypeCMD typeOpenOrder;


    // rev 1.149 - Do not run when the system is on the configuration menu.
    if ( (main_stateMachine.current_state == st_MenuConfiguration) && (menuConfiguration_stateMachine.current_state != st_LearningMode) )
    {
        return;
    }
        if (var_sys.preflashingcontrol == YES){
            
        WaitPreFlash();
    }
    
    //>>> State transitions.
    switch ((sm_state_ControlGate_t) psm->current_state) {
        case st_Idle:
        {
            

            if (psm->last_event == ev_GateClosed) {
                psm->current_state = st_Closed;

                
            } else if (psm->last_event == ev_GateOpened) {
                psm->current_state = st_Opened;

                
            }
        }
            break;
        case st_Closed:
        {
            if (psm->last_event == ev_OpenGate) {
                psm->current_state = st_Opening;
            } else if (psm->last_event == ev_SartLearning) {
                psm->current_state = st_Learning;
            }
        }
            break;
        case st_Opening:
        {
            if (psm->last_event == ev_StopGate) {
                psm->current_state = st_Opened;
            } else if (psm->last_event == ev_CloseGate) {
                psm->current_state = st_Closing;
            } else if (psm->last_event == ev_ErrorGate) {
                psm->current_state = st_Idle;
            }
        }
            break;
        case st_Closing:
        {
            if (psm->last_event == ev_StopGate) {
                psm->current_state = st_Opened;
            } else if (psm->last_event == ev_ClosedGate) {
                psm->current_state = st_Closed;
            } else if (psm->last_event == ev_OpenGate) {
                psm->current_state = st_Opening;
            } else if (psm->last_event == ev_ErrorGate) {
                psm->current_state = st_Idle;
            }
        }
            break;
        case st_Opened:
        {
            if (psm->last_event == ev_CloseGate) {
                psm->current_state = st_Closing;
            } else if (psm->last_event == ev_OpenGate) {
                psm->current_state = st_Opening;
            } else if (psm->last_event == ev_ErrorGate) {
                psm->current_state = st_Idle;
            }
            //>>> rev 1.152: DM Permitida a mudança para o processo de learn a partir do portão aberto.
            //>>>            Teve de ser alterado porque agora é permitido o acesso ao menu com portão aberto.
            else if (psm->last_event == ev_SartLearning) {
                //>>> rev 1.153: DM - Deixou de permitir aceder ao learn com o portão em estado de erro. Permite-se o acesso ao menu apenas para poder desligar fotocélulas ou banda de segurança.
                psm->current_state = st_Learning;
//                if ( var_sys.WorkTimeMaxAlarmState != EmAlarme && var_sys.NumberOffErrors <= MaxOfErrors )
//                {
//                    psm->current_state = st_Learning;
//                }
                //<<< rev 1.153: DM - Deixou de permitir aceder ao learn com o portão em estado de erro. Permite-se o acesso ao menu apenas para poder desligar fotocélulas ou banda de segurança.
            }
            //<<< rev 1.152: DM Permitida a mudança para o processo de learn a partir do portão aberto.
            //<<<            Teve de ser alterado porque agora é permitido o acesso ao menu com portão aberto.
        }
            break;
        case st_Learning:
        {
            if (psm->last_event == ev_LearningComplete) {
                psm->current_state = st_Closed;
            } else if (psm->last_event == ev_ErrorLearning) {
                psm->current_state = st_Idle;
            }
        }
            break;
        default:
        {
            while (1)
            {
                //asm("CLRWDT");  // DM: Make a WDT reset if the state machine is lost.
            }
        }
            break;
    }
    sm_send_event(&controlGate_stateMachine, ev_NULL);
    //<<< State transitions


    //>>> State implementations
    switch ((sm_state_ControlGate_t) psm->current_state) {
        case st_Idle:
        {

            
            ts_system.TimeStopADCZeroOffsetCalc = (5 * TIME_1S); // DM: Do not acquire de ADC Offset fot at least 5 seconds.

            //Bloqueia o estado quando esta em alarme.
            var_sys.PositionIsLost = YES;
            if (var_sys.WorkTimeMaxAlarmState == EmAlarme || var_sys.NumberOffErrors > MaxOfErrors) 
            {
                //Fica em erro com o motor imoblizado ate que uma tecla seja primida.
                //EUSART_Write_String((char*)"Alarme");
                typeOpenOrder = GetOpenOrder();
                SetSegmentValueIntermitent(dE,dr, TIME_1S); //Apresenta o erro de max time Alarm ou de numero de erros consecutivos
                ts_system.timeSinalizationDigit = TIME_500MS; //Renicializa tempo minimo de apresentção da mensagem.
                if ((typeOpenOrder != NoCMD) ||(button_struct.current==BTN_MENU || button_struct.current==BTN_DOWN ||button_struct.current==BTN_UP ))//Limpa o bloqueio pelo erro quando uma tecla e pressionada.
                {
                    var_sys.WorkTimeMaxAlarmState = Clear;
                    var_sys.NumberOffErrors = 0;
                    button_struct.processed=1;
                }
  
            }
            else
            {
                     
                    
                    var_sys.Statedoorcontrol = st_Closed;
                    var_sys.actualCounterMoves++;
                    var_sys.Timewalkisactived = 0;
                    var_sys.PositionActual = 0;

                    var_sys.PositionIsLost = NO;
                    var_sys.NumberOffErrors = 0;
                    var_sys.StateMotor = Stopped;

                    ts_system.timeSinalizationDigit = TIME_1S * 2;
                    SetSegmentValueIntermitent(dF, dC, TIME_200MS);
                    sm_send_event(&controlGate_stateMachine, ev_GateClosed);        
            
            }
                        
        }
            break;
        case st_Closed:
        {
            //Executa dos as comparações para verificação da trasição de estado e gera o respectivo evento.
            actionZone_Closed();
        }
            break;
        case st_Opening:
        {
            //Executa dos as comparações para verificação da trasição de estado e gera o respectivo evento.
            actionZone_Opening();

            ts_system.TimeStopADCZeroOffsetCalc = (5 * TIME_1S); // DM: Do not acquire de ADC Offset fot at least 5 seconds.
        }
            break;
        case st_Opened:
        {
            //Executa dos as comparações para verificação da trasição de estado e gera o respectivo evento.
            actionZone_Opened();

            ts_system.TimeStopADCZeroOffsetCalc = (5 * TIME_1S); // DM: Do not acquire de ADC Offset fot at least 5 seconds.
        }
            break;
        case st_Closing:
        {
            //Executa todas as comparações para verificação de trasição de estado e gera o respectivo evento.
            actionZone_Closing();

            ts_system.TimeStopADCZeroOffsetCalc = (5 * TIME_1S); // DM: Do not acquire de ADC Offset fot at least 5 seconds.
        }
            break;
        case st_Learning:
        {
            sm_execute_ControlLearning(&controlLearning_stateMachine);

            ts_system.TimeStopADCZeroOffsetCalc = (5 * TIME_1S); // DM: Do not acquire de ADC Offset fot at least 5 seconds.
        }
            break;
    }
    //<<< State Implementations
}

// This routine decides what to do when the gate is in the closed position.

void actionZone_Closed(void) {
    // This routine decides what to do when the gate is in the closed position.

    // The gate only responds to commands when it is out of the configuration menu.
    if (main_stateMachine.current_state != st_MenuConfiguration) {
        // The gate is not in the configuration menu.

        TypeCMD typeOpenOrder = GetOpenOrder(); // Read if an order was requested.

        StateEnum securityOpening = GetSecurityStateInOpening(); //Buscar os estado das seguranças

        if (var_sys_NVM.homemPresente == 1) {
            // On the HomemPresente mode the gate only moves with the local mechanical buttons.

            // On this mode the first button implements a Full open order and the
            // second a full close order.
            // (otherwise, the buttons are full open/close and Walk open/close)
            if (typeOpenOrder == TypeFullOpen && var_sys.FimCurso_OpenIsEnabled == NO && securityOpening == NO) {
                // The full open button was pressed.
                OpenFullOrder();
                sm_send_event(&main_stateMachine, ev_MotorIsOpen);
            }
        } else if (((typeOpenOrder == TypeFull || typeOpenOrder == TypeFullOpen) && securityOpening == NO) && (var_sys.preflashingcontrol == NO)) {
            // If one of the full open/close RF button or full open mechanical button is pressed, open the gate totally.
            // (e caso não exista nenhuma proteção ativada)
            
            if (var_sys_NVM.flashRGBMode == rgb_pre){
                var_sys.preflashingcontrol = YES;
                WaitPreFlash();
            }
            else{
                OpenFullOrder();
               InitFullAutoTime();
                sm_send_event(&main_stateMachine, ev_MotorIsOpen);
            }
        } 
        else if (typeOpenOrder == TypeWalk && securityOpening == NO && var_sys_NVM.walkTime !=0) {
            // If the walk open/close RF button is pressed, open the gate parcially.
            // (e caso não exista nenhuma proteção ativada)
            //EUSART_Write_String("TypeWalk-closed");          
            OpenWalkOrder();
            InitWalkAutoTime();
            sm_send_event(&main_stateMachine, ev_MotorIsOpen);
        }
    }
}

void actionZone_Opening(void) {
    StateEnum securityClosing = GetSecurityStateInClosing(); //Buscar os estado das seguranças quando o motor está no sentido de fecho
    StateEnum securityOpening = GetSecurityStateInOpening(); //Buscar os estado das seguranças quando o motor está no sentido de abertura
    TypeCMD typeOpenOrder = GetOpenOrder(); // Reads the RF commands.


    controlVelocity(); // Calculate the velocity to apply.
    InitFullAutoTime(); //

    var_sys.passoAPassoAutoClose = NO; // rev 1.149

    VerifyFollowMe(securityClosing);
    if (var_sys.NumberOffErrors > MaxOfErrors) {
        // If the movement erros is high, the gate goes to the erros state.
        var_sys.StateMotor = Stopped;
        sm_send_event(&controlGate_stateMachine, ev_ErrorGate);
    } else if (var_sys.StateMotor == InOpenWalk && ts_system.timeOpenWalk <= 0)//Quando tempo de abertura termina.
    {
        // If the gate is opening in walk mode and the open time has elapsed, 
        // stop the walk open gate movement and starts the pause time for the walk opening.

       // EUSART_Write_String("\r\nStop Walk");
        setPositionInvertionInOpening();
        StopOrder();
        InitWalkAutoTime();
        var_sys.passoAPassoAutoClose = YES; // rev 1.149
        Abertura_pedonal = 1;

    } else if ((var_sys.FimCurso_OpenIsEnabled == YES)||(var_sys.TimeMaxMotorIsON<=0) && (var_sys.LearningIsEnabled==NO) && (var_sys.PositionIsLost==NO) && (var_sys.Statedoorcontrol == st_Opening))//Quando é detectado o fim de curso na Abertura.
    {
        // When the gate reaches the open position, stops and indicates that the
        // current position is full open time (acquired during learning)

       //EUSART_Write_String("\r\nStop Full");
        var_sys.Statedoorcontrol = st_Opened;
        var_sys.PositionActual = var_sys_NVM.learningTimeToClose;
        var_sys.AutoInversionActiveStop = NO;
        var_sys.PositionIsLost = NO;
        var_sys.DigitSinalizedTemp = 1;
        var_sys.NumberOffErrors = 0;
        ts_system.timeSinalizationDigit = TIME_1S * 2;
        SetSegmentValueIntermitent(dF, d0, TIME_200MS);
        StopOrder();
        var_sys.passoAPassoAutoClose = YES; // rev 1.149
        
    }//Inicialização da inversão quando é detectada uma sobre corrente ou interrupção da fotocelula ou da barreira
    else if ((securityOpening == YES || (ts_system.TimeCurrentAlarm > 0 && var_sys.CurrentAlarmIsOn == YES && ts_system.TimeInversionStart <= 0)) && var_sys.AutoInversionActive == NO) {
        // one security during opening was activated (photo cell, tip barrier or encoder blocking)
        if (securityOpening != YES){
             var_sys.NumberOffErrors++;
        }// Increment the total number of errors (to limit the movement inversions and goto error state after 6 times)
        //EUSART_Write_String("\r\nStart Inversao");
        var_sys.AutoInversionActive = YES; // Indicates auto invertion activated
        ts_system.TimeWaitToNextState = TIME_500MS; // Waits for 500ms until it passes to the next step of the invertion
        ts_system.TimeStopElectricBrake = (TIME_1S+TIME_500MS);   // rev 1.156: DM - Cancels the eletric brake for 500ms to inver the motion.   // rev 1.156
        //ts_system.TimeStopEncoder = TIME_500MS;     // to inhibit the encoder blocking error for 500ms. (clears the encoder blocking error)
    }//Quando a falha é de corrente executa esta rotina.
    else if (ts_system.TimeCurrentAlarm > 0 && var_sys.AutoInversionActive == YES) {
        if (var_sys.InvertionCurrentClosing == YES) {
            //EUSART_Write_String("\r\nErro limite corrente continua.");
            var_sys.StateMotor = Stopped;
            setPositionInvertionInClosing();
            sm_send_event(&controlGate_stateMachine, ev_ErrorGate);
        } else if (ts_system.TimeWaitToNextState <= 0) {
            CloseOrder();
            // Adiciona um segundo á posição actual para evitar cair fora da zona de abrandamento.
            setPositionInvertionInOpening();
            var_sys.AutoInversionActive = NO;
            var_sys.InvertionCurrentOpening = YES;
            ts_system.TimeInversionStart = TIME_1S;
            ts_system.InvertionTimeClosingFromOpen = TIME_1S * 2;
            var_sys.InvertionClosingFromOpen = YES;
            //EUSART_Write_String("\r\nInversão Full");


        } else 
        {
            var_sys.StateMotor = Stopped;
        }
    }//Caso seja um fotocelula ou uma barreira executa esta
    else if (var_sys.AutoInversionActive == YES) {
        
               
                var_sys.StateMotor = Stopped;

        
        if (ts_system.TimeWaitToNextState <= 0) {
            CloseOrder();
            // Adiciona um segundo á posição actual para evitar cair fora da zona de abrandamento.
            setPositionInvertionInOpening();
            var_sys.AutoInversionActive = NO;
            var_sys.InvertionCurrentOpening = YES;
            ts_system.TimeInversionStart = TIME_1S;
            ts_system.InvertionTimeClosingFromOpen = TIME_1S * 2;
            var_sys.InvertionClosingFromOpen = YES;
            //EUSART_Write_String("\r\nInversão");


        } 
    }
    
     
   
    else if (var_sys.StateMotor == Stopped && ts_system.TimeWaitToNextState <= 0) {
        // ??????????????????????????????????????
      if(securityOpening != ST){
        var_sys.NumberOffErrors++;
        //EUSART_Write_String("\r\nErro na abertura");
        var_sys.StateMotor = Stopped;
        setPositionInvertionInOpening();
        sm_send_event(&controlGate_stateMachine, ev_ErrorGate);
      }else{
          setPositionInvertionInOpening();
          StopOrder();
          
      }    
          
    } else if (var_sys_NVM.homemPresente == 1) {
        if (typeOpenOrder != TypeFullOpen) {
            //EUSART_Write_String("\r\nStop HomemPresente");
            // Tira um segundo á posição actual para evitar cair fora da zona de abrandamento.
            //setPositionInvertionInOpening();
            StopOrder();
        }
    } else if (typeOpenOrder == TypeWalk && var_sys.StateMotor == InOpenWalk && var_sys_NVM.operationMode != ModoCondominio) {
        //EUSART_Write_String("\r\nPara Walk");

        // Tira um segundo á posição actual para evitar cair fora da zona de abrandamento.
        setPositionInvertionInOpening();
        StopOrder();
        InitWalkAutoTime();
    } else if ((typeOpenOrder == TypeFull || typeOpenOrder == TypeFullOpen || typeOpenOrder == TypeFullClose) && var_sys_NVM.operationMode != ModoCondominio) {
       // EUSART_Write_String("\r\nPara Full");

        // Tira um segundo á posição actual para evitar cair fora da zona de abrandamento.
        setPositionInvertionInOpening();
        StopOrder();
    }
}

void actionZone_Opened(void) {
    StateEnum securityClosing = GetSecurityStateInClosing(); //Buscar os estado das seguranças quando o motor está no sentido de fecho

    if ((securityClosing != NO) && (Abertura_pedonal == 0))  {
        InitFullAutoTime();
    }
    else if ((securityClosing != NO) && (Abertura_pedonal == 1)){
         InitWalkAutoTime();
    }
   
    TypeCMD typeOpenOrder = GetOpenOrder(); // Reads if there is an order

    VerifyFollowMe(securityClosing); // Verify if the condition to close automatically the gate after passing is achieved. Only if the follow me home mode is active on the menu.
    
    
    
    if ((KeyFull_GetValue()==0) && (var_sys_NVM.autoTimeFullClose != 0)&&(var_sys.AutoCloseActive != 0) && (button_struct.current != BTN_FULL)&& (var_sys_NVM.operationMode == ModoCondominio)){
      typeOpenOrder = NoCMD;  
    }
    

     if (typeOpenOrder != NoCMD) 
     {
        // An order is present.

        ts_system.timeSinalizationDigit = TIME_1S * 3;

       if ( var_sys_NVM.operationMode == ModoCondominio && var_sys_NVM.autoTimeFullClose == 0 && (typeOpenOrder == TypeFull|| typeOpenOrder == TypeFullClose ))    // rev 1.149 - On the Condomínio mode it cannot receive orders on the pause state
        {

            CloseOrder(); // Close function in modocondominio when the automaticfullclose it is in 0
           
        }
        else if (var_sys_NVM.homemPresente > 0) {
            // On the HomemPresente mode the gate only moves with the local mechanical buttons.

            // On this mode the first button implements a Full open order and the
            // second a full close order.
            // (otherwise, the buttons are full open/close and Walk open/close)
            if (typeOpenOrder == TypeFullOpen && var_sys.FimCurso_OpenIsEnabled == NO && var_sys.Statedoorcontrol != st_Opened) {
                // Full open button was pressed.
                OpenFullOrder();
            } else if (typeOpenOrder == TypeFullClose) {
                // Full close button was pressed.
                CloseOrder();
                //SetSegmentValueIntermitent(dL,d5,TIME_500MS);
            }
        } else if (var_sys.LastState == InClose && typeOpenOrder == TypeFull) {
            // The gate is closed and the full open/close button on the RF was pressed.
            OpenFullOrder();

            var_sys.AutoInversionActive = NO;   // rev 1.149 - ?????

        } else if (var_sys.LastState == InClose && typeOpenOrder == TypeWalk) {
            // The gate is closed and the walk open/close button on the RF was pressed.
            OpenWalkOrder();

            var_sys.AutoInversionActive = NO;   // rev 1.149 - ?????

        } else if (typeOpenOrder == TypeFullOpen) {
            if (var_sys.Statedoorcontrol == st_Opened){
                
            }else{
            OpenFullOrder();
            var_sys.AutoInversionActive = NO;   // rev 1.149 - ????? 
            }
        }
        else if( var_sys_NVM.autoTimeFullClose > 0 && var_sys_NVM.operationMode == ModoCondominio)
        {

            InitFullAutoTime();
            
        }
         
        else if(securityClosing == NO) 
        {
            
            CloseOrder();

        }
    }
    
    else if (KeyFull_GetValue()==0 && var_sys_NVM.autoTimeFullClose != 0){
        ts_system.timeWaitToClose = ((int) var_sys_NVM.autoTimeFullClose * TIME_1S);
        
    }
    else if (var_sys.StateFollowIsOn == YES && securityClosing == NO) {
        // When the follow me home mode is active, the gate closes after passing by the gate
        // (photo cell activated)
        var_sys.StateFollowIsOn = NO;
        //EUSART_Write_String("\r\nFOLLOW_CLOSE");

        //>>> rev1.149:
        // The follow me function only closes the gate 3 seconds after the peon has pessed by the gate.
        // For this we will start a pause time count of 3 seconds.
        //CloseOrder();????????????????
        var_sys.AutoCloseActive = var_sys_NVM.folow_me;
        ts_system.timeWaitToClose = var_sys_NVM.folow_me * TIME_1S;
        //<<< rev1.149:
    }else if (ts_system.timeWaitToClose <= 0 && var_sys_NVM.operationMode == ModoPassoPasso && var_sys.passoAPassoAutoClose == YES && var_sys.AutoCloseActive != 0) {  // rev 1.149 - New condition to auto close on the "passo a passo" mode
        // When the gate is in the passo a passo mode it will close automatically when it reaches the open state.
        var_sys.AutoCloseActive = 0;
       
        var_sys.passoAPassoAutoClose = NO;
        CloseOrder();
    } else if (ts_system.timeWaitToClose <= 0 && var_sys_NVM.operationMode != ModoPassoPasso && var_sys.AutoCloseActive != 0) {
        // When the gate is not in the passo a passo mode and the pause time has elapsed, the gate closes.
        var_sys.AutoCloseActive = 0;
      
        //EUSART_Write_String("\r\nAUTO_CLOSE");
        
        // rev 1.149 - 
        //CloseOrder();
        if ( var_sys.AutoInversionActive == YES )
        {
            var_sys.AutoInversionActive = NO;
            OpenFullOrder();
        }
        else
        {
            CloseOrder();
            var_sys.PositionIsLost = 0;
        }
    } else if ((var_sys.DigitSinalizedTemp == YES) && (securityClosing == NO)) // rev1.149 - the security is checked to present the security letters on that case or L0 otherwise.
    {
        if (ts_system.timeSinalizationDigit <= 1) {
            var_sys.DigitSinalizedTemp = NO;
        }
        //>>> rev 1.152 - Para poder apresentar "FO" quando atinge o fim de curso aberto.
        //SetSegmentValueIntermitent(dL, d0, TIME_500MS);   // estava a passar por cima da mensagem "FO".
        //<<< rev 1.152 - Para poder apresentar "FO" quando atinge o fim de curso aberto.
    }

}

void actionZone_Closing(void) {
    
    TypeCMD typeOpenOrder = GetOpenOrder();
    //StateEnum securityOpening=GetSecurityStateInOpening();//Buscar os estado das seguranças quando o motor está no sentido de abertura
    StateEnum securityClosing = GetSecurityStateInClosing(); //Buscar os estado das seguranças quando o motor está no sentido de fecho
    Abertura_pedonal = 0;
    
    InitFullAutoTime(); //  rev 1.149 - In automatic mode, the pause must be applied to the gate when a button is pressed with the gate closing.

    var_sys.passoAPassoAutoClose = NO; // rev 1.149

    if (var_sys.NumberOffErrors > MaxOfErrors) {
        // If the movement erros is high, the gate goes to the erros state.
        var_sys.StateMotor = Stopped;
        sm_send_event(&controlGate_stateMachine, ev_ErrorGate);
    } else if ((var_sys.FimCurso_CloseIsEnabled == YES)||(var_sys.TimeMaxMotorIsON<=0) && (var_sys.LearningIsEnabled==NO) && (var_sys.PositionIsLost==NO)) {
        // The gate reached the closed position!
        if (var_sys_NVM.flashLightMode == 2) {
            ts_system.TimeOnFlashLigth = (long) ((long) var_sys_NVM.ligthTime * TIME_1MIN);
        }
        else {
            ts_system.TimeOnFlashLigth = 0;
        }
        var_sys.AutoInversionActiveStop = NO;
        //EUSART_Write_String("\r\nFechado");
        var_sys.Statedoorcontrol = st_Closed;
        var_sys.actualCounterMoves++;
        var_sys.Timewalkisactived = 0;
        var_sys.PositionActual = 0;

        var_sys.PositionIsLost = NO;
        var_sys.NumberOffErrors = 0;
        var_sys.StateMotor = Stopped;

        ts_system.timeSinalizationDigit = TIME_1S * 2;
        SetSegmentValueIntermitent(dF, dC, TIME_200MS);


         sm_send_event(&controlGate_stateMachine, ev_ClosedGate);
         
        //<<< DM: If the flashLightMode is not "modo de cortesia" the light will not
        //<<<     remain ON after the gate closes.
    }//Inicialização da inversão quando é detectada uma sobre corrente ou interrupção da fotocelula ou da barreira
    else if ((securityClosing == YES || (ts_system.TimeCurrentAlarm > 0 && var_sys.CurrentAlarmIsOn == YES && ts_system.TimeInversionStart <= 0)) && var_sys.AutoInversionActive == NO) {
        // EUSART_Write_String("\r\nStart Inversao");
         if (securityClosing != YES){
            var_sys.NumberOffErrors++;   
        }
        var_sys.NumberOffErrors++;
        var_sys.AutoInversionActive = YES;
        ts_system.TimeWaitToNextState = TIME_500MS;
        ts_system.TimeStopElectricBrake = (TIME_1S+TIME_500MS);   // rev 1.156: DM - Cancels the eletric brake for 500ms to inver the motion.   // rev 1.156
       // InitSoftStop(); //V1.156 barreira_br 2016.11.25
    }//Quando a falha é de corrente executa esta rotina.
    else if (ts_system.TimeCurrentAlarm > 0 && var_sys.AutoInversionActive == YES) {
        if (var_sys.InvertionCurrentOpening == YES) {
            //EUSART_Write_String("\r\nErro limite corrente continua.");
            var_sys.StateMotor = Stopped;
            setPositionInvertionInClosing();
            sm_send_event(&controlGate_stateMachine, ev_ErrorGate);
        } else if (ts_system.TimeWaitToNextState <= 0) {
         if(var_sys.Timewalkisactived == YES){
                OpenWalkOrder();
               // var_sys.PositionActual= 0;     
            }   
            else{
             
            OpenFullOrder();
            // Adiciona um segundo á posição actual para evitar cair fora da zona de abrandamento.
            setPositionInvertionInClosing();
            }
            var_sys.AutoInversionActive = NO;
            var_sys.InvertionCurrentClosing = YES;
            ts_system.TimeInversionStart = TIME_1S;
            //EUSART_Write_String("\r\nInversão Full");

    
        } else 
        {
            var_sys.StateMotor = Stopped;
        }
    } else if (var_sys.AutoInversionActive == YES) {
                   
                var_sys.StateMotor = Stopped;
        
         
         
         
        if (ts_system.TimeWaitToNextState <= 0) {
            if(var_sys.Timewalkisactived == YES){
                OpenWalkOrder();
               // var_sys.PositionActual= 0;     
            }          
            else{
               // EUSART_Write_String("OpenFullOrder");
                 OpenFullOrder();
            // Adiciona um segundo á posição actual para evitar cair fora da zona de abrandamento.
            setPositionInvertionInClosing();
             }
            var_sys.AutoInversionActive = NO;
            //EUSART_Write_String("\r\nInversão Full");
   
        } 

    } else if (var_sys.StateMotor == Stopped) {
        //EUSART_Write_String("\r\nErro no fecho");
        if(securityClosing != ST){
           var_sys.NumberOffErrors++;
           var_sys.StateMotor = Stopped;
           setPositionInvertionInClosing();
           sm_send_event(&controlGate_stateMachine, ev_ErrorGate); 
        }else
        {
            setPositionInvertionInClosing();
            StopOrder();
        }

    } else if (ts_system.InvertionTimeClosingFromOpen <= 0 && var_sys.InvertionClosingFromOpen == YES) {
        // Adiciona um segundo á posição actual para evitar cair fora da zona de abrandamento.
        setPositionInvertionInClosing();
        var_sys.InvertionClosingFromOpen = NO;
        StopOrder();
        
    } else if ((var_sys_NVM.homemPresente == 1) || (var_sys_NVM.homemPresente == 2)) {
        if (typeOpenOrder != TypeFullClose) {
            //ts_system.timeSinalizationDigit=TIME_1S*3;
            //SetSegmentValueIntermitent(dL,d5,TIME_500MS);
            //EUSART_Write_String("\r\nStop HomemPresente");
            //Adiciona um segundo á posição actual para evitar cair fora da zona de abrandamento.
            //setPositionInvertionInClosing();
            StopOrder();
        }
    } else if (typeOpenOrder != NoCMD) {
        // Adiciona um segundo á posição actual para evitar cair fora da zona de abrandamento.
//        setPositionInvertionInClosing();
//        StopOrder();

        // rev 1.149
//        if ( var_sys_NVM.operationMode != ModoCondominio )
        if ( var_sys_NVM.operationMode == ModoPassoPasso )
        {
            setPositionInvertionInClosing();
            StopOrder();
            
            if (typeOpenOrder == TypeWalk && /*var_sys.StateMotor == InOpenWalk &&*/ var_sys_NVM.operationMode != ModoCondominio)
            {
                InitWalkAutoTime();
                var_sys.showAP = YES;
            }

        }
        else   
        {
            if (typeOpenOrder != TypeFullClose){
                var_sys.AutoInversionActive = YES;
                ts_system.TimeWaitToNextState = TIME_500MS;
                //InitSoftStop();  //V1.156 barreira_br 2016.11.25 
            }
            else{
               StopOrder(); 
            }
            
        }
   
    }
}

void InitSoftStart(void) {
    if (var_sys_NVM.softStart != 0 && var_sys.AutoInversionActive == NO) {
        //EUSART_Write_String((char*)"\r\nInit softStart");
        
        //>>> rev 1.152 - Pedido do cliente para iniciar o softstart a partir de uma
        //>>>             potência mínima e não a partir do zero.
        //var_sys.velocityFactor = 0;
        //var_sys.velocityFactor = GetMotorPower();
        var_sys.velocityFactorstop = 0; 
        var_sys.velocityFactor = 0;
        var_sys.velocityFactor = GetMotorPower();
        if ( var_sys.velocityFactor > MIN_SOFT_START_POWER )
        {
            var_sys.velocityFactor = MIN_SOFT_START_POWER;
        }
        else
        {
            // Do nothing, the start velocity is already higher than the minimum
            // defined by MIN_SOFT_START_POWER.
        }
        
        //<<< rev 1.152 - Pedido do cliente para iniciar o softstart a partir de uma
        //<<<             potência mínima e não a partir do zero.
        
        ts_system.timeSoftStart = var_sys.velocityFactor + 1;
        //ts_system.TimeStopEncoder = TIME_200MS;	// rev 1.149
        var_sys.SoftStartDecrementControl = 10 - var_sys_NVM.softStart;
    }

  

}

void InitSoftStop(void) {       //V1.156 barreira_br 2016.11.25
    if (((var_sys.AutoInversionActiveStop == YES)|| (var_sys.AutoInversionActive == YES))&&(var_sys_NVM.softstop >0)) {

        
        var_sys.velocityFactor = 0;
        var_sys.velocityFactorstop = 0;
        var_sys.velocityFactorstop = GetMotorPower();
        

        
        ts_system.timeSoftStop = var_sys.velocityFactorstop + 1;
        //ts_system.TimeStopEncoder = TIME_200MS;	// rev 1.149
        var_sys.SoftStopDecrementControl = 10 - var_sys_NVM.softstop;
    }
    
}


void setPositionInvertionInClosing() {
    //var_sys.errorOpening=var_sys.errorOpening+TIME_1S;
    //var_sys.PositionActual=var_sys.PositionActual+TIME_1S;

     // EUSART_Write_String_n(var_sys.PositionActual,4);
    if(var_sys_NVM.TypeofMotor != 2){ 
  
       var_sys.PositionActual += TIME_100MS; // DM: The compiller reduces the code this way. ALTEREI ISTO AGORA 
        
    }
    else 
    {
       var_sys.PositionActual -= TIME_50MS;    
    }
    
    if (var_sys.PositionActual > getTimeDecelaration(InOpenFull)&& var_sys_NVM.TypeofMotor != 2) {
        var_sys.PositionActual = getTimeDecelaration(InOpenFull);
        //var_sys.PositionActual= var_sys.PositionActual+TIME_1S;
        //var_sys.PositionActual += TIME_1S; // DM: The compiller reduces the code this way.ALTEREI ISTO AGORA 
    } else if (var_sys.PositionActual < getTimeDecelaration(InClose) && var_sys_NVM.TypeofMotor != 2) {
        var_sys.PositionActual = getTimeDecelaration(InClose);
    }
       //EUSART_Write_String_n(var_sys.PositionActual,4);
    var_sys.TimeMaxMotorIsON = ((signed long)var_sys_NVM.learningTimeToOpen - var_sys.PositionActual) + (var_sys_NVM.decelarationOpen*TIME_500MS)+ TIME_1S*10;
    
}

void setPositionInvertionInOpening() {

    if(var_sys_NVM.TypeofMotor != 2){
       var_sys.PositionActual -= TIME_100MS; // DM: The compiller reduces the code this way. ALTEREI ISTO AGORA   
    }
    else{

         var_sys.PositionActual += TIME_50MS; // DM: The compiller reduces the code this way. ALTEREI ISTO AGORA 
    }
      
   
        
    if (var_sys.PositionActual < getTimeDecelaration(InClose)) {
        var_sys.PositionActual = getTimeDecelaration(InClose); 
    } else if (var_sys.PositionActual > getTimeDecelaration(InOpenFull)) {
        var_sys.PositionActual = getTimeDecelaration(InOpenFull);
    }
    var_sys.TimeMaxMotorIsON = var_sys.PositionActual + var_sys_NVM.decelarationClose*TIME_500MS + TIME_1S*10;
//EUSART_Write_String_n(var_sys.PositionActual,4);
}
