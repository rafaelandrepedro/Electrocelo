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
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.decelarationClose;
                package->data.data8[0]=var_sys_NVM.decelarationOpen;
                write_package(*package);
                break;
            case 0x11:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.motorSensitivity;
                package->data.data8[0]=var_sys_NVM.motorPower;
                write_package(*package);
                break;
            case 0x12:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.walkTime;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x02:
            case 0x13:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.autoTimeWalkClose;
                package->data.data8[0]=var_sys_NVM.autoTimeFullClose;
                write_package(*package);
                break;
            case 0x05:
            case 0x14:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.photoCellInOpen;
                package->data.data8[0]=var_sys_NVM.photoCellIsON;
                write_package(*package);
                break;
            case 0x15:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.securityBandType;
                package->data.data8[0]=var_sys_NVM.securityBandIsON;
                write_package(*package);
                break;
            case 0x16:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.securityBandInOpen;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x17:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.operationMode;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x18:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.flashLightMode;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x19:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.programmingDistance;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x1A:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.decelarationSensivity;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
                
            case 0x1B:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.homemPresente;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x07:
            case 0x1C:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.logicDigital;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x1D:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.softstop;
                package->data.data8[0]=var_sys_NVM.softStart;
                write_package(*package);
                break;
            case 0x03:
            case 0x1E:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.ligthTime;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x0A:
            case 0x1F:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.folow_me;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x20:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.Stopboton;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x21:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.electricBrake;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x22:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.velocityDecelaration;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x08:
            case 0x23:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.flashRGBMode;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x24:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.Direction_motor;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x25:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.TypeofMotor;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x26:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.positionRemotesWalk;
                package->data.data8[0]=var_sys_NVM.positionRemotesFull;
                write_package(*package);
                break;
            case 0x27:
                //input:
                //output:
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.counterMoves))+1);
                write_package(*package);
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.counterMoves))+0);
                write_package(*package);
                break;
            case 0x29:
                //input:
                //output:
                package->data.data8[1]=var_sys_NVM.OnlyRollingCode;
                package->data.data8[0]=0x00;
                write_package(*package);
                break;
            case 0x2A:
                //input:
                //output:
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningCurrentDecelarationClose))+1);
                write_package(*package);
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningCurrentDecelarationClose))+0);
                write_package(*package);
                break;
            case 0x2C:
                //input:
                //output:
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningCurrentDecelarationOpen))+1);
                write_package(*package);
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningCurrentDecelarationOpen))+0);
                write_package(*package);
                break;
            case 0x2E:
                //input:
                //output:
                package->data.data16=var_sys_NVM.learningCurrentNormalClose;
                write_package(*package);
                break;
            case 0x2F:
                //input:
                //output:
                package->data.data16=var_sys_NVM.learningCurrentNormalOpen;
                write_package(*package);
                break;
            case 0x30:
                //input:
                //output:
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningTimeToOpen))+1);
                write_package(*package);
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningTimeToOpen))+0);
                write_package(*package);
                break;
            case 0x32:
                //input:
                //output:
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningTimeToClose))+1);
                write_package(*package);
                package->data.data16=*(((uint16_t*)&(var_sys_NVM.learningTimeToClose))+0);
                write_package(*package);
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
                //input:
                //output:
                var_sys_NVM.decelarationOpen=package.data.data8[0];
                var_sys_NVM.decelarationClose=package.data.data8[1];
                break;
            case 0x11:
                //input:
                //output:
                var_sys_NVM.motorPower=package.data.data8[0];
                var_sys_NVM.motorSensitivity=package.data.data8[1];
                break;
            case 0x12:
                //input:
                //output:
                var_sys_NVM.walkTime=package.data.data8[1];
                break;
            case 0x02:
            case 0x13:
                //input:
                //output:
                var_sys_NVM.autoTimeFullClose=package.data.data8[0];
                var_sys_NVM.autoTimeWalkClose=package.data.data8[1];
                break;
            case 0x05:
            case 0x14:
                //input:
                //output:
                var_sys_NVM.photoCellIsON=package.data.data8[0];
                var_sys_NVM.photoCellInOpen=package.data.data8[1];
                break;
            case 0x15:
                //input:
                //output:
                var_sys_NVM.securityBandIsON=package.data.data8[0];
                var_sys_NVM.securityBandType=package.data.data8[1];
                break;
            case 0x16:
                //input:
                //output:
                var_sys_NVM.securityBandInOpen=package.data.data8[1];
                break;
            case 0x17:
                //input:
                //output:
                var_sys_NVM.operationMode=package.data.data8[1];
                break;
            case 0x18:
                //input:
                //output:
                var_sys_NVM.flashLightMode=package.data.data8[1];
                break;
            case 0x19:
                //input:
                //output:
                var_sys_NVM.programmingDistance=package.data.data8[1];
                break;
            case 0x1A:
                //input:
                //output:
                var_sys_NVM.decelarationSensivity=package.data.data8[1];
                break;
                
            case 0x1B:
                //input:
                //output:
                var_sys_NVM.homemPresente=package.data.data8[1];
                break;
            case 0x07:
            case 0x1C:
                //input:
                //output:
                var_sys_NVM.logicDigital=package.data.data8[1];
                break;
            case 0x1D:
                //input:
                //output:
                var_sys_NVM.softStart=package.data.data8[0];
                var_sys_NVM.softstop=package.data.data8[1];
                break;
            case 0x03:
            case 0x1E:
                //input:
                //output:
                var_sys_NVM.ligthTime=package.data.data8[1];
                break;
            case 0x0A:
            case 0x1F:
                //input:
                //output:
                var_sys_NVM.folow_me=package.data.data8[1];
                break;
            case 0x20:
                //input:
                //output:
                var_sys_NVM.Stopboton=package.data.data8[1];
                break;
            case 0x21:
                //input:
                //output:
                var_sys_NVM.electricBrake=package.data.data8[1];
                break;
            case 0x22:
                //input:
                //output:
                var_sys_NVM.velocityDecelaration=package.data.data8[1];
                break;
            case 0x08:
            case 0x23:
                //input:
                //output:
                var_sys_NVM.flashRGBMode=package.data.data8[1];
                break;
            case 0x24:
                //input:
                //output:
                var_sys_NVM.Direction_motor=package.data.data8[1];
                break;
            case 0x25:
                //input:
                //output:
                var_sys_NVM.TypeofMotor=package.data.data8[1];
                break;
            case 0x26:
                //input:
                //output:
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
                //input:
                //output:
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
                var_sys_NVM.learningCurrentDecelarationOpen=var_sys_NVM.learningCurrentDecelarationOpen|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                var_sys_NVM.learningCurrentDecelarationOpen=var_sys_NVM.learningCurrentDecelarationOpen&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                break;
            case 0x31:
                var_sys_NVM.learningCurrentDecelarationOpen=var_sys_NVM.learningCurrentDecelarationOpen|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                var_sys_NVM.learningCurrentDecelarationOpen=var_sys_NVM.learningCurrentDecelarationOpen&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                break;
                
            case 0x32:
                var_sys_NVM.learningCurrentDecelarationOpen=var_sys_NVM.learningCurrentDecelarationOpen|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                var_sys_NVM.learningCurrentDecelarationOpen=var_sys_NVM.learningCurrentDecelarationOpen&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(1*16));
                break;
            case 0x33:
                var_sys_NVM.learningCurrentDecelarationOpen=var_sys_NVM.learningCurrentDecelarationOpen|((uint32_t)(package.data.data16&0xFFFF)<<(uint8_t)(0*16));
                var_sys_NVM.learningCurrentDecelarationOpen=var_sys_NVM.learningCurrentDecelarationOpen&~((uint32_t)(~package.data.data16&0xFFFF)<<(uint8_t)(0*16));
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
            case (uint8_t)0://READ
                if(programmer_enable)
                    read_eusartparser(package);
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
                
            case (uint8_t)1://WRITE
                if(programmer_enable)
                    write_eusartparser(*package);
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
                
            case (uint8_t)2://PROGRAMMING_ENABLE
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
            case (uint8_t)3://CONFIRM
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
            case (uint8_t)4://NUM_COMMANDS
                package->address=0x00;
                package->data.data16=var_sys_NVM.positionRemotesFull;
                for(uint8_t i=0;i<var_sys_NVM.positionRemotesFull;i++)
                if(cmdMemoryIsEmpty(0,i)==TRUE)
                    package->data.data16--;
                write_package(*package);
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
            case (uint8_t)5://NUM_EMPTY_COMMANDS
                package->address=0x00;
                package->data.data16=0;
                for(uint8_t i=0;i<var_sys_NVM.positionRemotesFull;i++)
                if(cmdMemoryIsEmpty(0,i)==TRUE)
                    package->data.data16++;
                write_package(*package);
                confirmpackage(package, TRUE);
                write_package(*package);
                break;
            case (uint8_t)6://OCCUPIED_POS
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
            case (uint8_t)7://EMPTY_POS
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
            case (uint8_t)8://SAVE_COMMAND
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
                break;
            case (uint8_t)9://ERASE_COMMAND
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
                break;
                
            default:
                package->functioncode=0x03;
                package->address=0x00;
                package->data.data16=0x0000;
                write_package(*package);
        }       
    }
