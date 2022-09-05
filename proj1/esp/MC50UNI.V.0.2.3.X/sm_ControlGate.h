/* 
 * File:   sm_ControlGate.h
 * Author: cpereira
 *
 * Created on 7 de Outubro de 2014, 15:17
 */

#ifndef SM_CONTROLGATE_H
#define	SM_CONTROLGATE_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MIN_SOFT_START_POWER    (81)    // This constant will define the minimum velocity of the softstart. Between 0 and 81, being 0 the fastest and 81 stopped. 
    
typedef enum {
    st_Idle,        /**<Quando o port�o fica sem saber o estado em que se encontra. */
	st_Closed,      /**<Estado em que o port�o est� fechado. */
	st_Opening,     /**<Estado em que o port�o est� a abrir. */
    st_Closing,     /**<Estado em que o port�o a fechar. */
    st_Opened,      /**<Estado em que o port�o est� aberto. */
    st_Learning,    /**<Estado em que o port�o est� fazer a aprendizagem. */
}sm_state_ControlGate_t;


/**
 * \brief	Fun��o que controla o estados da Maquina de estados De controlo do Port�o
 *
 * \param psm	Apontador para estrutura da maquina de estados
 *
 * \return void
 */
void sm_execute_ControlGate( sm_t *psm );

/**
 * \brief Fun��o de para inicializar o softStart.
 *
 * \return void
 */
void InitSoftStart(void);

void InitSoftStop(void);
/**
 * \brief Fun��o que controla e gera eventos quando o port�o est� fechado.
 *
 * \return void
 */
void actionZone_Closed(void);

/**
 * \brief Fun��o que controla e gera eventos quando o port�o est� A Abrir.
 *
 * \return void
 */
void actionZone_Opening(void);

/**
 * \brief Fun��o que controla e gera eventos quando o port�o est� Aberto.
 *
 * \return void
 */
void actionZone_Opened(void);

/**
 * \brief Fun��o que controla e gera eventos quando o port�o est� A Fechar.
 *
 * \return void
 */
void actionZone_Closing(void);

/**
 * \brief Fun��o para dar uma ordem de abertura total ao port�o.
 *
 * \return void
 */
void OpenFullOrder(void);

/**
 * \brief Fun��o para dar uma ordem de fecho ao port�o
 *
 * \return void
 */
void CloseOrder(void);

/**
 * \brief Fun��o para dar uma ordem de Abertura pedonal ao port�o
 *
 * \return void
 */
void OpenWalkOrder(void);

/**
 * \brief Fun��o para dar uma ordem de paragem ao port�o
 *
 * \return void
 */
void StopOrder(void);

/**
 * \brief Fun��o que inicializa o tempo automatico de uma abertura pedonal.
 *
 * \return void
 */
void InitWalkAutoTime(void);

/**
 * \brief Fun��o que inicializa o tempo automatico de uma abertura pedonal.
 *
 * \return void
 */
void InitFullAutoTime(void);

/**
 * \brief Fun��o que verifica o estado de Follow me para ver se � necess�rio activar esse estado.
 *
 * \param securityClose	Estado das seguran�as no fecho.
 *
 * \return void
 */
void VerifyFollowMe(StateEnum securityClose);

void setPositionInvertionInClosing();

void setPositionInvertionInOpening();

#ifdef	__cplusplus
}
#endif

#endif	/* SM_CONTROLGATE_H */



