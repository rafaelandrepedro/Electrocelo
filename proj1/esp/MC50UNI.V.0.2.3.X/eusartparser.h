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

