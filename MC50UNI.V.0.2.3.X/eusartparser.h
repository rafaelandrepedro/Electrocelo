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
#include "main.h"


#ifdef	__cplusplus
extern "C" {
#endif
    
    extern volatile varSystem_NVM var_sys_NVM;
    extern volatile char RFFull;
    extern volatile varSystem var_sys;
    
    bool programmer_enable=0;
    
    bool read_eusartparser(struct package_t* package);
    
    void write_eusartparser(struct package_t package);
    
    void confirmpackage(struct package_t* package, bool confirm);
    
    void eusartparser(struct package_t* package);
    
    void updateChangesToUart(void);

#ifdef	__cplusplus
}
#endif

#endif	/* EUSARTPARSER_H */

