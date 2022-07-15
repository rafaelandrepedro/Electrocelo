/**
  I2C Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c.c

  @Summary
    This is the generated header file for the I2C driver using MPLAB® Code Configurator

  @Description
    This header file provides APIs for driver for I2C.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.0.1
        Device            :  PIC16F1519
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.31
        MPLAB 	          :  MPLAB X 2.10
*/

/*
Copyright (c) 2013 - 2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*/

/**
  Section: Included Files
*/

#include "i2c.h"

/**
  I2C Driver Queue Status Type

  @Summary
    Defines the type used for the transaction queue status.

  @Description
    This defines type used to keep track of the queue status.
 */

typedef union
{
    struct
    {
            uint8_t full:1;
            uint8_t empty:1;
            uint8_t reserved:6;
    }s;
    uint8_t status;
}I2C_TR_QUEUE_STATUS;

/**
  I2C Driver Queue Entry Type

  @Summary
    Defines the object used for an entry in the i2c queue items.

  @Description
    This defines the object in the i2c queue. Each entry is a composed
    of a list of TRBs, the number of the TRBs and the status of the
    currently processed TRB.
 */
typedef struct
{
    uint8_t                             count;          // a count of trb's in the trb list
    I2C_TRANSACTION_REQUEST_BLOCK *ptrb_list;     // pointer to the trb list
    I2C_MESSAGE_STATUS            *pTrFlag;       // set with the error of the last trb sent.
                                                        // if all trb's are sent successfully,
                                                        // then this is I2C_MESSAGE_COMPLETE
} I2C_TR_QUEUE_ENTRY;

/**
  I2C Master Driver Object Type

  @Summary
    Defines the object that manages the i2c master.

  @Description
    This defines the object that manages the sending and receiving of
    i2c master transactions.
  */

typedef struct
{
    /* Read/Write Queue */
    I2C_TR_QUEUE_ENTRY          *pTrTail;       // tail of the queue
    I2C_TR_QUEUE_ENTRY          *pTrHead;       // head of the queue
    I2C_TR_QUEUE_STATUS         trStatus;       // status of the last transaction
    uint8_t                         i2cDoneFlag;    // flag to indicate the current
                                                    // transaction is done
    uint8_t                         i2cErrors;      // keeps track of errors


} I2C_OBJECT ;

/**
  I2C Master Driver State Enumeration

  @Summary
    Defines the different states of the i2c master.

  @Description
    This defines the different states that the i2c master
    used to process transactions on the i2c bus.
*/

typedef enum
{
    S_MASTER_IDLE,
    S_MASTER_RESTART,
    S_MASTER_SEND_ADDR,
    S_MASTER_SEND_DATA,
    S_MASTER_SEND_STOP,
    S_MASTER_ACK_ADDR,
    S_MASTER_RCV_DATA,
    S_MASTER_RCV_STOP,
    S_MASTER_ACK_RCV_DATA,
    S_MASTER_NOACK_STOP,
    S_MASTER_SEND_ADDR_10BIT_LSB,
    S_MASTER_10BIT_RESTART,
    
} I2C_MASTER_STATES;

/**
 Section: Macro Definitions
*/

/* defined for I2C */

#ifndef I2C_CONFIG_TR_QUEUE_LENGTH
        #define I2C_CONFIG_TR_QUEUE_LENGTH 1
#endif

#define I2C_TRANSMIT_REG                       SSP1BUF                 // Defines the transmit register used to send data.
#define I2C_RECEIVE_REG                        SSP1BUF                 // Defines the receive register used to receive data.

// The following control bits are used in the I2C state machine to manage
// the I2C module and determine next states.
#define I2C_WRITE_COLLISION_STATUS_BIT         SSP1CON1bits.WCOL     // Defines the write collision status bit.
#define I2C_MODE_SELECT_BITS                   SSP1CON1bits.SSPM     // I2C Master Mode control bit.
#define I2C_MASTER_ENABLE_CONTROL_BITS         SSP1CON1bits.SSPEN    // I2C port enable control bit.

#define I2C_START_CONDITION_ENABLE_BIT         SSP1CON2bits.SEN      // I2C START control bit.
#define I2C_REPEAT_START_CONDITION_ENABLE_BIT  SSP1CON2bits.RSEN     // I2C Repeated START control bit.
#define I2C_RECEIVE_ENABLE_BIT                 SSP1CON2bits.RCEN     // I2C Receive enable control bit.
#define I2C_STOP_CONDITION_ENABLE_BIT          SSP1CON2bits.PEN      // I2C STOP control bit.
#define I2C_ACKNOWLEDGE_ENABLE_BIT             SSP1CON2bits.ACKEN    // I2C ACK start control bit.
#define I2C_ACKNOWLEDGE_DATA_BIT               SSP1CON2bits.ACKDT    // I2C ACK data control bit.
#define I2C_ACKNOWLEDGE_STATUS_BIT             SSP1CON2bits.ACKSTAT  // I2C ACK status bit.

#define I2C_7bit    true
/**
 Section: Local Functions
*/

void I2C_FunctionComplete(void);
void I2C_Stop(I2C_MESSAGE_STATUS completion_code);

/**
 Section: Local Variables
*/

static I2C_TR_QUEUE_ENTRY                  i2c_tr_queue[I2C_CONFIG_TR_QUEUE_LENGTH];
static I2C_OBJECT                          i2c_object;
//static I2C_MASTER_STATES                   i2c_state = S_MASTER_IDLE;
//static uint8_t                                 i2c_trb_count = 0;
//
////static I2C_TRANSACTION_REQUEST_BLOCK       *p_i2c_trb_current = NULL;
//static I2C_TR_QUEUE_ENTRY                  *p_i2c_current = NULL;


/**
  Section: Driver Interface
*/


void I2C_Initialize(void)
{
    i2c_object.pTrHead = i2c_tr_queue;
    i2c_object.pTrTail = i2c_tr_queue;
    i2c_object.trStatus.s.empty = true;
    i2c_object.trStatus.s.full = false;

    i2c_object.i2cErrors = 0;

    // BF RCinprocess_TXcomplete; UA dontupdate; SMP Standard Speed; P stopbit_notdetected; S startbit_notdetected; R_nW write_noTX; CKE Idle to Active; D_nA lastbyte_address; 
    SSP1STAT = 0x80;
    // SSPEN enabled; WCOL no_collision; SSPOV no_overflow; CKP Idle:Low, Active:High; SSPM FOSC/4_SSPxADD; 
    SSP1CON1 = 0x28;
    // BOEN disabled; AHEN disabled; SBCDE disabled; SDAHT 100ns; DHEN disabled; ACKTIM ackseq; PCIE disabled; SCIE disabled; 
    SSP1CON3 = 0x00;
    // Baud Rate Generator Value: SSPADD 9;   
    SSP1ADD = 0x09;

    /* Byte sent or received */
    // clear the master interrupt flag
    PIR1bits.SSPIF = 0;
    // enable the master interrupt
    //PIE1bits.SSPIE = 1;
    
}

        
//void I2C_Stop(I2C_MESSAGE_STATUS completion_code)
//{
//    // then send a stop
//    I2C_STOP_CONDITION_ENABLE_BIT = 1;
//
//    // make sure the flag pointer is not NULL
//    if (p_i2c_current->pTrFlag != NULL)
//    {
//        // update the flag with the completion code
//        *(p_i2c_current->pTrFlag) = completion_code;
//    }
//
//    // Done, back to idle
//    i2c_state = S_MASTER_IDLE;
//
//}

//void I2C_MasterWrite(
//                                uint8_t *pdata,
//                                uint8_t length,
//                                uint16_t address,
//                                I2C_MESSAGE_STATUS *pflag)
//{
//    static I2C_TRANSACTION_REQUEST_BLOCK   trBlock;
//
//    // check if there is space in the queue
//    if (i2c_object.trStatus.s.full != true)
//    {
//        I2C_MasterWriteTRBBuild(&trBlock, pdata, length, address);
//        I2C_MasterTRBInsert(1, &trBlock, pflag);
//    }
//    else
//    {
//        *pflag = I2C_MESSAGE_FAIL;
//    }
//
//}

//void I2C_MasterRead(
//                                uint8_t *pdata,
//                                uint8_t length,
//                                uint16_t address,
//                                I2C_MESSAGE_STATUS *pflag)
//{
//    static I2C_TRANSACTION_REQUEST_BLOCK   trBlock;
//
//
//    // check if there is space in the queue
//    if (i2c_object.trStatus.s.full != true)
//    {
//        I2C_MasterReadTRBBuild(&trBlock, pdata, length, address);
//        I2C_MasterTRBInsert(1, &trBlock, pflag);
//    }
//    else
//    {
//        *pflag = I2C_MESSAGE_FAIL;
//    }
//
//}

//void I2C_MasterTRBInsert(
//                                uint8_t count,
//                                I2C_TRANSACTION_REQUEST_BLOCK *ptrb_list,
//                                I2C_MESSAGE_STATUS *pflag)
//{
//
//    // check if there is space in the queue
//    if (i2c_object.trStatus.s.full != true)
//    {
//        *pflag = I2C_MESSAGE_PENDING;
//
//        i2c_object.pTrTail->ptrb_list = ptrb_list;
//        i2c_object.pTrTail->count     = count;
//        i2c_object.pTrTail->pTrFlag   = pflag;
//        i2c_object.pTrTail++;
//
//        // check if the end of the array is reached
//        if (i2c_object.pTrTail == (i2c_tr_queue + I2C_CONFIG_TR_QUEUE_LENGTH))
//        {
//            // adjust to restart at the beginning of the array
//            i2c_object.pTrTail = i2c_tr_queue;
//        }
//
//        // since we added one item to be processed, we know
//        // it is not empty, so set the empty status to false
//        i2c_object.trStatus.s.empty = false;
//
//        // check if full
//        if (i2c_object.pTrHead == i2c_object.pTrTail)
//        {
//            // it is full, set the full status to true
//            i2c_object.trStatus.s.full = true;
//        }
//
//    }
//    else
//    {
//        *pflag = I2C_MESSAGE_FAIL;
//    }
//
//    // for interrupt based
//    if (*pflag == I2C_MESSAGE_PENDING)
//    {
//        while(i2c_state != S_MASTER_IDLE);
//        {
//            // force the task to run since we know that the queue has
//            // something that needs to be sent
//            PIR1bits.SSPIF = true;
//        }
//    }   // block until request is complete
//
//}

//void I2C_MasterReadTRBBuild(
//                                I2C_TRANSACTION_REQUEST_BLOCK *ptrb,
//                                uint8_t *pdata,
//                                uint8_t length,
//                                uint16_t address)
//{
//    ptrb->address  = address << 1;
//    // make this a read
//    ptrb->address |= 0x01;
//    ptrb->length   = length;
//    ptrb->pbuffer  = pdata;
//}

//void I2C_MasterWriteTRBBuild(
//                                I2C_TRANSACTION_REQUEST_BLOCK *ptrb,
//                                uint8_t *pdata,
//                                uint8_t length,
//                                uint16_t address)
//{
//    ptrb->address = address << 1;
//    ptrb->length  = length;
//    ptrb->pbuffer = pdata;
//}

//bool I2C_MasterQueueIsEmpty(void)
//{
//    return(i2c_object.trStatus.s.empty);
//}

//bool I2C_MasterQueueIsFull(void)
//{
//    return(i2c_object.trStatus.s.full);
//}        
        
//void I2C_BusCollisionISR( void )
//{
//    // enter bus collision handling code here
//}        
        
        
/**
 End of File
*/
