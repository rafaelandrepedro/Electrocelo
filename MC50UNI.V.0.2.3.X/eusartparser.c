/* 
 * File:   eusartparser.c
 * Author: rafael pedro
 *
 * Created on July 14, 2022, 12:18 AM
 */

#include "eusartparser.h"
#include "sm_common.h"
#include "sm_Main.h"

    void read_eusartparser(struct package_t* package){
        switch(package->address){
            case 0x00:
            case 0x10:
                package->data.data8[1]=var_sys_NVM.decelarationClose;
                package->data.data8[0]=var_sys_NVM.decelarationOpen;
                write_package(*package);
                break;
            case 0x11:
                package->data.data8[1]=var_sys_NVM.motorSensitivity;
                package->data.data8[0]=var_sys_NVM.motorPower;
                write_package(*package);
                break;
            case 0x12:
                package->data.data8[1]=var_sys_NVM.walkTime;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x02:
            case 0x13:
                package->data.data8[1]=var_sys_NVM.autoTimeWalkClose;
                package->data.data8[0]=var_sys_NVM.autoTimeFullClose;
                write_package(*package);
                break;
            case 0x05:
            case 0x14:
                package->data.data8[1]=var_sys_NVM.photoCellInOpen;
                package->data.data8[0]=var_sys_NVM.photoCellIsON;
                write_package(*package);
                break;
            case 0x15:
                package->data.data8[1]=var_sys_NVM.securityBandType;
                package->data.data8[0]=var_sys_NVM.securityBandIsON;
                write_package(*package);
                break;
            case 0x16:
                package->data.data8[1]=var_sys_NVM.securityBandInOpen;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x17:
                package->data.data8[1]=var_sys_NVM.operationMode;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x18:
                package->data.data8[1]=var_sys_NVM.flashLightMode;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x19:
                package->data.data8[1]=var_sys_NVM.programmingDistance;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x1A:
                package->data.data8[1]=var_sys_NVM.decelarationSensivity;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
                
            case 0x1B:
                package->data.data8[1]=var_sys_NVM.homemPresente;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x07:
            case 0x1C:
                package->data.data8[1]=var_sys_NVM.logicDigital;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x1D:
                package->data.data8[1]=var_sys_NVM.softstop;
                package->data.data8[0]=var_sys_NVM.softStart;
                write_package(*package);
                break;
            case 0x03:
            case 0x1E:
                package->data.data8[1]=var_sys_NVM.ligthTime;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x0A:
            case 0x1F:
                package->data.data8[1]=var_sys_NVM.folow_me;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x20:
                package->data.data8[1]=var_sys_NVM.Stopboton;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x21:
                package->data.data8[1]=var_sys_NVM.electricBrake;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x22:
                package->data.data8[1]=var_sys_NVM.velocityDecelaration;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x08:
            case 0x23:
                package->data.data8[1]=var_sys_NVM.flashRGBMode;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x24:
                package->data.data8[1]=var_sys_NVM.Direction_motor;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x25:
                package->data.data8[1]=var_sys_NVM.TypeofMotor;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x26:
                package->data.data8[1]=var_sys_NVM.positionRemotesWalk;
                package->data.data8[0]=var_sys_NVM.positionRemotesFull;
                write_package(*package);
                break;
            case 0x27:
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.counterMoves))+1);
                write_package(*package);
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.counterMoves))+0);
                write_package(*package);
                break;
            case 0x29:
                package->data.data8[1]=var_sys_NVM.OnlyRollingCode;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x2A:
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningCurrentDecelarationClose))+1);
                write_package(*package);
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningCurrentDecelarationClose))+0);
                write_package(*package);
                break;
            case 0x2C:
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningCurrentDecelarationOpen))+1);
                write_package(*package);
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningCurrentDecelarationOpen))+0);
                write_package(*package);
                break;
            case 0x2E:
                package->data.data16=var_sys_NVM.learningCurrentNormalClose;
                write_package(*package);
                break;
            case 0x2F:
                package->data.data16=var_sys_NVM.learningCurrentNormalOpen;
                write_package(*package);
                break;
            case 0x30:
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningTimeToOpen))+1);
                write_package(*package);
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningTimeToOpen))+0);
                write_package(*package);
                break;
            case 0x32:
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningTimeToClose))+1);
                write_package(*package);
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningTimeToClose))+0);
                write_package(*package);
                break;
                
                //read only
                
            case 0x34:
                package->data.data8[1]=RFFull;
                package->data.data8[0]=0x00;
                break;
                
                
            default:
                //address not avaliable
                break;
        }      
    }
    
    void write_eusartparser(struct package_t package){
        volatile int debug=(uint8_t)package.address;
        volatile int debug2=0x10;
        switch((uint8_t)package.address){
            case 0x00:
            case 0x10:
                var_sys_NVM.decelarationOpen=package.data.data8[0];
                var_sys_NVM.decelarationClose=package.data.data8[1];
                break;
            case 0x11:
                var_sys_NVM.motorPower=package.data.data8[0];
                var_sys_NVM.motorSensitivity=package.data.data8[1];
                break;
            case 0x12:
                var_sys_NVM.walkTime=package.data.data8[1];
                break;
            case 0x02:
            case 0x13:
                var_sys_NVM.autoTimeFullClose=package.data.data8[0];
                var_sys_NVM.autoTimeWalkClose=package.data.data8[1];
                break;
            case 0x05:
            case 0x14:
                var_sys_NVM.photoCellIsON=package.data.data8[0];
                var_sys_NVM.photoCellInOpen=package.data.data8[1];
                break;
            case 0x15:
                var_sys_NVM.securityBandIsON=package.data.data8[0];
                var_sys_NVM.securityBandType=package.data.data8[1];
                break;
            case 0x16:
                var_sys_NVM.securityBandInOpen=package.data.data8[1];
                break;
            case 0x17:
                var_sys_NVM.operationMode=package.data.data8[1];
                break;
            case 0x18:
                var_sys_NVM.flashLightMode=package.data.data8[1];
                break;
            case 0x19:
                var_sys_NVM.programmingDistance=package.data.data8[1];
                break;
            case 0x1A:
                var_sys_NVM.decelarationSensivity=package.data.data8[1];
                break;
                
            case 0x1B:
                var_sys_NVM.homemPresente=package.data.data8[1];
                break;
            case 0x07:
            case 0x1C:
                var_sys_NVM.logicDigital=package.data.data8[1];
                break;
            case 0x1D:
                var_sys_NVM.softStart=package.data.data8[0];
                var_sys_NVM.softstop=package.data.data8[1];
                break;
            case 0x03:
            case 0x1E:
                var_sys_NVM.ligthTime=package.data.data8[1];
                break;
            case 0x0A:
            case 0x1F:
                var_sys_NVM.folow_me=package.data.data8[1];
                break;
            case 0x20:
                var_sys_NVM.Stopboton=package.data.data8[1];
                break;
            case 0x21:
                var_sys_NVM.electricBrake=package.data.data8[1];
                break;
            case 0x22:
                var_sys_NVM.velocityDecelaration=package.data.data8[1];
                break;
            case 0x08:
            case 0x23:
                var_sys_NVM.flashRGBMode=package.data.data8[1];
                break;
            case 0x24:
                var_sys_NVM.Direction_motor=package.data.data8[1];
                break;
            case 0x25:
                var_sys_NVM.TypeofMotor=package.data.data8[1];
                break;
            case 0x26:
                var_sys_NVM.positionRemotesFull=package.data.data8[0];
                var_sys_NVM.positionRemotesWalk=package.data.data8[1];
                break;
                
            case 0x27:
                var_sys_NVM.counterMoves=var_sys_NVM.counterMoves|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                var_sys_NVM.counterMoves=var_sys_NVM.counterMoves&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                break;
            case 0x28:
                var_sys_NVM.counterMoves=var_sys_NVM.counterMoves|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                var_sys_NVM.counterMoves=var_sys_NVM.counterMoves&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                break;
            
            case 0x29:
                var_sys_NVM.OnlyRollingCode=package.data.data8[1];
                break;
                
            case 0x2A:
                var_sys_NVM.learningCurrentDecelarationClose=var_sys_NVM.learningCurrentDecelarationClose|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                var_sys_NVM.learningCurrentDecelarationClose=var_sys_NVM.learningCurrentDecelarationClose&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                break;
            case 0x2B:
                var_sys_NVM.learningCurrentDecelarationClose=var_sys_NVM.learningCurrentDecelarationClose|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                var_sys_NVM.learningCurrentDecelarationClose=var_sys_NVM.learningCurrentDecelarationClose&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                break;
                
            case 0x2C:
                var_sys_NVM.learningCurrentDecelarationOpen=var_sys_NVM.learningCurrentDecelarationOpen|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                var_sys_NVM.learningCurrentDecelarationOpen=var_sys_NVM.learningCurrentDecelarationOpen&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                break;
            case 0x2D:
                var_sys_NVM.learningCurrentDecelarationOpen=var_sys_NVM.learningCurrentDecelarationOpen|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                var_sys_NVM.learningCurrentDecelarationOpen=var_sys_NVM.learningCurrentDecelarationOpen&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                break;
                
            case 0x2E:
                var_sys_NVM.learningCurrentNormalClose=package.data.data16;
                break;
                
            case 0x2F:
                var_sys_NVM.learningCurrentNormalOpen=package.data.data16;
                break;
                
            case 0x30:
                var_sys_NVM.learningTimeToOpen=var_sys_NVM.learningTimeToOpen|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                var_sys_NVM.learningTimeToOpen=var_sys_NVM.learningTimeToOpen&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                break;
            case 0x31:
                var_sys_NVM.learningTimeToOpen=var_sys_NVM.learningTimeToOpen|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                var_sys_NVM.learningTimeToOpen=var_sys_NVM.learningTimeToOpen&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                break;
                
            case 0x32:
                var_sys_NVM.learningTimeToClose=var_sys_NVM.learningTimeToClose|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                var_sys_NVM.learningTimeToClose=var_sys_NVM.learningTimeToClose&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                break;
            case 0x33:
                var_sys_NVM.learningTimeToClose=var_sys_NVM.learningTimeToClose|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                var_sys_NVM.learningTimeToClose=var_sys_NVM.learningTimeToClose&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                break;

            default:
                //address not avaliable
                break;
        }      
    }
    
    void confirmpackage(struct package_t* package, bool confirm){
        init_package(package);
        package->functioncode=0x03;
        package->address=0x00;
        if(confirm==TRUE)
            package->data.data16=0x0001;
        else
            package->data.data16=0x0000;
    }
    
    void eusartparser(struct package_t* package){
        struct package_t a;
        uint8_t relcounter;
        static bool save_f=FALSE;
        static uint16_t buffer=0x0000;
        uint32_t serial;
        char pos;
        
        switch(package->functioncode){
            case READ://READ
                read_eusartparser(package);
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
                
            case WRITE://WRITE
                if(programmer_enable){
                    write_eusartparser(*package);
                    confirmpackage(package, TRUE);
                    write_package(*package);
                }
                else{
                    confirmpackage(package, FALSE);
                    write_package(*package);
                }
                break;
                
            case PROGRAMMING_ENABLE://PROGRAMMING_ENABLE
                if(programmer_enable){
                    SaveNVM_VarSystem(pageMemoryE);
                    SaveNVM_VarSystem(pageMemoryP);
                    programmer_enable=0;
                }
                else{
                    if((sm_state_Main_t)main_stateMachine.current_state==st_standBy)
                        programmer_enable=1;
                    else{
                        package->data.data16=(uint16_t)2;
                        write_package(*package);
                        confirmpackage(package, TRUE);
                        write_package(*package);
                        break;
                    }
                }
                
                package->data.data16=(uint16_t)programmer_enable;
                write_package(*package);
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
            case CONFIRM://CONFIRM
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
            case NUM_COMMANDS_F://NUM_COMMANDS_F
                    package->address=0x00;
                    package->data.data16=var_sys_NVM.positionRemotesFull;
                    for(uint8_t i=0;i<var_sys_NVM.positionRemotesFull;i++)
                    if(cmdMemoryIsEmpty(0,i)==TRUE)
                        package->data.data16--;
                    write_package(*package);
                    confirmpackage(package, TRUE);
                    write_package(*package);
                break;
            case NUM_EMPTY_COMMANDS_F://NUM_EMPTY_COMMANDS_F
                
                package->address=0x00;
                package->data.data16=0;
                for(uint8_t i=0;i<var_sys_NVM.positionRemotesFull;i++)
                if(cmdMemoryIsEmpty(0,i)==TRUE)
                    package->data.data16++;
                write_package(*package);
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
            case OCCUPIED_POS_F://OCCUPIED_POS_F
                relcounter=0;
                for(uint8_t i=0;i<var_sys_NVM.positionRemotesFull;i++)
                    if(cmdMemoryIsEmpty(0,i)==FALSE){
                        package->data.data16=(uint16_t)i;
                        package->address=relcounter;
                        relcounter++;
                        write_package(*package);
                    }
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
            case EMPTY_POS_F://EMPTY_POS_F
                relcounter=0;
                for(uint8_t i=0;i<var_sys_NVM.positionRemotesFull;i++)
                    if(cmdMemoryIsEmpty(0,i)==TRUE){
                        package->data.data16=(uint16_t)i;
                        package->address=relcounter;
                        relcounter++;
                        write_package(*package);
                    }
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
            case SAVE_COMMAND_F://SAVE_COMMAND_F
                if(programmer_enable){
                    if(save_f==FALSE){
                        buffer=package->data.data16;
                        confirmpackage(package, TRUE);
                        write_package(*package);
                        save_f=TRUE;
                    }
                    else{
                        serial=((uint32_t)buffer<<16)+(uint32_t)package->data.data16;
                        if(validateRemoteSerialNumber(serial, NO, &pos)==NoCMD){
                            for(uint8_t i=0;;i++)
                                if(cmdMemoryIsEmpty(0,i)==TRUE&&package->address==0){
                                    saveNewSerial(0,serial,i);
                                    confirmpackage(package, TRUE);
                                    write_package(*package);
                                    break;
                                }
                                else if(cmdMemoryIsEmpty(0,i)==TRUE){
                                    package->address--;
                                }
                                else if(i==var_sys_NVM.positionRemotesFull){
                                    confirmpackage(package, FALSE);
                                    write_package(*package);
                                    break;
                                }
                        }
                        else{
                            confirmpackage(package, FALSE);
                            write_package(*package);
                        }
                        save_f=FALSE;
                    }
                }
                else{
                    confirmpackage(package, FALSE);
                    write_package(*package);
                }
                break;
            case ERASE_COMMAND_F://ERASE_COMMAND_F
                if(programmer_enable){
                    for(uint8_t i=0;;i++)
                        if(cmdMemoryIsEmpty(0,i)==FALSE&&package->address==0){
                            RemoveSerial(0, i);
                            confirmpackage(package, TRUE);
                            write_package(*package);
                            save_f=FALSE;
                            break;
                        }
                        else if(cmdMemoryIsEmpty(0,i)==FALSE){
                            package->address--;
                        }
                        else if(i==var_sys_NVM.positionRemotesFull){
                            confirmpackage(package, FALSE);
                            write_package(*package);
                            save_f=FALSE;
                            break;
                        }
                }
                else{
                    confirmpackage(package, FALSE);
                    write_package(*package);
                }
                break;
            case READ_SERIAL_F://READ_SERIAL_F   
                for(uint8_t i=0;;i++)
                    if(cmdMemoryIsEmpty(0,i)==FALSE&&package->address==0){
                        ReadSerial(0, &serial, i);
                        package->data.data16=(uint16_t)serial;
                        write_package(*package);
                        package->data.data16=(uint16_t)(serial>>16);
                        write_package(*package);
                        confirmpackage(package, TRUE);
                        write_package(*package);
                        break;
                    }
                    else if(cmdMemoryIsEmpty(0,i)==FALSE){
                        package->address--;
                    }
                    else if(i==var_sys_NVM.positionRemotesFull){
                        confirmpackage(package, FALSE);
                        write_package(*package);
                        break;
                    }
                break;
            case NUM_COMMANDS_W://NUM_COMMANDS_W
                    package->address=0x00;
                    package->data.data16=var_sys_NVM.positionRemotesWalk;
                    for(uint8_t i=0;i<var_sys_NVM.positionRemotesWalk;i++)
                    if(cmdMemoryIsEmpty(1,i)==TRUE)
                        package->data.data16--;
                    write_package(*package);
                    confirmpackage(package, TRUE);
                    write_package(*package);
                break;
            case NUM_EMPTY_COMMANDS_W://NUM_EMPTY_COMMANDS_W
                
                package->address=0x00;
                package->data.data16=0;
                for(uint8_t i=0;i<var_sys_NVM.positionRemotesWalk;i++)
                if(cmdMemoryIsEmpty(1,i)==TRUE)
                    package->data.data16++;
                write_package(*package);
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
            case OCCUPIED_POS_W://OCCUPIED_POS_W
                relcounter=0;
                for(uint8_t i=0;i<var_sys_NVM.positionRemotesWalk;i++)
                    if(cmdMemoryIsEmpty(1,i)==FALSE){
                        package->data.data16=(uint16_t)i;
                        package->address=relcounter;
                        relcounter++;
                        write_package(*package);
                    }
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
            case EMPTY_POS_W://EMPTY_POS_W
                relcounter=0;
                for(uint8_t i=0;i<var_sys_NVM.positionRemotesWalk;i++)
                    if(cmdMemoryIsEmpty(1,i)==TRUE){
                        package->data.data16=(uint16_t)i;
                        package->address=relcounter;
                        relcounter++;
                        write_package(*package);
                    }
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
            case SAVE_COMMAND_W://SAVE_COMMAND_W
                if(programmer_enable){
                    if(save_f==FALSE){
                        buffer=package->data.data16;
                        confirmpackage(package, TRUE);
                        write_package(*package);
                        save_f=TRUE;
                    }
                    else{
                        serial=((uint32_t)buffer<<16)+(uint32_t)package->data.data16;
                        if(validateRemoteSerialNumber(serial, NO, &pos)==NoCMD){
                            for(uint8_t i=0;;i++)
                                if(cmdMemoryIsEmpty(1,i)==TRUE&&package->address==0){
                                    saveNewSerial(1,serial,i);
                                    confirmpackage(package, TRUE);
                                    write_package(*package);
                                    break;
                                }
                                else if(cmdMemoryIsEmpty(1,i)==TRUE){
                                    package->address--;
                                }
                                else if(i==var_sys_NVM.positionRemotesWalk){
                                    confirmpackage(package, FALSE);
                                    write_package(*package);
                                    break;
                                }
                        }
                        else{
                            confirmpackage(package, FALSE);
                            write_package(*package);
                        }
                        save_f=FALSE;
                    }
                }
                else{
                    confirmpackage(package, FALSE);
                    write_package(*package);
                }
                break;
            case ERASE_COMMAND_W://ERASE_COMMAND_W
                if(programmer_enable){
                    for(uint8_t i=0;;i++)
                        if(cmdMemoryIsEmpty(1,i)==FALSE&&package->address==0){
                            RemoveSerial(1, i);
                            confirmpackage(package, TRUE);
                            write_package(*package);
                            save_f=FALSE;
                            break;
                        }
                        else if(cmdMemoryIsEmpty(1,i)==FALSE){
                            package->address--;
                        }
                        else if(i==var_sys_NVM.positionRemotesWalk){
                            confirmpackage(package, FALSE);
                            write_package(*package);
                            save_f=FALSE;
                            break;
                        }
                }
                else{
                    confirmpackage(package, FALSE);
                    write_package(*package);
                }
                break;
            case READ_SERIAL_W://READ_SERIAL_W   
                for(uint8_t i=0;;i++)
                    if(cmdMemoryIsEmpty(1,i)==FALSE&&package->address==0){
                        ReadSerial(1, &serial, i);
                        package->data.data16=(uint16_t)serial;
                        write_package(*package);
                        package->data.data16=(uint16_t)(serial>>16);
                        write_package(*package);
                        confirmpackage(package, TRUE);
                        write_package(*package);
                        break;
                    }
                    else if(cmdMemoryIsEmpty(1,i)==FALSE){
                        package->address--;
                    }
                    else if(i==var_sys_NVM.positionRemotesWalk){
                        confirmpackage(package, FALSE);
                        write_package(*package);
                        break;
                    }
                break;
                
            default:
                confirmpackage(package, FALSE);
                write_package(*package);
        }       
    }
