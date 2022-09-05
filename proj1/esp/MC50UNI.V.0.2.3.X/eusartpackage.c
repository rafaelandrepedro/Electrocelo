/* 
 * File:   eusartpackage.c
 * Author: rafael pedro
 *
 * Created on July 14, 2022, 10:12 AM
 */

#include "mcc_generated_files/eusart1.h"
#include "eusartpackage.h"

    void init_package(struct package_t* package){
        package->startbyte=STARTBYTE;
        package->endbyte=ENDBYTE;
        package->valid=TRUE;
    }
    
    bool valid_package(const struct package_t package){
        return package.valid;
    }
    
    struct package_t read_package(){
        struct package_t package;
        //verify start byte
        if(EUSART1_Read()!=STARTBYTE){
            package.valid=FALSE;
            return package;
        }
        else
            package.startbyte=STARTBYTE;
        
        //read package
        package.functioncode=EUSART1_Read();
        package.address=EUSART1_Read();
        package.data.data8[0]=EUSART1_Read();
        package.data.data8[1]=EUSART1_Read();
        
        //verify end byte
        if(EUSART1_Read()!=ENDBYTE){
            package.valid=FALSE;
            return package;
        }
        else
            package.endbyte=ENDBYTE;
        
        //valid package
        package.valid=TRUE;
        return package;
    }
    
    void write_package(const struct package_t package){
        //verify if its valid
        if(package.valid==FALSE)
            return;
        
        //send package
        EUSART1_Write(package.startbyte);
        EUSART1_Write(package.functioncode);
        EUSART1_Write(package.address);
        EUSART1_Write(package.data.data8[0]);
        EUSART1_Write(package.data.data8[1]);
        EUSART1_Write(package.endbyte);
        
        return;
    }
    