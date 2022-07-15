
#include <xc.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "controlMemory.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/drivers/i2c_simple_master.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
//#include "mcc_generated_files/eusart.h"
#include "inputs.h"



unsigned long memoryTEMP[4];
extern volatile varSystem var_sys;
extern volatile varSystem_NVM var_sys_NVM;
extern volatile timeslotSystem ts_system;
//unsigned int xx;



void checkNVM_VarSystem ( void );


TypeCMD validateRemoteSerialNumber(unsigned long serial, StateEnum VerifyOnlySerial, char* position){
    char i=0;
    char j=0;
    unsigned long mask;

    //Validação para a programção á distancia.
    if(VerifyOnlySerial==YES)
    {
        mask=0x0FFFFFFF;
    }
    else
    {
        mask=0xFFFFFFFF;
    }

    for (i=0;i<var_sys_NVM.positionRemotesFull;i++)
    {
        if(i%4==0)
        {
            j=0;
            
            i2c_readDataBlock(MEMORY_ADDRESS, (uint16_t)(STARTADD_FULL + (i * 4)),(char*)memoryTEMP, PAGE_SIZE);
        }
        if((unsigned long)serial==((unsigned long)memoryTEMP[j]&mask))
        {

            position[0]=i;
            return TypeFull;

        }
        j++;

    }
    
    for (i=0;i<var_sys_NVM.positionRemotesWalk;i++)
    {
        if(i%4==0)
        {
            j=0;
            i2c_readDataBlock(MEMORY_ADDRESS, (uint16_t)(STARTADD_WALK + (i * 4)),(char*)memoryTEMP, PAGE_SIZE);
        }

        if((unsigned long)serial==((unsigned long)memoryTEMP[j]&mask))
        {
            //EUSART_Write_String("typeWalk");
            position[0]=i;
            return TypeWalk;
        }
        j++;
    }
    //EUSART_Write_String("noCMD");
    return NoCMD;
}

void saveNewSerial(char cmdType,unsigned long tempSerial, char position)
{
    if(cmdType==0)
    {
        //EUSART_Write_String("\r\nSave FULL");
        i2c_writeNBytes(MEMORY_ADDRESS, (uint16_t)(STARTADD_FULL + (position * 4)), (char*)&tempSerial, CMD_SIZE);
    }
    else
    {
        //EUSART_Write_String("\r\nSave WALK");
        i2c_writeNBytes(MEMORY_ADDRESS, (uint16_t)(STARTADD_WALK + (position * 4)), (char*)&tempSerial, CMD_SIZE);
    }
}

void RemoveSerial(char cmdType, char position)
{
    unsigned long tempSerial=0;
    
    
    if(cmdType==0)
    {
       i2c_writeNBytes(MEMORY_ADDRESS, (uint16_t)(STARTADD_FULL + (position * 4)), (char*)&tempSerial, CMD_SIZE);
    }
    else
    {
       i2c_writeNBytes(MEMORY_ADDRESS, (uint16_t)(STARTADD_WALK + (position * 4)), (char*)&tempSerial, CMD_SIZE);
    }
}

char cmdMemoryIsEmpty(char cmdType, char position)
{
    unsigned long tempSerial=0;
    
    
     if(cmdType==0)
    {
         i2c_readDataBlock(MEMORY_ADDRESS, (uint16_t)(STARTADD_FULL + (position * 4)),(char*)&tempSerial, CMD_SIZE);
    }
    else
    {
         i2c_readDataBlock(MEMORY_ADDRESS, (uint16_t)(STARTADD_WALK + (position * 4)),(char*)&tempSerial, CMD_SIZE);
    }

     if( tempSerial==0)
     {
         return 1;
     }
     else
     {
         return 0;
     }
}



//**************************************************************************************
// Load all vars from memory of NVM_VarSystem
//**************************************************************************************
void loadNVM_VarSystem(void)
{
    if((I2C1_Read1ByteRegister(MEMORY_ADDRESS, 0) == 0xFF) && (I2C1_Read1ByteRegister(MEMORY_ADDRESS, 16) == 0xFF))
    {
        ResetDefaultMemory(SC);
        var_sys_NVM.learningTimeToClose                = 0;
        var_sys_NVM.learningTimeToOpen                 = 0;
        var_sys_NVM.learningCurrentNormalClose         = 0;
        var_sys_NVM.learningCurrentNormalOpen          = 0;
        var_sys_NVM.learningCurrentDecelarationClose   = 0;    // Included by Deniz Martins
        var_sys_NVM.learningCurrentDecelarationOpen    = 0;    // Included by Deniz Martins
        SaveNVM_VarSystem(pageMemoryLearningVars);
        var_sys_NVM.positionRemotesFull                = 0;    // var_sys_NVM.positionRemotesFull;
        var_sys_NVM.positionRemotesWalk                = 0;    // var_sys_NVM.positionRemotesWalk;
        var_sys_NVM.OnlyRollingCode                    = NO;   // Included by Deniz Martins. Limpa a Flag de modo a aceitar todos os tipos de comandos.
        var_sys_NVM.counterMoves                       = 0;    // var_sys_NVM.counterMoves;
       SaveNVM_VarSystem(pageMemoryCounters);
       // EUSART_Write_String((char*)"resetdefaut");
         var_sys_NVM.TypeofMotor                       = 0;
    }

    i2c_readDataBlock(MEMORY_ADDRESS, (uint16_t)(pageMemoryP * PAGE_SIZE),(char*)&var_sys_NVM,PAGE_SIZE);
    i2c_readDataBlock(MEMORY_ADDRESS, (uint16_t)(pageMemoryE * PAGE_SIZE),(char*)&var_sys_NVM.homemPresente, PAGE_SIZE);
    i2c_readDataBlock(MEMORY_ADDRESS, (uint16_t)(pageMemoryCounters * PAGE_SIZE),(char*)&var_sys_NVM.positionRemotesFull,PAGE_SIZE);
    i2c_readDataBlock(MEMORY_ADDRESS, (uint16_t)(pageMemoryLearningVars * PAGE_SIZE),(char*)&var_sys_NVM.learningCurrentNormalClose, PAGE_SIZE); 
    //EUSART_Write_String((char*)"reagi2c");
    // The read values should be verifyed to check for corruption.
    checkNVM_VarSystem();

    var_sys.actualCounterMoves=var_sys_NVM.counterMoves;
}

    
//**************************************************************************************
// Save all vars in memory of NVM_VarSystem by page.
//**************************************************************************************
void SaveNVM_VarSystem(unsigned char page)
{
    unsigned int tempAdd=page*16;
    char* point=(char*)&var_sys_NVM;
    point=point+tempAdd;
   i2c_writeNBytes(MEMORY_ADDRESS, tempAdd, point, PAGE_SIZE);
}

//**************************************************************************************
// Reset all memory NVM_VarSystem to default values.
//**************************************************************************************
void ResetDefaultMemory(unsigned char type)
{
 
   // var_sys_NVM.decelarationType      = decelarationType_default;
    var_sys_NVM.decelarationOpen        = decelarationOpen_default;	
    var_sys_NVM.motorPower              = motorPower_default;    
    var_sys_NVM.decelarationClose       = decelarationClose_default;	    
    var_sys_NVM.photoCellIsON           = photoCellIsON_default;
    var_sys_NVM.photoCellInOpen         = photoCellInOpen_default;
    var_sys_NVM.securityBandIsON        = securityBandIsON_default ;
    var_sys_NVM.securityBandType        = securityBandType_default;
    var_sys_NVM.securityBandInOpen      = securityBandInOpen_default;
    var_sys_NVM.flashLightMode          = flashLightMode_default;
    var_sys_NVM.programmingDistance     = programmingDistance_default;
    var_sys_NVM.decelarationSensivity   = decelarationSensivity_default;
    var_sys_NVM.homemPresente           = homemPresente_default;
    var_sys_NVM.autoTimeWalkClose       = autoTimeWalkClose_default;
    var_sys_NVM.ligthTime               = ligthTime_default;
    var_sys_NVM.folow_me                = folow_me_default;
    var_sys_NVM.electricBrake           = electricBrake_default;  
    var_sys_NVM.autoTimeWalkClose       = autoTimeWalkClose_default;
    var_sys_NVM.Direction_motor         = Direcciont_Motor_default ;
  

    if (type == SC){ 
        
        var_sys_NVM.motorSensitivity        = motorSensitivity_default;
        var_sys_NVM.logicDigital            = logicDigital_default;
        var_sys_NVM.Stopboton               = StopButton_default;
        var_sys_NVM.autoTimeFullClose       = autoTimeFullClose_default;
        var_sys_NVM.operationMode           = operationMode_default;
        var_sys_NVM.velocityDecelaration    = velocityDecelaration_default;      
        var_sys_NVM.flashRGBMode            = flashRGBMode_default;
        var_sys_NVM.softstop                = Softstop_default;
        var_sys_NVM.softStart               = softStart_default;
        var_sys_NVM.walkTime                = walkTime_default;
        
    }
    else if (type == SE){
        var_sys_NVM.decelarationClose       = SE_decelarationClose_default;
        var_sys_NVM.decelarationOpen        = SE_decelarationOpen_default;	 
        var_sys_NVM.motorSensitivity        = SE_motorSensitivity_default;
        var_sys_NVM.logicDigital            = SE_logicDigital_default;
        var_sys_NVM.Stopboton               = SE_StopButton_default;
        var_sys_NVM.autoTimeFullClose       = SE_autoTimeFullClose_default;
        var_sys_NVM.operationMode           = SE_operationMode_default;
        var_sys_NVM.velocityDecelaration    = SE_velocityDecelaration_default;      
        var_sys_NVM.flashRGBMode            = SE_flashRGBMode_default;
        var_sys_NVM.softstop                = SE_Softstop_default;
        var_sys_NVM.softStart               = SE_softStart_default;
        var_sys_NVM.walkTime                = SE_walkTime_default;
        var_sys_NVM.Direction_motor         = 0 ; 
        
    }
    else if (type == br){
        var_sys_NVM.decelarationClose       = br_decelarationClose_default;
        var_sys_NVM.decelarationOpen        = br_decelarationOpen_default;	
        var_sys_NVM.motorSensitivity        = br_motorSensitivity_default;
        var_sys_NVM.logicDigital            = br_logicDigital_default;
        var_sys_NVM.Stopboton               = br_StopButton_default;
        var_sys_NVM.autoTimeFullClose       = br_autoTimeFullClose_default;
        var_sys_NVM.operationMode           = br_operationMode_default;
        var_sys_NVM.velocityDecelaration    = br_velocityDecelaration_default;      
        var_sys_NVM.flashRGBMode            = br_flashRGBMode_default;
        var_sys_NVM.softstop                = br_Softstop_default;
        var_sys_NVM.softStart               = br_softStart_default;
        var_sys_NVM.walkTime                = br_walkTime_default;
        
    }
   
  
    
   
   //
    SaveNVM_VarSystem(pageMemoryE);
    SaveNVM_VarSystem(pageMemoryP);

    //>>> rev1.149:
    // Clear all the NVM variables except the movement counter.
    
    var_sys_NVM.learningTimeToClose                = 0;
    var_sys_NVM.learningTimeToOpen                 = 0;
    var_sys_NVM.learningCurrentNormalClose         = 0;
    var_sys_NVM.learningCurrentNormalOpen          = 0;
    var_sys_NVM.learningCurrentDecelarationClose   = 0;
    var_sys_NVM.learningCurrentDecelarationOpen    = 0;
//>>> rev 1.157: Não apaga os comandos no reset de fábrica
//    var_sys_NVM.positionRemotesFull              = 0;
//    var_sys_NVM.positionRemotesWalk              = 0;
//    var_sys_NVM.OnlyRollingCode                  = NO;
    
    if ((FimCurso_Open_GetValue() == 0) &&  (FimCurso_Close_GetValue() == 0) &&  (PUSH_GetValue() == 0)&&(SecurityBar_GetValue()==0)){ //Condição para fazer reset ao contador de manobras
     var_sys.actualCounterMoves = 0;
     var_sys_NVM.counterMoves = 0; 
    }
     
//<<<
   // It doesn't clears the move counter.
    SaveNVM_VarSystem(pageMemoryCounters);
    SaveNVM_VarSystem(pageMemoryLearningVars);
    //<<< rev1.149:
}


//**************************************************************************************
// controla o guardar dos contadores de manorbas, evitando escritas com menos de 5 minutos de intervalo.
//**************************************************************************************
void ControlCounterMoves(void)
{
    //Trata de Guardar o numero de movimentos.
    if(ts_system.timeBetweenSaveCounters<=0)
    {
       ts_system.timeBetweenSaveCounters=TIME_1MIN*5;

       if(var_sys.actualCounterMoves!=var_sys_NVM.counterMoves)
       {
           var_sys_NVM.counterMoves=var_sys.actualCounterMoves;
           SaveNVM_VarSystem(pageMemoryCounters);
       }
    }
}


//**************************************************************************************
// Verify if the readed values are inside valid limits.
// Any parameter out of the limits, is corrected to the default value.
// If any value is corrected, the routine saves the parameters.
//**************************************************************************************
void checkNVM_VarSystem ( void )
{
    char    saveParam;
    
    
    saveParam = 0;
    
//     if ( var_sys_NVM.decelarationType>1)
//    {
//        //    var_sys_NVM.decelarationClose;        // Duration of the deceleration phase on the closing process [0..15sec].
//        var_sys_NVM.decelarationType = decelarationType_default;
//        saveParam=1;
//    }
    if ( var_sys_NVM.decelarationOpen>45 )
    {
        //    var_sys_NVM.decelarationOpen;         // Duration of the deceleration phase on the opening process [0..15sec].
        var_sys_NVM.decelarationOpen = decelarationOpen_default;
        saveParam=1;
    }
    
    if ( var_sys_NVM.decelarationClose>45 )
    {
        //    var_sys_NVM.decelarationClose;        // Duration of the deceleration phase on the closing process [0..15sec].
        var_sys_NVM.decelarationClose = decelarationClose_default;
        saveParam=1;
    }
   
    if ( (var_sys_NVM.motorPower<1) || (var_sys_NVM.motorPower>9) )
    {
        //    var_sys_NVM.motorPower;               // Motor Strength level [1..9].
        var_sys_NVM.motorPower = motorPower_default;
        saveParam=1;
    }

    if ( var_sys_NVM.motorSensitivity>9 )
    {
        //    var_sys_NVM.motorSensitivity;         // Motor current sensitivity level during full speed moving [0..9].
        var_sys_NVM.motorSensitivity = motorSensitivity_default;
        saveParam=1;
    }

    if ( var_sys_NVM.walkTime>99 )
    {
        //    var_sys_NVM.walkTime;                 // Time to open the gate for peons passing [0..99].
        var_sys_NVM.walkTime = walkTime_default;
        saveParam=1;
    }

    if ( var_sys_NVM.autoTimeFullClose>99 )
    {
        //    var_sys_NVM.autoTimeFullClose;        // Pause time after opening process that the system waits until it starts the close process automatically [0..99sec, being 0-OFF].
        var_sys_NVM.autoTimeFullClose = autoTimeFullClose_default;
        saveParam=1;
    }

    if ( var_sys_NVM.autoTimeWalkClose>99 )
    {
        //    var_sys_NVM.autoTimeWalkClose;        // Pause time after peons passage opening process that the system waits until it starts the close process automatically [0..99sec, being 0-OFF].
        var_sys_NVM.autoTimeWalkClose = autoTimeWalkClose_default;
        saveParam=1;
    }

    if ( var_sys_NVM.photoCellIsON>1 )
    {
        //    var_sys_NVM.photoCellIsON;            // Photo cell state [0-OFF, 1-ON].
        var_sys_NVM.photoCellIsON = photoCellIsON_default;
        saveParam=1;
    }

    if ( var_sys_NVM.photoCellInOpen>1 )
    {
        //    var_sys_NVM.photoCellInOpen;          // Photo cell used on the opening process [0-Not used, 1-Used].
        var_sys_NVM.photoCellInOpen = photoCellInOpen_default;
        saveParam=1;
    }

    if ( var_sys_NVM.securityBandIsON>1 )
    {
        //    var_sys_NVM.securityBandIsON;         // Security Band state [0-Not installed, 1-Installed and used].
        var_sys_NVM.securityBandIsON = securityBandIsON_default ;
        saveParam=1;
    }

    if ( var_sys_NVM.securityBandType>1 )
    {
        //    var_sys_NVM.securityBandType;         // Security Band Type [0-8K2 type, 1-NC type].
        var_sys_NVM.securityBandType = securityBandType_default;
        saveParam=1;
    }

    if ( var_sys_NVM.securityBandInOpen>1 )
    {
        //    var_sys_NVM.securityBandInOpen;       // Security Band used on the opening process [0-Not used, 1-Used].
        var_sys_NVM.securityBandInOpen = securityBandInOpen_default;
        saveParam=1;
    }

    if ( var_sys_NVM.operationMode>2 )
    {
        //    var_sys_NVM.operationMode;            // Operation mode [0-Modo automático, 1-Modo passo-a-passo, 2-Modo Condomínio].
        var_sys_NVM.operationMode = operationMode_default;
        saveParam=1;
    }

    if ( var_sys_NVM.flashLightMode>3 )
    {
        //    var_sys_NVM.flashLightMode;           // Flashlight operation mode [0-1Hz Blink opening, 0.5Hz closing and ON at autoTime????Close time; 1- ON opening and closing and OFF at autoTime????Close time; 2- ON opening, closing, at autoTime????Close time and ligthTime minutes after closing].
        var_sys_NVM.flashLightMode = flashLightMode_default;
        saveParam=1;
    }

    if ( var_sys_NVM.programmingDistance>1 )
    {
        //    var_sys_NVM.programmingDistance;      // Distance programming enable [0-Disabled, 1-Enabled].
        var_sys_NVM.programmingDistance = programmingDistance_default;
        saveParam=1;
    }

    if ( var_sys_NVM.decelarationSensivity>9 )
    {
        //    var_sys_NVM.decelarationSensivity;    // Motor current sensitivity level during deceleration moving phase [0..9].
        var_sys_NVM.decelarationSensivity = decelarationSensivity_default;
        saveParam=1;
    }
    //<<< page0

    //>>> page1
    if ( var_sys_NVM.homemPresente>2 )
    {
        //    var_sys_NVM.homemPresente;            // Indicates if the gate is controlled only manually by a person [0-Controlled normally, 1-Controlled only by hand on the buttons].
        var_sys_NVM.homemPresente = homemPresente_default;
        saveParam=1;
    }

    if ( var_sys_NVM.logicDigital>1 )
    {
        //    var_sys_NVM.logicDigital;             // Defines the buttons functioning logic [0- Button 1 is full open and close, Button 2 is peons open and close; 1- Button 1 is full open and Button 2 is full close].
        var_sys_NVM.logicDigital = logicDigital_default;
        saveParam=1;
    }

    if ( var_sys_NVM.softStart>9 )
    {
        //    var_sys_NVM.softStart;                // Soft start enable state [0-Disabled, 1-Enabled].
        var_sys_NVM.softStart = softStart_default;
        saveParam=1;
    }
   

    if ( var_sys_NVM.ligthTime>99 )
    {
        //    var_sys_NVM.ligthTime;                // Time for the flashlight ON after closing the gate (implies flashLightMode=2) [0..99 minutes].
        var_sys_NVM.ligthTime = ligthTime_default;
        saveParam=1;
    }

    if ( var_sys_NVM.folow_me>9 )
    {
        //    var_sys_NVM.folow_me;                 // Indicates if the follow me mode is active. When active, the gate initiates the close process after a passage trough the photocell.[0-Disabled, 1-Enabled]
        var_sys_NVM.folow_me = folow_me_default;
        saveParam=1;
    }



    if ( var_sys_NVM.electricBrake>1 )
    {
        //    var_sys_NVM.electricBrake;            // Electric brake state [0-Disabled, 1-Enabled].
        var_sys_NVM.electricBrake = electricBrake_default;
        saveParam=1;
    }

    if ( (var_sys_NVM.velocityDecelaration<1) || (var_sys_NVM.velocityDecelaration>9) )
    {
        //    var_sys_NVM.velocityDecelaration;     // Velocity to decelerate the gate in levels [1..9].
        var_sys_NVM.velocityDecelaration = velocityDecelaration_default;
        saveParam=1;
    }

    if ( var_sys_NVM.flashRGBMode>3 )
    {
        //    var_sys_NVM.flashRGBMode;             // Indicates the RGB flashlight functioning mode [0-Continuous mode, 1-0.5Hz Blinking mode].
        var_sys_NVM.flashRGBMode = flashRGBMode_default;
        saveParam=1;
    }
        if ( var_sys_NVM.Stopboton > 1 )
    {
        //    var_sys_NVM.flashRGBMode;             // Indicates the RGB flashlight functioning mode [0-Continuous mode, 1-0.5Hz Blinking mode].
        var_sys_NVM.Stopboton = StopButton_default ;
        saveParam=1;
    }
        if ( var_sys_NVM.Direction_motor>1 )
    {
        //    var_sys_NVM.flashRGBMode;             // Indicates the RGB flashlight functioning mode [0-Continuous mode, 1-0.5Hz Blinking mode].
        var_sys_NVM.Direction_motor = Direcciont_Motor_default;
        saveParam=1;
    }
        if ( var_sys_NVM.softstop>9 )
    {
        //    var_sys_NVM.flashRGBMode;             // Indicates the RGB flashlight functioning mode [0-Continuous mode, 1-0.5Hz Blinking mode].
        var_sys_NVM.softstop = Softstop_default;
        saveParam=1;
    }

    //unsigned char selectedMotor;          // Not used.

    //<<< page1
    
    
    //>>> page2
//    var_sys_NVM.positionRemotesFull;
//    var_sys_NVM.positionRemotesWalk;
//    var_sys_NVM.counterMoves;
//    var_sys_NVM.OnlyRollingCode;
//    var_sys_NVM.learningCurrentDecelarationClose;
//    var_sys_NVM.learningCurrentDecelarationOpen;
    //<<< page2


    //>>> page3
//    var_sys_NVM.learningCurrentNormalClose;
//    var_sys_NVM.learningCurrentNormalOpen;
//    var_sys_NVM.learningTimeToOpen;
//    var_sys_NVM.learningTimeToClose;
    //<<< page3

    if ( saveParam != 0 )
    {
        SaveNVM_VarSystem(pageMemoryP);
        SaveNVM_VarSystem(pageMemoryE);
    }
}
