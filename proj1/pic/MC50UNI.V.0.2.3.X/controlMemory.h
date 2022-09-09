/* 
 * File:   controlMemory.h
 * Author: cpereira
 *
 * Created on 18 de Setembro de 2014, 16:26
 */

#ifndef CONTROLMEMORY_H
#define	CONTROLMEMORY_H

#include "inputs.h"
#include "main.h"


#ifdef	__cplusplus
extern "C" {
#endif

#define MEMORY_ADDRESS                  0x50
#define MEMORY_RETRY_MAX                100
#define PAGE_SIZE   16
#define CMD_SIZE    4
#define Wbit        0
#define Rbit        1
#define MASTER_I2C_GENERIC_RETRY_MAX    1000
#define _24LC16B_ADDRESS                 0xA0 // slave device address

#define STARTADD_FULL                   0x0200
#define STARTADD_WALK                   0x0500

#define	decelarationOpen_default	    3
#define	decelarationClose_default	    3
#define	decelarationType_default	    0
#define	motorPower_default              9
#define	motorSensitivity_default	    0
#define decelarationSensivity_default   0
#define	walkTime_default                10
#define	autoTimeFullClose_default       0
#define	autoTimeWalkClose_default       0
#define	photoCellIsON_default           0
#define	photoCellInOpen_default         0
#define	securityBandIsON_default        0
#define	securityBandType_default        1
#define	securityBandInOpen_default      0
#define	operationMode_default           0
#define	flashLightMode_default          0
#define	programmingDistance_default     0
#define	homemPresente_default           0
#define	logicDigital_default            0
#define	softStart_default               0
#define	ligthTime_default               3
#define	folow_me_default                0
#define	encoder_default                 0
#define	electricBrake_default           0
#define	velocityDecelaration_default	5
#define	flashRGBMode_default            3
#define	Softstop_default                0    
#define	StopButton_default              0
#define	Direcciont_Motor_default        1  

#define sizeMemory                      24
    
//________________________Barreira__________________________________________
    
#define	br_decelarationOpen_default	       2
#define	br_decelarationClose_default	   6    
#define	br_motorSensitivity_default        0    
#define	br_logicDigital_default            0     
#define	br_autoTimeFullClose_default       0
#define	br_operationMode_default           2
#define	br_velocityDecelaration_default	   5
#define	br_flashRGBMode_default            1
#define	br_Softstop_default                5
#define	br_StopButton_default              0 
#define br_walkTime_default                0
#define br_softStart_default               0    
//________________________Seccionada________________________________________
        
 
#define	SE_decelarationOpen_default	       4
#define	SE_decelarationClose_default	   4     
#define	SE_motorSensitivity_default        4
#define	SE_logicDigital_default            1  
#define	SE_StopButton_default              1  
#define	SE_autoTimeFullClose_default       0
#define	SE_operationMode_default           0
#define	SE_velocityDecelaration_default	   5
#define	SE_flashRGBMode_default            3
#define	SE_Softstop_default                0
#define SE_walkTime_default                0  
#define SE_softStart_default               5
 
    



typedef enum {
        pageMemoryP,
        pageMemoryE,
        pageMemoryCounters,
        pageMemoryLearningVars,
}pageMemory;

typedef enum {
    SC,
    SE,
    br,
}typemotor;

TypeCMD validateRemoteSerialNumber(unsigned long serial, StateEnum VerifyOnlySerial, char* position);
void saveNewSerial(char cmdType,unsigned long tempSerial, char position);
void RemoveSerial(char cmdType, char position);
void ReadSerial(char cmdType, unsigned long* tempSerial, char position);
char cmdMemoryIsEmpty(char cmdType, char position);
void SaveNVM_VarSystem(unsigned char page);
void ResetDefaultMemory(unsigned char type);
void loadNVM_VarSystem(void);
void ControlCounterMoves(void);

#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLMEMORY_H */

