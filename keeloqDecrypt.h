/* 
 * File:   keeloqDecrypt.h
 * Author: cpereira
 *
 * Created on 3 de Outubro de 2014, 11:52
 */

#ifndef KEELOQDECRYPT_H
#define	KEELOQDECRYPT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#define  SIZE_ListSyncValues 25
/** Decryption key for the KLQ algorithm. */
extern uint8_t DKEY[8];


typedef enum  {
    NO_DATA,    ///< No Transmission Received
    VALID_PACKET, /**< Valid Packet Received*/
    NOT_VALID_PACKET,
    NOT_LEARNED,
    SEED_RECEIVED,
    NOT_SEED_PACKET,
    LEARN_SUCCESS,
    NO_SPACE,
    DECRYPT_FAIL,
    RESYNC_REQ,
    HOP_CHECK_FAIL,
    NVM_WRITE_ERROR,
    MAC_ERROR,
    TIMER_OUT_OF_SYNC,
    ENCODER_TIMER_RESYNC,
    TX_LOW_VOLTAGE,
    CNT_OUT_OF_SYNC
    //Add more Errors here
}  result_code_t;

typedef struct  {
    uint32_t raw_data;
    uint32_t serialnumber;
    uint16_t sync;
    uint16_t disc;
    uint8_t fcode1;
    uint8_t fcode2;
    TypeRemote_st type;
    uint8_t positionMem;
}  classic_encoder_t;

typedef struct  {
    uint32_t serial;
    uint16_t sync;
}  classic_nvm_t;

/**
 * KLQ decryption algorithm.
 * \pre DKEY must contain the encryption key and Buffer must contain the data
 */
void Decrypt(uint8_t* packet);
void LoadManufCode(void);
void NormalKeyGen(uint32_t* serial);
void SecureKeyGen(uint8_t* seed);
bool DecCHK(classic_encoder_t* data);
result_code_t ReqResync(uint16_t CurrentHop);
result_code_t HopCHK(classic_encoder_t* data);

void* getClassicManufCode(void);
void setClassicManufCode(const uint8_t* data);
TypeCMD keeloqDecryptPacket(char* data,classic_encoder_t* classic_data);
static void keeloq_classic_decrypt_packet(classic_encoder_t* data);
uint16_t getHopCode(classic_encoder_t* data);

TypeCMD verifyProgramingMode(classic_encoder_t* classic_data);

TypeCMD DecryptPacket_12BIT (char* data,classic_encoder_t* classic_data);

#ifdef	__cplusplus
}
#endif

#endif	/* KEELOQDECRYPT_H */

