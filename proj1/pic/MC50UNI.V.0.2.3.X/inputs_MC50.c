
#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "mcc_generated_files/pin_manager.h"
#include "inputs.h"
#include "outputs.h"
#include "controlMemory.h"
#include "keeloqDecrypt.h"




unsigned char BufferRF[9]; // receive buffer
unsigned char BufferRF_12BIT[2]; // temp receive buffer for Validation

static unsigned char RFstate; // receiver state
static signed int RFcount; // timer counter
static unsigned char Bptr; // receive buffer pointer
static unsigned char BitCount; // received bits counter
//unsigned int XTMR; // 16 bit extended timer
volatile char RFFull; // buffer full
volatile char RFFull_12BIT; //Buffer full for 12Bit
volatile char RFBit; // sampled RF signal

volatile FimdeCurso_st fimdecurso;
volatile Security_st   security;

//volatile Tenho de usar a contagem com base em 100us pois 1ms não dará para medir a uma velocidade baixa.

extern char tempMEM;

extern volatile BUTTONS_STRUCT button_struct;
extern volatile RF_KEY_STRUCT rfCMD;
extern volatile varSystem_NVM var_sys_NVM;
extern volatile varSystem var_sys;
extern volatile timeslotSystem ts_system;
classic_encoder_t classic_data;

void rxi(void) {
    // this routine gets called every time TMR0 overflows
    RFBit = DataRF_PORT; // sampling RF pin verify!!!
    //TMR0 -= PERIOD; // reload
    //T0IF = 0;
    //XTMR++; // extended 16 long timer update
    if (RFFull) // avoid overrun
        return;

    switch (RFstate) // state machine main switch
    {
        case TRFUNO:
            if (RFBit == 0) { // falling edge detected ----+
                // |? 2001 Microchip Technology Inc. Preliminary DS00744A-page 17 AN744
                // +----
                RFstate = TRFZERO;
            } else { // while high
                RFcount--;
                if (RFcount < HIGH_TO)
                {
                    
                    RFstate = TRFreset; // reset if too long
                }
            }
            break;
        case TRFZERO:
            if (RFBit) { // rising edge detected +----
                // |
                // ----+
                
                RFstate = TRFUNO;
                BufferRF[Bptr] >>= 1; // rotate
                if (RFcount >= 0) {
                    BufferRF[Bptr] += 0x80; // shift in bit
                    //EUSART_Write('1');
                }
                else
                {
                    //EUSART_Write('0');
                }
                RFcount = 0; // reset length counter

                if ((++BitCount & 7) == 0)
                    Bptr++; // advance one byte
                if (BitCount == NBIT) {
                    RFstate = TRFreset; // finished receiving
                    RFFull = 1;
                    //EUSART_Write('\r');
                    //EUSART_Write('\n');
                }
            } else { // still low
                RFcount++;
                if (RFcount >= LOW_TO) // too long low
                {
                    
                    RFstate = TRFSYNC; // fall back into RFSYNC state
                    Bptr = 0; // reset pointers, while keep counting on
                    BitCount = 0;
                }
            }
            break;
        case TRFSYNC:
            if (RFBit) { // rising edge detected +---+ +---..
                // | | <-Theader-> |
                // +----------------+
                if ((RFcount < SHORT_HEAD) || (RFcount >= LONG_HEAD)) {
                    if((RFcount < SHORT_HEAD_12BIT) || RFcount>=LONG_HEAD_12BIT)
                    {
                        RFstate = TRFreset;
                    }
                    else
                    {
                        RFcount = -10; // restart counter
                        RFstate = TRFUNO_12BIT;

                    }
                } else {
                    RFcount = 0; // restart counter
                    RFstate = TRFUNO;
                }
            } else { // still low
                RFcount++;
            }
            break;
            //alTERAÇÃO DO ALGORITMO PARA 12 bIT //
        case TRFUNO_12BIT:
            if (RFBit == 0) { // falling edge detected ----+
                // |? 2001 Microchip Technology Inc. Preliminary DS00744A-page 17 AN744
                // +----
                RFstate = TRFZERO_12BIT;
                BufferRF[Bptr] >>= 1; // rotate
                if (RFcount >= 0) {
                    BufferRF[Bptr] += 0x80; // shift in bit
                    
                }
                RFcount = 0; // reset length counter

                if ((++BitCount & 7) == 0)
                {
                    Bptr++; // advance one byte
                    BufferRF[Bptr]=0;
                }
                if (BitCount == NBIT_12BIT) {
                    RFstate = TRFreset; // finished receiving
                    if(RFFull_12BIT==1)
                    {
                        if(BufferRF_12BIT[0]==BufferRF[0] && BufferRF_12BIT[1]==BufferRF[1])
                        {
                            RFFull = 1;
                            BufferRF[2]=0;
                            BufferRF[3]=0;
                        }
                        else
                        {
                            BufferRF_12BIT[0]=BufferRF[0];
                            BufferRF_12BIT[1]=BufferRF[1];
                        }

                    }
                    else
                    {
                        RFFull_12BIT=1;
                        BufferRF_12BIT[0]=BufferRF[0];
                        BufferRF_12BIT[1]=BufferRF[1];
                    }
                }
            } else { // while high
                RFcount++;
                if (RFcount >= LOW_TO)
                {

                    RFstate = TRFreset; // reset if too long
                }
            }
        break;
        case TRFZERO_12BIT:
            if (RFBit) { // rising edge detected +----
                // |
                // ----+

                RFstate = TRFUNO_12BIT;
                
            } else { // still low
                RFcount--;
                if (RFcount < HIGH_TO) // too long low
                {

                    RFstate = TRFSYNC; // fall back into RFSYNC state
                    Bptr = 0; // reset pointers, while keep counting on
                    BitCount = 0;
                }
            }
        break;
        //AN744 DS00744A-page 18 Preliminary ? 2001 Microchip Technology Inc.
        case TRFreset:
        default:
            RFstate = TRFSYNC; // reset state machine in all other cases
            RFcount = 0;
            Bptr = 0;
            BitCount = 0;
            break;

    } // switch

} // rxi

void InitReceiver() {
    TMR0IF = 0;
    TMR0IE = 1; // TMR0 overflow interrupt
    GIE = 1; // enable interrupts
    RFstate = TRFreset; // reset state machine in all other cases
    RFFull_12BIT=0;//Mark buffer 12BIT empty
    RFFull = 0; // start with buffer empty
    //XTMR = 0; // start extended timer
}

signed char getKeyPressed() {
    signed char temp=-1;
    if(RFFull)
    {
        temp=(BufferRF[7]&0xF0)>>4;//Remove os 4 bit do byte 7 buffer corresponde ao ultimo byte do serial number e favria comfrome os teclas pressionada
    }
    return temp;
}


/******************************************************************************/
/* This task reads the RF keys state and resets the processed key indicator   */
/* flag. It runs at the main timeslot frequency, currently at 50ms            */
/******************************************************************************/
void readRFButtons() {
    static unsigned char key1       = 0;
    static uint32_t      serial     = 0;
    static uint16_t      rollingCode= 0;
    static TypeCMD       keyType    = 0;
    static TypeRemote_st typeRemote;
    

    //button_struct.old = 0x00;																												//Nenhuma tecla permida
    //button_struct.current = 0x00;
    if(RFFull)//Verifica se existe alguma tecla RF permida
    {
            
         if(RFFull_12BIT==0)
         {
            keyType = keeloqDecryptPacket(BufferRF,&classic_data);//Faz desencyptação do comando keeloQ recebido
         }
         else
         {
            keyType = DecryptPacket_12BIT(BufferRF,&classic_data);//faz desencyptação do comando 12 bIT recebido
         }


        key1        = classic_data.fcode1;
        serial      = classic_data.serialnumber;
        rollingCode = classic_data.sync;
        typeRemote  = classic_data.type;
        
//        if (typeRemote == 0){
//            
//             SetSegmentValueMain(dM,d0);
//             ts_system.timeSinalizationDigit=(TIME_1S*2);
//        }
//        else{
//            
//            SetSegmentValueMain(d0,d0);
//            ts_system.timeSinalizationDigit=(TIME_1S*2);
//        }
        
        if  (var_sys.LearningIsEnabled == YES){
           
             if (keyType==NoCMD || rfCMD.currentKey!=key1 || rfCMD.currentSerial!=serial || keyType!=rfCMD.currentType)
                rfCMD.processed=0;
                rfCMD.timer=0; 
        }

        else if (keyType==NoCMD ||( keyType!=rfCMD.currentType && ts_system.TimeLastCommand<=0 && rfCMD.currentRolling!=rollingCode ) || rfCMD.currentKey!=key1 || rfCMD.currentSerial!=serial)
        {
           rfCMD.processed=0;
           rfCMD.timer=0;
        }
        else if(ts_system.TimeLastCommand<=0 && typeRemote==DIP_12BIT)
        {
           rfCMD.processed=0;
           rfCMD.timer=0;
        }
           

        ts_system.TimeLastCommand=TIME_500MS;//Renicia o contador entre comandos válidos. Ou seja tem que estar 500Ms sem receber qualquer comando para aceitar um novo comando.
        
        rfCMD.currentType=keyType;
        if
        (
            rfCMD.currentType == NoCMD  ||
            rfCMD.currentKey!=key1      ||
            rfCMD.currentSerial!=serial ||
            rfCMD.currentRolling!=rollingCode
        )
        {
            rfCMD.currentKey=key1;
            rfCMD.currentSerial=serial;
            rfCMD.currentPosMem=classic_data.positionMem;
            rfCMD.timer=0;  
        }
        rfCMD.currentRolling=rollingCode;

    }

    // se a tecla já foi processada, não se processa segunda vez!
    if(rfCMD.processed == 1)
    {
       rfCMD.currentType = NoCMD;
    }
    else if(rfCMD.currentType != NoCMD)
    {
//        rfCMD.timer++;
        if ( rfCMD.timer < 250 )
        {
            rfCMD.timer++;
        }
//        rfCMD.timer++;
//        if ( rfCMD.timer==0 )
//        {
//            rfCMD.timer--;  // DM: Overflow protection.
//        }
    }
    
}

TypeCMD GetOpenOrder(void){
    //Força o sistema a nao aceitar comandos quando ocorre o erro de sobre corrente.
   if (var_sys.LearningIsEnabled == NO){
        
       if(ts_system.TimeCurrentAlarm>0) 

        {
            SetSegmentValueIntermitentMain(dL,d1,TIME_1S);
            ts_system.timeSinalizationDigit=TIME_500MS;
            rfCMD.processed=1;//Limpa Comandos recebidos
            button_struct.processed=1;//Limpa Teclas recebidas
            return NoCMD;
        }
        else if(var_sys_NVM.homemPresente >0)
        {
            if(button_struct.current==BTN_FULL)
            {
                ts_system.timeSinalizationDigit=TIME_500MS;
                SetSegmentValueIntermitentMain(dL,d0,TIME_200MS);
                if (var_sys_NVM.homemPresente == 2){
                   button_struct.processed=1; 
                }
                return TypeFullOpen;
            }
            else if(button_struct.current==BTN_WALK)
            {
                ts_system.timeSinalizationDigit=TIME_500MS;
                SetSegmentValueIntermitentMain(dL,d5,TIME_200MS);
                 //EUSART_Write_String("type");
                return TypeFullClose;

            }
            else
            {
                // EUSART_Write_String("NOCMD");
                return NoCMD;

            }

        }
        else if(button_struct.current==BTN_FULL)
        {
            ts_system.timeSinalizationDigit=TIME_1S*2;
            SetSegmentValueIntermitentMain(dL,d0,TIME_200MS);
            if(var_sys_NVM.logicDigital==1)
            {
                button_struct.processed=1;
                return TypeFullOpen;
            }
            else
            {
                button_struct.processed=1;
                return TypeFull;

            }
        }
        else if(button_struct.current==BTN_WALK)
        {
             // EUSART_Write_String("walk");
            ts_system.timeSinalizationDigit=TIME_1S*2;
            SetSegmentValueIntermitentMain(dL,d5,TIME_200MS);
            if(var_sys_NVM.logicDigital==1)
            {
                 button_struct.processed=1;
                 // EUSART_Write_String("typefullclose");
                return TypeFullClose;

            }
            else
            {
                 button_struct.processed=1;
                 // EUSART_Write_String("typewalk");
                return TypeWalk;


            }
        }
        else if(button_struct.current==BTN_PUSH)
        {
            ts_system.timeSinalizationDigit=TIME_1S*2;
            SetSegmentValueIntermitentMain(dP,dU,TIME_200MS);
            {
                button_struct.processed=1;
                return TypeFull;
            }
        }
        else
        {
            if(rfCMD.currentType!=NoCMD && rfCMD.currentType!=TypeProgrammingModeFull && rfCMD.currentType!=TypeProgrammingModeWalk )
            {
                SetSegmentValueIntermitentMain(rfCMD.currentPosMem/10, rfCMD.currentPosMem-((rfCMD.currentPosMem/10)*10),TIME_200MS);
                ts_system.timeSinalizationDigit=TIME_1S*2;
                rfCMD.processed=1;
            }
            // EUSART_Write_String((char*)rfCMD.currentType);
            return rfCMD.currentType;
        }
    }else
    {
       if(rfCMD.currentType!=NoCMD ){
                  SetSegmentValueIntermitentMain(rfCMD.currentPosMem/10, rfCMD.currentPosMem-((rfCMD.currentPosMem/10)*10),TIME_200MS);
                ts_system.timeSinalizationDigit=TIME_1S*1;
                rfCMD.processed=1; 
       }
       return rfCMD.currentType;
       
    }

    
    
}

signed char getSerialCmd(unsigned long* serial) {
    signed char temp=-1;
    if(RFFull)
    {
        if(RFFull_12BIT)
        {
            memcpy((char*)serial,&classic_data.serialnumber,4);
        }
        else
        {
            memcpy((char*)serial,(char*)BufferRF+4,4);
        }
        temp=classic_data.fcode1;//KeyLOQ
    }
    return temp;
}

TypeRemote_st getTypeRemote() {
    return classic_data.type;
}

void ClearFlag_rfCMD() {
    rfCMD.processed=1;
}

/******************************************************************************/
/* This task reads the keys state and resets the processed key indicator flag */
/* It runs at the main timeslot frequency, currently at 50ms                  */
/******************************************************************************/
void readbutton(void){
    
    
	static unsigned char key1=0, key2=0;

	//button_struct.old = 0x00;			//Nenhuma tecla permida
	//button_struct.current = 0x00;		//Nenhuma tecla permida

	key2 = ( BUTTON_PORT & NO_KEY );
    asm("NOP"); 
    asm("NOP");
    asm("NOP");
	key1 = ( BUTTON_PORT & NO_KEY );

	if ( key2 == key1 )
	{
        button_struct.current = key1;
	}
    else
    {
        button_struct.current = NO_KEY;
    }

    if ( button_struct.current == NO_KEY ||  ( button_struct.current != button_struct.old && button_struct.current == BTN_UPDOWN))
	{
		button_struct.processed=0;
        button_struct.timer=0;
	}

	if ( button_struct.current != NO_KEY )
	{
		button_struct.old = button_struct.current;
//        button_struct.timer++;
        if ( button_struct.timer < 250 )
        {
            button_struct.timer++;
        }
//		button_struct.timer++;
//        if ( button_struct.timer == 0 )
//        {
//            button_struct.timer--;
//        }
	}
	else
	{
		button_struct.timer=0;
	}

	// se a tecla já foi processada, não se processa segunda vez!
	if ( button_struct.processed == 1 )
	{
		button_struct.current = NO_KEY;
	}

}


void readInputs(void){
    
    //---------------------------------FIM-DE-CURSO-DE-FECHO---------------------------------------------------------

    //var_sys.FimCurso_CloseIsEnabled = FimCurso_Close_GetValue();
    if(var_sys_NVM.Direction_motor == 0){fimdecurso.FimdeCursoCloseAUX=FimCurso_Close_GetValue();}
    else {fimdecurso.FimdeCursoCloseAUX=FimCurso_Open_GetValue();}
    
    
    
    //De forma a eliminar lixo na leitura dos PINS FIM DE CURSO FECHADO.
    //(50 milisegundos de estabilidade no pino para confirmar valor do fim de curso e da abertura)
    // caso estado se mantenha
    if (fimdecurso.FimdeCursoCloseAUX==fimdecurso.FimdeCursoCloseOLD)
    {
           fimdecurso.FimdeCursoCloseTimer++;																											// incrementar o timer
    }
    // caso o estado se tenha alterado
    else
    {
            fimdecurso.FimdeCursoCloseOLD = fimdecurso.FimdeCursoCloseAUX;																			// guardar valor actual
            fimdecurso.FimdeCursoCloseTimer=0;																											// e fazer reset do timer
    }

    // caso o valor esteja estabilizado por mais de 50ms, copiar valor para a respéctiva variável do sistema
    if (fimdecurso.FimdeCursoCloseTimer>=TIME_50MS)
    {
        var_sys.FimCurso_CloseIsEnabled=fimdecurso.FimdeCursoCloseAUX;
    }
    
    
    //---------------------------------FIM-DE-CURSO-DE-ABERTURA---------------------------------------------------------
    
    
    //var_sys.FimCurso_OpenIsEnabled = FimCurso_Open_GetValue();
    
    if(var_sys_NVM.Direction_motor == 0){fimdecurso.FimdeCursoOpenAUX=FimCurso_Open_GetValue();}
    else {fimdecurso.FimdeCursoOpenAUX=FimCurso_Close_GetValue();}

    //De forma a eliminar lixo na leitura dos PINS FIM DE CURSO ABERTO.
    //(50 milisegundos de estabilidade no pino para confirmar valor do fim de curso e da abertura)
    // caso estado se mantenha
    if (fimdecurso.FimdeCursoOpenAUX==fimdecurso.FimdeCursoOpenOLD)
    {
           fimdecurso.FimdeCursoOpenTimer++;																											// incrementar o timer
    }
    // caso o estado se tenha alterado
    else
    {
            fimdecurso.FimdeCursoOpenOLD = fimdecurso.FimdeCursoOpenAUX;																			// guardar valor actual
            fimdecurso.FimdeCursoOpenTimer=0;																											// e fazer reset do timer
    }

    // caso o valor esteja estabilizado por mais de 50ms, copiar valor para a respéctiva variável do sistema
    if (fimdecurso.FimdeCursoOpenTimer>=TIME_50MS)
    {
        var_sys.FimCurso_OpenIsEnabled=fimdecurso.FimdeCursoOpenAUX;
    }


    //var_sys.photoCellIsObstructed = Photocell_GetValue();
    security.PhotoCellAUX=Photocell_GetValue();

    //De forma a eliminar lixo na leitura dos PINS FotoCelelula obstruida.
    //(50 milisegundos de estabilidade no pino para confirmar valor do fim de curso e da abertura)
    // caso estado se mantenha
    if (security.PhotoCellAUX==security.PhotoCellOLD)
    {
           security.PhotoCellTimer++;																											// incrementar o timer
    }
    // caso o estado se tenha alterado
    else
    {
            security.PhotoCellOLD = security.PhotoCellAUX;																			// guardar valor actual
            security.PhotoCellTimer=0;																											// e fazer reset do timer
    }

    // caso o valor esteja estabilizado por mais de 50ms, copiar valor para a respéctiva variável do sistema
    if (security.PhotoCellTimer>=TIME_50MS)
    {
        var_sys.photoCellIsObstructed=security.PhotoCellAUX;
    }


    security.SecurityBarAUX=SecurityBar_GetValue();
    //De forma a eliminar lixo na leitura dos PINS FotoCelelula obstruida.
    //(50 milisegundos de estabilidade no pino para confirmar valor do fim de curso e da abertura)
    // caso estado se mantenha
    if (security.SecurityBarAUX==security.SecurityBarOLD)
    {
           security.SecurityBarTimer++;																											// incrementar o timer
    }
    // caso o estado se tenha alterado
    else
    {
            security.SecurityBarOLD = security.SecurityBarAUX;																			// guardar valor actual
            security.SecurityBarTimer=0;																											// e fazer reset do timer
    }

    // caso o valor esteja estabilizado por mais de 50ms, copiar valor para a respéctiva variável do sistema
    if (security.SecurityBarTimer>=TIME_50MS)
    {
        security.SecurityBarSTATE=security.SecurityBarAUX;
    }

    security.SecurityBar8K2AUX=SecurityBar8K_GetValue();
    //De forma a eliminar lixo na leitura dos PINS FotoCelelula obstruida.
    //(50 milisegundos de estabilidade no pino para confirmar valor do fim de curso e da abertura)
    // caso estado se mantenha
    if (security.SecurityBar8K2AUX==security.SecurityBar8K2OLD)
    {
           security.SecurityBar8K2Timer++;																											// incrementar o timer
    }
    // caso o estado se tenha alterado
    else
    {
            security.SecurityBar8K2OLD = security.SecurityBar8K2AUX;																			// guardar valor actual
            security.SecurityBar8K2Timer=0;																											// e fazer reset do timer
    }

    // caso o valor esteja estabilizado por mais de 50ms, copiar valor para a respéctiva variável do sistema
    if (security.SecurityBar8K2Timer>=TIME_50MS)
    {
        security.SecurityBar8K2STATE=security.SecurityBar8K2AUX;
    }
    

    if (var_sys_NVM.securityBandType == 0)
    {
        if(security.SecurityBarSTATE==0 && security.SecurityBar8K2STATE==1)
        {
            var_sys.SecurityBarIsObstructed = NO;
        }
        else
        {
            var_sys.SecurityBarIsObstructed = YES;
        }
    }
    else
    {
        var_sys.SecurityBarIsObstructed = security.SecurityBarSTATE;
    }

    //Não implementado não é necessário validação temporal.
}

void ControlInputs(void){
    
    
    
    if (( var_sys.StateMotor==InClose || (((RelayClose_GetValue() == 1)&& var_sys_NVM.Direction_motor == 0)||((RelayOpen_GetValue() == 1)&&var_sys_NVM.Direction_motor == 1))) && (var_sys.FimCurso_CloseIsEnabled == YES))
    {
        var_sys.StateMotor = Stopped;
        //EUSART_Write_String("Stop fecho por fim de curso\n");
    }
    if((var_sys.StateMotor==InOpenFull || var_sys.StateMotor==InOpenWalk || (((RelayOpen_GetValue() == 1) &&var_sys_NVM.Direction_motor == 0)||((RelayClose_GetValue() == 1) && var_sys_NVM.Direction_motor == 1))) && (var_sys.FimCurso_OpenIsEnabled == YES))
    { 
        var_sys.StateMotor = Stopped;
        //EUSART_Write_String("Stop abertura por fim de curso 3\n");
    }
    if (var_sys.LearningIsEnabled != YES){
    //controle por fotocelula
        if((var_sys_NVM.photoCellIsON == 1) && (var_sys.photoCellIsObstructed == YES) && var_sys.AutoInversionActive==NO)
        {
            // fotocélula ativa e obstruída. Verifica se a fotocélula tem de atuar
            // conforme o valor de photoCellInOpen que diz se funcionam no fecho ou na
            // abertura. Não é possível uma opção para ambos os sentidos porque pode
            // provocar entalamentos (ambas ligadas na mesma entrada não se consegue
            // distinguir).
            // (Sr. Simões Electrocelos 08-01-2016)
            //if( (var_sys.StateMotor==InOpenFull || var_sys.StateMotor==InOpenWalk) && (var_sys_NVM.photoCellInOpen!=0) ) // (photoCellInOpen!=0) is the same that (photoCellInOpen==1 || photoCellInOpen==2)
            if((var_sys.StateMotor==InOpenFull || var_sys.StateMotor==InOpenWalk) && (var_sys_NVM.photoCellInOpen==1))
            {
                var_sys.StateMotor = Stopped;
                //EUSART_Write_String("Stop abertura por fotocelula\n");
            }
            //else if( (var_sys.StateMotor==InClose) && (var_sys_NVM.photoCellInOpen==0 || var_sys_NVM.photoCellInOpen==2))
            else if(( var_sys.StateMotor == InClose && (var_sys_NVM.photoCellInOpen == 0))&&(var_sys.velocityFactorstop <=0)&& (var_sys.AutoInversionActive == YES))
            {
                var_sys.StateMotor = Stopped;
                //EUSART_Write_String("Stop fecho por fotocelula\n");
            }
        }

        //controle por Barreiras
        if((var_sys_NVM.securityBandIsON == 1 || var_sys_NVM.Stopboton == 1) && (var_sys.SecurityBarIsObstructed == YES && var_sys.AutoInversionActive == NO))
        {
            // Banda ativa e obstruída. Verifica se a banda tem de atuar
            // conforme o valor de securityBandInOpen que diz se funcionam no fecho, na
            // abertura. Não é possível uma opção para ambos os sentidos porque pode
            // provocar entalamentos (ambas ligadas na mesma entrada não se consegue
            // distinguir).
            // (Sr. Simões Electrocelos 08-01-2016)
            //if( (var_sys.StateMotor==InClose) && (var_sys_NVM.securityBandInOpen==0 || var_sys_NVM.securityBandInOpen==2) )
            
            if(var_sys.StateMotor == InClose && (var_sys_NVM.securityBandInOpen == 0))
            {
                var_sys.StateMotor = Stopped;
                //EUSART_Write_String("Stop fecho por barreira \n");
            }
            //else if( (var_sys.StateMotor==InOpenFull || var_sys.StateMotor==InOpenWalk) && (var_sys_NVM.securityBandInOpen!=0) )    // (securityBandInOpen!=0) is the same that (securityBandInOpen==1 || securityBandInOpen==2)
            else if((var_sys.StateMotor==InOpenFull || var_sys.StateMotor==InOpenWalk) && (var_sys_NVM.securityBandInOpen == 1)||var_sys_NVM.Stopboton ==1)
            {
                var_sys.StateMotor = Stopped;
                //EUSART_Write_String("Stop abertura por barreira\n");
            }        
         }
   }
}

StateEnum GetSecurityStateInOpening()
{
    // The photocell and security band cannot actuate in close an open at the
    // same time. It can provoke accidents. (Sr. Simões Electrocelos 08-01-2016)
    
    //if( (var_sys_NVM.securityBandIsON==1) && (var_sys.SecurityBarIsObstructed==YES) && (var_sys_NVM.securityBandInOpen!=0) )    // (securityBandInOpen!=0) is the same that (securityBandInOpen==1 || securityBandInOpen==2)
//    if (ts_system.timeoutMenu > 0 || button_struct.timer > TIME_1S){
//         return YES;
//     }
    if((var_sys_NVM.securityBandIsON == 1) && (var_sys.SecurityBarIsObstructed == YES)&&(var_sys_NVM.securityBandInOpen == 1)&& (var_sys_NVM.Stopboton == 0))
    {
        //Sinaliza o LCD quando as Bandas sao obstruidas
        ts_system.timeSinalizationDigit=TIME_200MS;
        SetSegmentValueIntermitent(dL,dA,TIME_1S);
        return YES;
    }
    
    else if((var_sys_NVM.Stopboton == 1) && (var_sys.SecurityBarIsObstructed == YES))//&&(var_sys_NVM.securityBandInOpen == 1))  V.156_SE 25-11-2016
    {
        //Sinaliza o LCD quando as Bandas sao obstruidas
        ts_system.timeSinalizationDigit=TIME_200MS;
        SetSegmentValueIntermitent(d5,dt,TIME_1S);
        return ST;//V.156_SE 25-11-2016
    }
    //else if( (var_sys_NVM.photoCellIsON==1) && (var_sys.photoCellIsObstructed==YES) && (var_sys_NVM.photoCellInOpen!=0) )   // (photoCellInOpen!=0) is the same that (photoCellInOpen==1 || photoCellInOpen==2)
    else if( (var_sys_NVM.photoCellIsON==1) && (var_sys.photoCellIsObstructed==YES)&&(var_sys_NVM.photoCellInOpen==1) )
    {
        //Sinaliza o LCD quando as Fotocelulas sao obstruidas
        ts_system.timeSinalizationDigit=TIME_200MS;
        SetSegmentValueIntermitent(dL,dE,TIME_1S);
        return YES;
    }
    else
    {
        return NO;
    }
}

StateEnum GetSecurityStateInClosing()
{
    // The photocell and security band cannot actuate in close an open at the
    // same time. It can provoke accidents. (Sr. Simões Electrocelos 08-01-2016)

    //if( (var_sys_NVM.securityBandIsON==1) && (var_sys.SecurityBarIsObstructed==YES) && (var_sys_NVM.securityBandInOpen==0 || var_sys_NVM.securityBandInOpen==2) )
//     if (ts_system.timeoutMenu > 0 || button_struct.timer > TIME_1S){
//         return YES;
//     }
    
     if((var_sys_NVM.securityBandIsON == 1) && (var_sys.SecurityBarIsObstructed == YES)&&(var_sys_NVM.securityBandInOpen == 0)&& (var_sys_NVM.Stopboton == 0))
    {
        //Sinaliza o LCD quando as Bandas sao obstruidas

        ts_system.timeSinalizationDigit=TIME_200MS;
        SetSegmentValueIntermitent(dL,dA,TIME_1S);
        return YES;
    }
        else if((var_sys_NVM.Stopboton == 1) && (var_sys.SecurityBarIsObstructed == YES))//&&(var_sys_NVM.securityBandInOpen == 1))  V.156_SE 25-11-2016
    {
        //Sinaliza o LCD quando as Bandas sao obstruidas
        ts_system.timeSinalizationDigit=TIME_200MS;
        SetSegmentValueIntermitent(d5,dt,TIME_1S);
        return ST;//V.156_SE 25-11-2016
    }
    //else if( (var_sys_NVM.photoCellIsON==1) && (var_sys.photoCellIsObstructed==YES) && (var_sys_NVM.photoCellInOpen==0 || var_sys_NVM.photoCellInOpen==2) )
    else if((var_sys_NVM.photoCellIsON == 1) && (var_sys.photoCellIsObstructed == YES)&&(var_sys_NVM.photoCellInOpen == 0))
    {
        //Sinaliza o LCD quando as Fotocelulas sao obstruidas
        ts_system.timeSinalizationDigit=TIME_200MS;
        SetSegmentValueIntermitent(dL,dE,TIME_1S);
        return YES;
    }

    else
    {
        return NO;
    }
}
