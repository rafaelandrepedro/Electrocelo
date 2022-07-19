/* 
 * File:   inputs.h
 * Author: cpereira
 *
 * Created on 4 de Setembro de 2014, 12:42
 */

#ifndef INPUTS_H
#define	INPUTS_H

#include "outputs.h"


#ifdef	__cplusplus
extern "C" {
#endif
#define CLOCK               4 // MHz
#define TE                  400 // us
#define OVERSAMPLING        3
#define BUTTON_PORT         PORTB
#define PERIOD              (TE/OVERSAMPLING*4/CLOCK)
#define NBIT                65 // number of bit to receive -1
#define NBIT_12BIT          13 // number of bit to receive -1
#define TRFreset            0
#define TRFSYNC             1
#define TRFUNO              2
#define TRFZERO             3
#define TRFUNO_12BIT        4
#define TRFZERO_12BIT       5

#define HIGH_TO             -10 // longest high Te
#define LOW_TO              10 // longest low Te
#define SHORT_HEAD          20 // shortest Thead accepted 2,7ms
#define LONG_HEAD           45 // longest Thead accepted 6,2ms

#define LONG_HEAD_12BIT     100 // longest Thead accepted 13,0ms
#define SHORT_HEAD_12BIT    80 // longest Thead accepted 11,0ms


// Masks for key detection.
    

  //::::::::::::::::::::::::::Debug:::::::::::::::::::::::::::::::::::::::::   
    
#define NO_KEY              0x37
#define BTN_MENU            0x27
#define BTN_UP              0x17
#define BTN_DOWN            0x00
#define BTN_CMD             0x07//0x27 wrong define 
    
#define BTN_UPDOWN          0x00
#define BTN_FULL            0x35
#define BTN_WALK            0x33
#define BTN_PUSH            0X36   
    
  //:::::::::::::::::::::::::PROGRAMA_EM_USO:::::::::::::::::::::::::::::::::::::::::

    
//#define NO_KEY              0xF7
//#define BTN_MENU            0xE7
//#define BTN_UP              0xD7
//#define BTN_DOWN            0xB7
//#define BTN_CMD             0x77
//#define BTN_UPDOWN          0x97
//#define BTN_FULL            0xF5
//#define BTN_WALK            0xF3
//#define BTN_PUSH            0XF6



/**
* \typedef    	KEYS_STRUCT
*
* \brief    Estrutura com timer para validação da tecla premida.
*/
typedef struct 
{
	unsigned char old;      // Last key to detect when a new key is pressed.
	unsigned char current;  // Current key detected, one of NO_KEY, BTN_MENU, BTN_UP, BTN_DOWN, BTN_CMD, BTN_UPDOWN, BTN_FULL or BTN_WALK.
	//unsigned long timer;    // Pressed time for the current key. Protected against overflow. (DM: With the current main timeslot, the 8 bits is sufficient for 12 seconds!)
    unsigned char timer;    // Pressed time for the current key. Protected against overflow. (DM: With the current main timeslot, the 8 bits is sufficient for 12 seconds!)
	unsigned char processed;// Flag to indicate when the current key has been processed by the code. Cleared automatically when no key is pressed.
}BUTTONS_STRUCT;

/**
* \typedef    	KEYS_STRUCT
*
* \brief    Estrutura com timer para validação da tecla premida.
*/
typedef struct 
{
	unsigned char currentType;
	unsigned char currentKey;
    unsigned long currentSerial;
    unsigned int  currentRolling;
    unsigned char currentPosMem;
	//unsigned long timer;                // Pressed time for the current RF key. DM: At the current main timeslot (50ms) it is sufficient for 12 seconds.
    unsigned char timer;                // Pressed time for the current RF key. DM: At the current main timeslot (50ms) it is sufficient for 12 seconds.
	unsigned char processed;            // Indicates if the key has been processed by the code.
}RF_KEY_STRUCT;

// estrutura para a validação dos valores dos fins de curso
typedef struct
{
	unsigned char FimdeCursoOpenAUX;
	unsigned char FimdeCursoOpenOLD;
	unsigned char FimdeCursoOpenTimer;
	unsigned char FimdeCursoCloseAUX;
	unsigned char FimdeCursoCloseOLD;
	unsigned char FimdeCursoCloseTimer;
}FimdeCurso_st;

// estrutura para a validação dos valores dos fins de curso
typedef struct
{
	unsigned char PhotoCellAUX;
	unsigned char PhotoCellOLD;
	unsigned char PhotoCellTimer;
	unsigned char SecurityBarAUX;
	unsigned char SecurityBarOLD;
	unsigned char SecurityBarTimer;
    unsigned char SecurityBarSTATE;
    unsigned char SecurityBar8K2AUX;
	unsigned char SecurityBar8K2OLD;
	unsigned char SecurityBar8K2Timer;
    unsigned char SecurityBar8K2STATE;
}Security_st;

/**********
 * Headers *
 **********/



void            rxi(void);
void            InitReceiver();
signed char     getKeyPressed();
signed char     getSerialCmd(unsigned long* serial);
TypeRemote_st   getTypeRemote();

void ClearFlag_rfCMD();
/**
* \fn    		void  readbutton ( void  )
* \return   	void
* \param		void
* \brief    	Função de leitura das teclas e calculo de timer de pressão da tecla.
*		Neste caso só pode estar uma tecla pressiona, quando está duas pressionadas é considerado outra tecla.
*/
void readbutton(void);

void readRFButtons();

/**
* \fn    	void readInputs(void)
* \return   	void
* \param        void
* \brief    	Leitura das entradas, e coloca o seu valor na estrutura
*/
void readInputs(void);

/**
* \fn    	void ControlInputs(void)
* \return   	void
* \param        void
* \brief    	Actua sobre o motor se detectar alguma condição de paragem
*/
void ControlInputs(void);

/**
* \fn    	StateEnum GetSecurityStateInOpening(void)
* \return   	YES- Quando estão activadas seguranças na abertura e NO- para quando essas seguranças estão desactivas.
* \param        void
* \brief    	Devolve o estado das seguranças na Abertura.
*/
StateEnum GetSecurityStateInOpening();

/**
* \fn    	StateEnum GetSecurityStateInClosing(void)
* \return   	YES- Quando estão activadas seguranças na fecho e NO- para quando essas seguranças estão desactivas.
* \param        void
* \brief    	Devolve o estado das seguranças no fecho.
*/
StateEnum GetSecurityStateInClosing();

/**
* \fn    	TypeCMD GetOpenOrder(void)
* \return   	Tipo de comando recebido.
* \param        void
* \brief    	Devolve o tipo de comando recebido por parte do botões fisicos ou por parte do do comando RF
*/
TypeCMD GetOpenOrder(void);

#ifdef	__cplusplus
}
#endif

#endif	/* INPUTS_H */

