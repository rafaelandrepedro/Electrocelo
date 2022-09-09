/* 
 * File:   eusartparser.h
 * Author: rafael pedro
 *
 * Created on July 14, 2022, 11:16 AM
 */

#ifndef EUSARTPARSER_H
#define	EUSARTPARSER_H

#include "eusartpackage.h"
#include "controlMemory.h"
#include "sm_common.h"
#include "sm_Main.h"
#include "main.h"
#include "inputs.h"


#ifdef	__cplusplus
extern "C" {
#endif
    
#define MC50UNI_V_0_2_3_X
//#define MC52_V_1_3_0
    
extern volatile varSystem_NVM var_sys_NVM;
extern volatile char RFFull;
extern volatile varSystem var_sys;

bool programmer_enable=0;

enum VarSize{
    B8=0,
    B16,   
    B32
};

struct Parameter{
    void* address;
    uint8_t byte;
    uint8_t key;
    enum VarSize size;
};

#ifdef MC50UNI_V_0_2_3_X

struct Parameter systemVarAddresses[]={
    {&var_sys_NVM.decelarationOpen, 1, 0x10, B8},
    {&var_sys_NVM.decelarationClose, 0, 0x10, B8},
    {&var_sys_NVM.motorPower, 1, 0x11, B8},
    {&var_sys_NVM.motorSensitivity, 0, 0x11, B8},
    {&var_sys_NVM.walkTime, 0, 0x12, B8},
    {&var_sys_NVM.autoTimeFullClose, 1, 0x13, B8},
    {&var_sys_NVM.autoTimeWalkClose, 0, 0x13, B8},
    {&var_sys_NVM.photoCellIsON, 1, 0x14, B8},
    {&var_sys_NVM.photoCellInOpen, 0, 0x14, B8},
    {&var_sys_NVM.securityBandIsON, 1, 0x15, B8},
    {&var_sys_NVM.securityBandType, 0, 0x15, B8},
    {&var_sys_NVM.securityBandInOpen, 0, 0x16, B8},
    {&var_sys_NVM.operationMode, 0, 0x17, B8},
    {&var_sys_NVM.flashLightMode, 0, 0x18, B8},
    {&var_sys_NVM.programmingDistance, 0, 0x19, B8},
    {&var_sys_NVM.decelarationSensivity, 0, 0x1A, B8},
    
    {&var_sys_NVM.homemPresente, 0, 0x1B, B8},
    {&var_sys_NVM.logicDigital, 0, 0x1C, B8},
    {&var_sys_NVM.softStart, 1, 0x1D, B8},
    {&var_sys_NVM.softstop, 0, 0x1D, B8},
    {&var_sys_NVM.ligthTime, 0, 0x1E, B8},
    {&var_sys_NVM.folow_me, 0, 0x1F, B8},
    {&var_sys_NVM.Stopboton, 0, 0x20, B8},
    {&var_sys_NVM.electricBrake, 0, 0x21, B8},
    {&var_sys_NVM.velocityDecelaration, 0, 0x22, B8},
    {&var_sys_NVM.flashRGBMode, 0, 0x23, B8},
    {&var_sys_NVM.Direction_motor, 0, 0x24, B8},
    {&var_sys_NVM.TypeofMotor, 0, 0x25, B8},
    
    {&var_sys_NVM.positionRemotesFull, 1, 0x26, B8},
    {&var_sys_NVM.positionRemotesWalk, 0, 0x26, B8},
    {&var_sys_NVM.counterMoves, 0, 0x27, B32},
    {&var_sys_NVM.OnlyRollingCode, 0, 0x29, B8},
    {&var_sys_NVM.learningCurrentDecelarationClose, 0, 0x2A, B32},
    {&var_sys_NVM.learningCurrentDecelarationOpen, 0, 0x2C, B32},
    
    {&var_sys_NVM.learningCurrentNormalClose, 0, 0x2E, B16},
    {&var_sys_NVM.learningCurrentNormalOpen, 0, 0x2F, B16},
    {&var_sys_NVM.learningTimeToOpen, 0, 0x30, B32},
    {&var_sys_NVM.learningTimeToClose, 0, 0x32, B32},
    
    {&RFFull, 0, 0x34, B8},
    
    {&var_sys.photoCellIsObstructed, 1, 0x35, B8},
    {&var_sys.SecurityBarIsObstructed, 0, 0x35, B8},
    {&var_sys.FimCurso_CloseIsEnabled, 1, 0x36, B8},
    {&var_sys.FimCurso_OpenIsEnabled, 0, 0x36, B8},
    {&var_sys.Statedoorcontrol, 0, 0x37, B8},
    {&var_sys.PositionActual, 0, 0x38, B32},
    {&var_sys.PositionIsLost, 1, 0x3A, B8},
    {&var_sys.StateVersion, 0, 0x3A, B8},
};

#endif

#ifdef MC52_V_1_3_0

struct Parameter systemVarAddresses[]={
    {&var_sys_NVM.motorPower, 1, 0x11, B8},
    {&var_sys_NVM.walkTime, 0, 0x12, B8},
    {&var_sys_NVM.autoTimeFullClose, 1, 0x13, B8},
    {&var_sys_NVM.autoTimeWalkClose, 0, 0x13, B8},
    {&var_sys_NVM.photoCellIsON, 1, 0x14, B8},
    {&var_sys_NVM.photoCellInOpen, 0, 0x14, B8},
    {&var_sys_NVM.securityBandIsON, 1, 0x15, B8},
    {&var_sys_NVM.securityBandType, 0, 0x15, B8},
    {&var_sys_NVM.securityBandInOpen, 0, 0x16, B8},
    {&var_sys_NVM.operationMode, 0, 0x17, B8},
    {&var_sys_NVM.flashLightMode, 0, 0x18, B8},
    {&var_sys_NVM.programmingDistance, 0, 0x19, B8},

    {&var_sys_NVM.homemPresente, 0, 0x1B, B8},
    {&var_sys_NVM.logicDigital, 0, 0x1C, B8},
    {&var_sys_NVM.softStart, 1, 0x1D, B8},
    {&var_sys_NVM.ligthTime, 0, 0x1E, B8},
    {&var_sys_NVM.folow_me, 0, 0x1F, B8},
    {&var_sys_NVM.electricBrake, 0, 0x21, B8},
    {&var_sys_NVM.velocityDecelaration, 0, 0x22, B8},
    {&var_sys_NVM.flashRGBMode, 0, 0x23, B8},



    {&var_sys_NVM.positionRemotesFull, 1, 0x26, B8},
    {&var_sys_NVM.positionRemotesWalk, 0, 0x26, B8},
    {&var_sys_NVM.counterMoves, 0, 0x27, B32},
    {&var_sys_NVM.OnlyRollingCode, 0, 0x29, B8},

    {&var_sys_NVM.gateDelay, 1, 0x3B, B8},
    {&var_sys_NVM.photoCellType, 0, 0x3B, B8},
    {&var_sys_NVM.gateDelayOpen, 1, 0x3C, B8},
    {&var_sys_NVM.gateNum, 0, 0x3C, B8},

    {&var_sys_NVM.electricLock, 1, 0x3D, B8},
    {&var_sys_NVM.pushInOpen, 0, 0x3D, B8},
    {&var_sys_NVM.pushInClose, 1, 0x3E, B8},
    {&var_sys_NVM.schemeDeceleration, 0, 0x3E, B8},

    {&var_sys_NVM.gate1_time_fullpower_in_open, 0, 0x3F, B16},
    {&var_sys_NVM.gate2_time_fullpower_in_open, 0, 0x40, B16},
    {&var_sys_NVM.gate1_time_fullpower_in_close, 0, 0x41, B16},
    {&var_sys_NVM.gate2_time_fullpower_in_close, 0, 0x42, B16},
    {&var_sys_NVM.gate1_time_softpower_in_open, 0, 0x43, B16},
    {&var_sys_NVM.gate2_time_softpower_in_open, 0, 0x44, B16},
    {&var_sys_NVM.gate1_time_softpower_in_close, 0, 0x45, B16},
    {&var_sys_NVM.gate2_time_softpower_in_close, 0, 0x46, B16},
};

#endif

/*
 * @brief writes to the uart a reading reply from a packed command
 * @param package reading command package
 * @return 1 if successful
 */
bool read_eusartparser(struct package_t* package);

/*
 * @brief writes to the memory with data from the uart from a packed command
 * @param package write command package
 */
void write_eusartparser(struct package_t package);

/*
 * @brief builds a confirmation package
 * @param package package built
 * @param confirm confirmation state
 */
void confirmpackage(struct package_t* package, bool confirm);

/*
 * @brief parser for a package that automaticly identifies the request and replies
 * @param package to be parsed
 */
void eusartparser(struct package_t* package);

/*
 * @brief sends all the variables through the uart
 */
void updateChangesToUart(void);

#ifdef	__cplusplus
}
#endif

#endif	/* EUSARTPARSER_H */

