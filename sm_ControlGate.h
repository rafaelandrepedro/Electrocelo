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
    st_Idle,        /**<Quando o portão fica sem saber o estado em que se encontra. */
	st_Closed,      /**<Estado em que o portão está fechado. */
	st_Opening,     /**<Estado em que o portão está a abrir. */
    st_Closing,     /**<Estado em que o portão a fechar. */
    st_Opened,      /**<Estado em que o portão está aberto. */
    st_Learning,    /**<Estado em que o portão está fazer a aprendizagem. */
}sm_state_ControlGate_t;


/**
 * \brief	Função que controla o estados da Maquina de estados De controlo do Portão
 *
 * \param psm	Apontador para estrutura da maquina de estados
 *
 * \return void
 */
void sm_execute_ControlGate( sm_t *psm );

/**
 * \brief Função de para inicializar o softStart.
 *
 * \return void
 */
void InitSoftStart(void);

void InitSoftStop(void);
/**
 * \brief Função que controla e gera eventos quando o portão está fechado.
 *
 * \return void
 */
void actionZone_Closed(void);

/**
 * \brief Função que controla e gera eventos quando o portão está A Abrir.
 *
 * \return void
 */
void actionZone_Opening(void);

/**
 * \brief Função que controla e gera eventos quando o portão está Aberto.
 *
 * \return void
 */
void actionZone_Opened(void);

/**
 * \brief Função que controla e gera eventos quando o portão está A Fechar.
 *
 * \return void
 */
void actionZone_Closing(void);

/**
 * \brief Função para dar uma ordem de abertura total ao portão.
 *
 * \return void
 */
void OpenFullOrder(void);

/**
 * \brief Função para dar uma ordem de fecho ao portão
 *
 * \return void
 */
void CloseOrder(void);

/**
 * \brief Função para dar uma ordem de Abertura pedonal ao portão
 *
 * \return void
 */
void OpenWalkOrder(void);

/**
 * \brief Função para dar uma ordem de paragem ao portão
 *
 * \return void
 */
void StopOrder(void);

/**
 * \brief Função que inicializa o tempo automatico de uma abertura pedonal.
 *
 * \return void
 */
void InitWalkAutoTime(void);

/**
 * \brief Função que inicializa o tempo automatico de uma abertura pedonal.
 *
 * \return void
 */
void InitFullAutoTime(void);

/**
 * \brief Função que verifica o estado de Follow me para ver se é necessário activar esse estado.
 *
 * \param securityClose	Estado das seguranças no fecho.
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



