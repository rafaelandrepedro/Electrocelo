/* 
 * File:   controlCurrent.h
 * Author: cpereira
 *
 * Created on 24 de Fevereiro de 2015, 11:30
 */

#ifndef CONTROLCURRENT_H
#define	CONTROLCURRENT_H

#ifdef	__cplusplus
extern "C" {
#endif

#define Samples_ADC                 30
#define Samples_DISCARD             2
#define ZERO_VALUE_ADC              510
#define OFFSET_CURRENT_INIT         60//50//100
#define OFFSET_CURRENT_HIST_INIT    1200//700//1000
#define OFFSET_CURRENT              50//100
#define OFFSET_CURRENT_HIST         500//700//1000

#define FactorX2                    10
#define FactorX                     -200  //-220
#define FactorB                     1300  //1100

#define Samples_EnergyADCHist       10
    
//typedef enum
//{
//    Motor500,
//    Motor800,
//    Motor1500,
//    Motor2000,
//    MotorSize
//}typeMotor_enum;
//
//typedef struct
//{
//    int     b;
//    char    m;
//    char    offset_m;
//    int     offset_b;
//    int     offsetDecelaration[NumberOfCycles];
//}CURRENT_LINE_STRUCT;

/**
* \fn    	void  ReadADC ( void  )
* \return   	void
* \param        void
* \brief    	Leitura da ADC lê o numero de samples definindo pelo Samples_ADC.
*/
void ReadADC(void);

/**
* \fn    	void getCurrent(void)
* \return   	void
* \param        void
* \brief        Calcula os valores de corrente e actualiza os mesmos.
*/
void refreshCurrent(void);


/**
* \fn    	unsigned long sumEnergy(unsigned int * array)
* \return   	Total de energia recebido em 20 instâncias.
* \param        unsigned int* array Ponteiro para o array de leituras da ADC.
* \brief    	Devolve o somatorio de enrgia nas ultimas  converções
*/
//unsigned int sumEnergyADC(unsigned int * array);
unsigned int sumEnergyADC(void);

/**
* \fn    	unsigned long sumEnergy(unsigned int * array)
* \param        unsigned int valueToSave Valor a ser guardado no array de historico de sumatorios.
* \param        unsigned int* arrayPointer Ponteiro para o array do historico de sumatorios da ADC.
* \brief    	adiciona ao array a quantidade de energia do ultimo sumatorio.
*/
//void saveEnergyADCHist(unsigned int valueToSave, unsigned int* arrayPointer);
void saveEnergyADCHist(unsigned int valueToSave);

/**
* \fn    	unsigned long sumEnergy(unsigned int * array)
* \return   	Total de energia recebido em 20 instâncias.
* \param        unsigned int* array ponteiro para o array com os valores a serem somados.
* \brief    	Devolve o somatorio a quantidade de energia nas ultimas converções de Samples_EnergyADCHist
*/
//unsigned long sumHIST(unsigned int * array);
unsigned long sumHIST(void);

/**
* \fn    	unsigned long getCurrentComparator(void)
* \brief    	Devolve o comparador de energia, este depende do modo em que o motor esta a operar dos parametros aprendidos e dos ofssets configurados para a currente.
* \return   	unsigned long quantidade de energia a ser comparada para gerar alarme.
*/
unsigned long getCurrentComparator();

/**
* \fn    	unsigned long sumEnergy(unsigned int * array)
* \brief    	controla todas as acções de gestão da corrente de consumo do motor de forma a gerar os alarmes de corrente.
*/
void ControlCurrent(void);


#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLCURRENT_H */

