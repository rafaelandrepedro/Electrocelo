/* 
 * File:   sm_ControlLearning.h
 * Author: cpereira
 *
 * Created on 17 de Outubro de 2014, 15:41
 */

#ifndef SM_CONTROLLEARNING_H
#define	SM_CONTROLLEARNING_H

#include "sm_common.h"
    
#ifdef	__cplusplus
extern "C" {
#endif


typedef struct {
    long timeClose;
    long timeOpen;
    unsigned char timeDecelerationClose;
    unsigned char timeDecelerationOpen;    
    unsigned int openCurrent;
    unsigned int closeCurrent;
    unsigned int openHistCurrent;
    unsigned int closeHistCurrent;
}LearnStruct;

typedef enum {
        st_InitLearning,            /**<Quando o port�o fica sem saber o estado em que se encontra. */
	st_WaitForClosed,           /**<Estado em que o port�o est� fechado. */
        st_WaitLearnigOpen,           /**<Estado em que o port�o est� fechado. */
	st_WaitLearnigClose,           /**<Estado em que o port�o est� a abrir. */
	st_WaitForOpened,           /**<Estado em que o port�o est� a abrir. */
        st_WaitForEndLearn,         /**<Est� a fechar o port�o espera que chega ao fim. */
}sm_state_ControlLearning_t;

void sm_execute_ControlLearning( sm_t *psm );

void generateErrorLearnig(void);

void clearLearningValue(void);

unsigned long calculateMean(unsigned long meanValue,unsigned long newValue);



#ifdef	__cplusplus
}
#endif

#endif	/* SM_CONTROLLEARNING_H */

