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
        st_InitLearning,            /**<Quando o portão fica sem saber o estado em que se encontra. */
	st_WaitForClosed,           /**<Estado em que o portão está fechado. */
        st_WaitLearnigOpen,           /**<Estado em que o portão está fechado. */
	st_WaitLearnigClose,           /**<Estado em que o portão está a abrir. */
	st_WaitForOpened,           /**<Estado em que o portão está a abrir. */
        st_WaitForEndLearn,         /**<Está a fechar o portão espera que chega ao fim. */
}sm_state_ControlLearning_t;

void sm_execute_ControlLearning( sm_t *psm );

void generateErrorLearnig(void);

void clearLearningValue(void);

unsigned long calculateMean(unsigned long meanValue,unsigned long newValue);



#ifdef	__cplusplus
}
#endif

#endif	/* SM_CONTROLLEARNING_H */

