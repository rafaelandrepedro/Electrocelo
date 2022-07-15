/* 
 * File:   sm_Main.h
 * Author: cpereira
 *
 * Created on 18 de Setembro de 2014, 14:18
 */

#ifndef SM_MAIN_H
#define	SM_MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "eusartparser.h"

typedef enum {
	st_standBy=0,		    /**<Em que o sistema está em standby. */
	st_MenuConfiguration=1,	    /**<Estado em que são efectuadas alterações do menu de configuração.. */
        st_MotorON=2,                 /**<Estado em que o motor está em movimento. */
}sm_state_Main_t;


extern sm_t main_stateMachine;

void sm_execute_main( sm_t *psm );
#ifdef	__cplusplus
}
#endif

#endif	/* SM_MAIN_H */

