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
    bool programmer_enable=0;
    
    void read_eusartparser(struct package_t* package);
    
    void write_eusartparser(struct package_t package);
    
    void confirmpackage(struct package_t* package, bool confirm);
    
    void eusartparser(struct package_t* package);

#ifdef	__cplusplus
}
#endif

#endif	/* EUSARTPARSER_H */

