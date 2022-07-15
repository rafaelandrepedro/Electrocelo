/* 
 * File:   outputs.h
 * Author: cpereira
 *
 * Created on 4 de Setembro de 2014, 12:42
 */

#ifndef OUTPUTS_H
#define	OUTPUTS_H

#include "main.h"


#ifdef	__cplusplus
extern "C" {
#endif

    #define DelayTRIACWait_20MS     200
//    #define SizeDecelatarionZone    (3*TIME_1S)
    //#define TimeElectricalBrake    (2*TIME_100MS)
    //#define TimeElectricalBrake    (8*TIME_100MS) // rev1.149
//    #define TimeElectricalBrake    (6*TIME_100MS) // rev1.151 - Cannot be bigger than 600ms so that it doesn't conflict with the TimeWaitToNextState.
    #define TimeElectricalBrake    ((5+6)*TIME_100MS) // rev1.151 - Cannot be bigger than 600ms so that it doesn't conflict with the TimeWaitToNextState.
    #define TimeToTurnOffTriac      80      //o Triac e desligado sempre passados 8000us do zero detectionc
    #define AtrasoNaVelocidadeStop   5
    #define AtrasoNaVelocidade      23//14  // Tempo minimo que o o triac está UP 1400us
    #define VelocidadeMinima        6 //7   //Calculado com expriencia no motor para definir uma velocidade a que o motor se desloca
    #define Timesecurityturnoofftriac  20 //Este valor foi adicionado de maneira que o triac desligue sempre ante de chegar ao zerocrossing.


    #define A	0x40
    #define B	0x20
    #define C	0X01
    #define D	0x02//0xFD//0x7F
    #define E	0x04//0xFB
    #define F	0x08//0xF7
    #define G	0x10//0xEF
    #define DP	0xFD

  

    #define	DISPLAY0		E|F|A|B|C|D
    #define	DISPLAY1		B|C
    #define	DISPLAY2		A|B|G|E|D
    #define	DISPLAY3		A|B|C|D|G
    #define	DISPLAY4		F|G|B|C
    #define	DISPLAY5		A|F|G|C|D
    #define	DISPLAY6		F|G|C|D|E|A
    #define	DISPLAY7		A|B|C
    #define	DISPLAY8		A|B|C|D|E|F|G
    #define	DISPLAY9		A|B|C|D|F|G
    #define	DISPLAYA		A|B|C|E|F|G
    #define	DISPLAYB		A|B|C|D|E|F|G
    #define	DISPLAYb		F|G|C|D|E
    #define	DISPLAYC		A|F|E|D
    #define	DISPLAYc		E|G|D
    #define	DISPLAYD		A|B|C|D|E|F
    #define	DISPLAYd		E|G|D|C|B
    #define	DISPLAYE		A|F|G|E|D
    #define	DISPLAYF		A|F|G|E
    #define	DISPLAYg		A|B|C|D|F|G
    #define	DISPLAYH		B|C|F|G|E
    #define	DISPLAYL		F|E|D
    #define	DISPLAYP		A|B|F|G|E
    #define	DISPLAYU		F|E|D|C|B
    #define	DISPLAYM		E|C|A 
    #define	DISPLAYr		E|G
    #define	DISPLAYc		E|G|D
    #define	DISPLAYMINUS            G
    #define	DISPLAYn		E|G|C
    #define	DISPLAYO		A|B|G|F
    #define	DISPLAYo		E|D|G|C
    #define	DISPLAYt		F|E|D|G
    #define	DISPLAYu		E|D|C
    #define	DISPLAYBAR		F|E
    #define	DISPLAYBLANK	0x00
    #define DISPLAYPOINT	DP
    #define UNDERSCORE		D
    #define	DISPLAYy		F|B|G|C|D


    typedef enum  DispValue_enum
    {
        d0,
        d1,
        d2,
        d3,
        d4,
        d5,
        d6,
        d7,
        d8,
        d9,
        dA,
        dB,
        dC,
        dd,
        dE,
        dF,
        dP,
        dH,
        dL,
        dU,
        dr,
        dt,
        du,        
        dM,
        dMinus,      
        dBar,
        sA,
        sB,
        sC,
        sD,
        sE,
        sF,
        dBlank,
        dy,
        db,
        dc,
        dq,        
        dSize,
                

    }DispValue_enum;
    typedef enum{
        Left,
        Rigth
    }Direction_en;

    typedef enum  ListDisp_enum
    {
        disp1_e,
        disp2_e,
        numberDisplays

    }ListDisp_enum;
    


    typedef enum  RGBY_enum
    {
        BLUE    = 1,
        GREEN   = 2,
        RED     = 3,
        YELLOW  = 4,    
    }RGBY_enum;
    
    typedef enum  RGB_type
    {
        rgb_fixo,
        rgb_pisca,
        rgb_pre,
        rgb_capacitor,        
                
    }RGB_type;
    
        typedef enum  flashtype
    {
        fixo,
        pisca,
        condominio,
        electroiman,        
                
    }flashtype;
    
        typedef enum  direcao_contagem
    {
            stoped,
            open,
            close        
    }direcao_contagem;

#define RGBO_ROn 0x20
#define RGBO_GOn 0x04
#define RGBO_BOn 0x00 
#define RGBO_YOn 0x24

    typedef struct display_group_st{
        unsigned char value_display1;
        unsigned char value_display2;
    }display_group_st;

    typedef struct display_st{
        display_group_st display_grp;
        ListDisp_enum lastDisplay;
        int intermitentFreq;
        char upFase;
    }display_st;

    typedef enum  TypeCycle_enum
    {
        Cycle12,
        Cycle21,
        Cycle32,
        NumberOfCycles,

    }TypeCycle_enum;

    typedef struct PowerControlStruct{
        StateEnum decelarationActive;
        unsigned char decelarationCyclesOn;
        unsigned char decelarationCyclesOff;
        unsigned char decelarationPower;
        unsigned char actualCycle;
        TypeCycle_enum typeCycle;
    }PowerControlStruct;

    typedef struct {
        stateMotor_enum lastState;
        StateEnum   ElectricBrakeIsActive ;
    }electricalBrakeStruct;
    

    void refreshSegment(void);
    void SetSegmentValueMain(char d1, char d2); // rev 1.149
    void SetSegmentValue(char d1, char d2);
    void SetSegmentValueLearn(Direction_en direction);
    void SetSegmentValueIntermitentMain(char d1, char d2,int time); // rev 1.149
    void SetSegmentValueIntermitent(char d1, char d2,int time);
    void Segments_Set(char value);
    void RGB_Set(char value);

    void controlMotorForce();
    unsigned char  GetMotorPower();

    void ControlMotor (void);
    void ControlLights(void);
    void controlVelocity(void);
    void setRGB_ON(RGBY_enum RGBLigth,int Freq);
    void setFlashLigth_ON(int Freq);
    stateMotor_enum VerifyElectricalBrake(stateMotor_enum actualState);
    signed long getTimeDecelaration(stateMotor_enum state);
    void ControlDecelarationFactor();

#ifdef	__cplusplus
}
#endif

#endif	/* OUTPUTS_H */

