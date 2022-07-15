/*
 * File:   main.h
 * Author: cpereira
 *
 * Created on 4 de Setembro de 2014, 12:29
 */



//Usar Como Exemplo para decumentação de funções.

/**
 * \brief Função de leitura do pedido, validação do request e identificação da função.
 *
 * \param modbusMemory	estrutura de memória do Modbus
 * \param _slave		estrutura de identificação do Slave
 * \param ringBufferRX	array que contém os dados recebidos do master
 * \param ringBufferTX	array que contém os dados a enviar do master
 * \param TCP_Active	0: Modo RTU
 *						1: Modo TCP
 *
 * \return int	0 if OK
 *				More than 0 is a exception code,
 *				Less than 0 is No Reply code.
 */

#ifndef MAIN_H
#define	MAIN_H

#include "mcc_generated_files/pin_manager.h"


#ifdef	__cplusplus
extern "C" {
#endif


#define VERSION_ERIS     1
#define REVISION_ERIS    180
#define VERSION "1.1.0"    


#define _TIME_10MS		10
#define _TIME_50MS		50

#define MAIN_TIMESLOT       _TIME_50MS
#define ENCODER_TIMESLOT	1

#define TIME_50MS		(  50/MAIN_TIMESLOT)
#define TIME_1S			(1000/MAIN_TIMESLOT)
#define	TIME_100MS		( 100/MAIN_TIMESLOT)
#define	TIME_200MS		( 200/MAIN_TIMESLOT)
//#define	TIME_300MS      ( 300/MAIN_TIMESLOT)
#define	TIME_500MS		( 500/MAIN_TIMESLOT)
#define TIME_1MIN		(TIME_1S*60)
#define TIMEOUT           (TIME_1S*5)
//#define MaxOfErrors     5
#define MaxOfErrors     3   //rev1.149  - Reduce the number of retries.

#define NUMBER_MAX_CMD  99

typedef enum{
        NoCMD,
        TypeFull,
        TypeWalk,
        TypeFullOpen,
        TypeFullClose,
        TypeProgrammingModeWalk,
        TypeProgrammingModeFull,
}TypeCMD;

typedef enum{
        Stopped,
        InOpenFull,
        InOpenWalk,
        InClose,
}stateMotor_enum;

typedef enum{
        ModoAutomatico,
        ModoPassoPasso,
        ModoCondominio,
}operationMode_enum;

typedef enum{
        Keeloq_RollingCode,
        Keeloq_NoRollingCode,
        DIP_12BIT,
}TypeRemote_st;

typedef enum{
        NO,
        YES,
        ST,
        SECUR        
}StateEnum;

typedef enum{
        Clear,
        Active,
        EmAlarme
}AlarmesStateEnum;


#define   NumberPages_VarSystem 4
typedef struct
{
    //page0
    unsigned char decelarationOpen;         // Duration of the deceleration phase on the opening process [0..15sec].
    unsigned char decelarationClose;        // Duration of the deceleration phase on the closing process [0..15sec].   
    unsigned char motorPower;               // Motor Strength level [1..9].
    unsigned char motorSensitivity;         // Motor current sensitivity level during full speed moving [0..9].
    unsigned char walkTime;                 // Time to open the gate for peons passing [0..99].
    unsigned char autoTimeFullClose;        // Pause time after opening process that the system waits until it starts the close process automatically [0..99sec, being 0-OFF].
    unsigned char autoTimeWalkClose;        // Pause time after peons passage opening process that the system waits until it starts the close process automatically [0..99sec, being 0-OFF].
    unsigned char photoCellIsON;            // Photo cell state [0-OFF, 1-ON].
    unsigned char photoCellInOpen;          // Photo cell used on the opening process [0-Not used, 1-Used].
    unsigned char securityBandIsON;         // Security Band state [0-Not installed, 1-Installed and used].
    unsigned char securityBandType;         // Security Band Type [0-8K2 type, 1-NC type].
    unsigned char securityBandInOpen;       // Security Band used on the opening process [0-Not used, 1-Used].
    unsigned char operationMode;            // Operation mode [0-Modo automático, 1-Modo passo-a-passo, 2-Modo Condomínio].
    unsigned char flashLightMode;           // Flashlight operation mode [0-1Hz Blink closing, 0.5Hz openning and ON at autoTime????Close time; 1- ON opening and closing and OFF at autoTime????Close time; 2- ON opening, closing, at autoTime????Close time and ligthTime minutes after closing]. (rev1.149)
    unsigned char programmingDistance;      // Distance programming enable [0-Disabled, 1-Enabled].
    unsigned char decelarationSensivity;    // Motor current sensitivity level during deceleration moving phase [0..9].
    
    
    //page1
    unsigned char homemPresente;            // Indicates if the gate is controlled only manually by a person [0-Controlled normally, 1-Controlled only by hand on the buttons].
    unsigned char logicDigital;             // Defines the buttons functioning logic [0- Button 1 is full open and close, Button 2 is peons open and close; 1- Button 1 is full open and Button 2 is full close].
    unsigned char softStart;                // Soft start enable state [0-Disabled, 1-Enabled].
    unsigned char softstop;                 // Soft sto enable state [0-Disabled, 1-Enabled].
    unsigned char ligthTime;                // Time for the flashlight ON after closing the gate (implies flashLightMode=2) [0..99 minutes].
    unsigned char folow_me;                 // Indicates if the follow me mode is active. When active, the gate initiates the close process 3 seconds after a passage trough the photocell. (rev1.149)
    unsigned char Stopboton;                // Activa o stop botton
    unsigned char electricBrake;            // Electric brake state [0-Disabled, 1-Enabled].
    unsigned char velocityDecelaration;     // Velocity to decelerate the gate in levels [1..9].
    unsigned char flashRGBMode;             // Indicates the RGB flashlight functioning mode [0-Continuous mode, 1-0.5Hz Blinking mode].
    unsigned char reserved10;         // Difene the type of the deceration us want. The decelation have two type one have 2 semi-cles and more 1 semi-cicle and other have only one semi cycle one and other cycle off.     unsigned char reserved3;
    unsigned char Direction_motor;          // Difene the direcion of motor. Can choose the direccion and change the limitswitch and motor relay.
    unsigned char TypeofMotor;              // Escolhe o tipo de motor que irá ser usado.
    unsigned char reserved;                 // Indicates when the motor has a movement encoder to control his movement.
    unsigned char reserved6;
    unsigned char reserved7;
    //unsigned char reserved8;

    
    //page2
    unsigned char positionRemotesFull;
    unsigned char positionRemotesWalk;
    unsigned long counterMoves;

    unsigned char OnlyRollingCode;
    unsigned char reserved12;
    unsigned long learningCurrentDecelarationClose;
    unsigned long learningCurrentDecelarationOpen;


    //page3
    unsigned int learningCurrentNormalClose;
    unsigned int learningCurrentNormalOpen;
    unsigned long learningTimeToOpen;
    unsigned long learningTimeToClose;
    unsigned char reserved31;
    unsigned char reserved32;
    unsigned char reserved33;
    unsigned char reserved34;

    }varSystem_NVM;


typedef struct
{
	stateMotor_enum	StateMotor;
    StateEnum       photoCellIsObstructed;
    StateEnum       SecurityBarIsObstructed;
    StateEnum       FimCurso_CloseIsEnabled;
    StateEnum       FimCurso_OpenIsEnabled;
    int             decelerationOpenCurrent;
    int             decelerationCloseCurrent;
    char            StartFromButton;
    unsigned char   WaitTimeCloseInitial;
    stateMotor_enum LastState;
    StateEnum       TriacON;
    StateEnum       InStoping;
    int             velocityFactor;
    int             velocityFactorstop;
    char            AutoInversionActiveStop;
    char            SoftStopDecrementControl;
    char            SoftStartDecrementControl;
    char            Torquerelanty;
    char            Activatecounter;
    char            Counter_Learning;
    unsigned long   TimeMaxMotorIsON;               // Maximum allowed ON time for the motor.
    char            Statedoorcontrol;
    char            preflashingcontrol;

    signed long     PositionActual;
    StateEnum       DigitSinalizedTemp;
    unsigned char   AutoCloseActive;
    char            upFaseRGB;
    char            upFaseFlashligth;
    char            LearningIsEnabled;
    char            AutoInversionActive;

    char            ControlReleCapacitorOpen;
    char            ControlReleCapacitorClose;
    char            programinAutomatic;
    
    StateEnum       photoCellMakeErrorOpen;
    StateEnum       photoCellMakeErrorClose;
    StateEnum       SecurityBarMakeError;
    unsigned int    ActualCurrent;
    unsigned long   ActualHistCurrent;
    unsigned long   ActualComparatorCurrent;
    int             velocityActual;
    StateEnum       StateFollowIsOn;
    TypeCMD         ProgrammingDistanceIs;
    unsigned long   actualCounterMoves;
    StateEnum       DistanceProgrammingActive;//Serve Para Sinalizar a FlashLigth
    StateEnum       CurrentAlarmIsOn;
    AlarmesStateEnum       WorkTimeMaxAlarmState;
    char            NumberOffErrors;
    StateEnum       InvertionCurrentClosing;
    StateEnum       InvertionCurrentOpening;
    StateEnum       InvertionClosingFromOpen;
    StateEnum       LearningDecelaration;
    StateEnum       PositionIsLost;
    char            StateVersion;
    char            Timewalkisactived;

    
    
    unsigned int    ADCZeroOffset;
    unsigned char       Control50or60hz;
    unsigned char  frequenciamotor;
    
//    unsigned int    motorCurrentSpeed;              // This variable will have the calculated motor speed using the encoder transition count.
//    char            errorEncoder;                   // Indicates when the encoder bloking error is active.
//    //char            encoderLastState;               // This variable has the last state of the encoder input, used to detect transitions.
//    //char            encoderFirstTransitionDetected; // Used to count the time (with encoderCountBetweenTransitions) since the last valid transition detected. Used to calculate the motor speed.
//    //unsigned int    encoderCountBetweenTransitions; // Used to count the time (with encoderFirstTransitionDetected) since the last valid transition detected.Used to calculate the motor speed.
//    //unsigned int    encoderCountSinceLastTransition;// This  counter will be used as auxiliar to check for blocked motor, because the process of the variables above takes some time.
//                                                    // When this counter climbs for more than 100ms we will consider that the motor is blocked!
    char            showAP;
    char            passoAPassoAutoClose;

    #ifdef  TEST_RESET
    char            showReset;
    #endif
    
}varSystem;

typedef struct
{
    char     ts_TimeSlot500ms;
    char     ts_TimeSlot50ms;
    char    ts_TimeSlot1ms;
    char	ts_TimeSlotMain;
    char    ts_TimeSlotEEPROM;
    char    ts_TimeSlotTRIAC;
    int     ts_TRIACWait;
    
    int     Debug_TS;
    int     timeFreqDigit;
    int     timeSinalizationDigit;
    int     timeoutMenu;
    int     timeOpenWalk;
    int     timeWaitToClose;
    int     TimeLastCommand;
    int     timeSoftStart;                  // Duration of the soft start phase.
    int     timeSoftStop;
    int     TimeChargeCondesador;           // Time to ignore the current every first second that the motor starts to run. The charge of the capacitor surges to much current.
//    int     timeForNextDecelaration;
    int     timeFreqRGB;
    int     timeFreqFlashligth;
    long    TimeOnFlashLigth;
    int     TimeWaitToNextState;            // Usada para inibição temporária em inversões de marcha e trnsições de fases no learning.
//    int     TimeDecelaration;
    int     timeBetweenSaveCounters;        // Time between counters saving. Currently 5 min.
    int     TimeElectricBrake;              // 
    int     TimeCurrentAlarm;               // Time to show the current alarm on the display.
    
    int     TimeStopedBeforeDecelaration;   // Time of stopped motor before starting the deceleration phase.
    int     TimeCurrentWaitForAlarm;        // Time to ignore the current on a deceleration start process (makes a pair with TimeStopedBeforeDecelaration)
    int     TimeInversionStart;             // Time to ignore the current on a inversion process
    int     InvertionTimeClosingFromOpen;
    int     TimeWaitToGetCurrent;           // Time used to wait for a valid Stable Current during the learn process.
    int     TimeLearningDecelaration;       // Time of the deceleration learning phase.
    int     TimeTransitionDecelaration;     // Time to ignore the current alarms on the running to deceleration phase.
    int     timewaitBeforeSoftStart;        // Time to ignore the current alarms after the soft start has ended.
    int     TimeShowVersion;                // time used durint the version display.
    int     TimeStopADCZeroOffsetCalc;      // Time used to stop the ADC Zero offset calculation.
    int     TimeStopElectricBrake;          // rev 1.156 - Time during wich the electronic brake cannot be used, because a protection has been actuated and the gate needs to invert the motion in a hurry.
    int     TimeReleCapacitor;
    int     TimeWaitReleCapacitor;
    int     timewaitFlashRGB;
   
    
}timeslotSystem;

#ifdef  DEBUG_RESET
extern  char resetTypeSTATUS;
extern  char resetTypePCON;
#endif

void controlTimeslots(void);
void decrementTimeslot(int * ts);
void ShowVersion(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

