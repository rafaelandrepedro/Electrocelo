/*
 * eusartpackage.h
 *
 *  Created on: 22/07/2022
 *      Author: rafael pedro
 */



#ifndef MAIN_EUSARTPACKAGE_H_
#define MAIN_EUSARTPACKAGE_H_


#ifdef	__cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "driver/uart.h"

#define STARTBYTE 0x0A
#define ENDBYTE 0x0D
#ifndef TRUE
#define TRUE 1
#endif  /* TRUE */
#ifndef FALSE
#define FALSE 0
#endif	/* FALSE */

#define swapped(num) ((uint16_t)((uint16_t)(num)>>8) | (uint16_t)((uint16_t)(num)<<8))

#define PACKAGE_COMMUNICATION_DEVICE 2

/*
 *\brief union that allows the data to be read in separated bytes or in a 16 bit integer
 */
union packagedata_t{
    uint16_t data16;
    uint8_t data8[2];
};

/*
 *\brief function operation modes
 */
enum functioncode_t{
    READ=0,
    WRITE=1,
    PROGRAMMING_ENABLE=2,
    CONFIRM=3,
    NUM_COMMANDS_F=4,
    NUM_EMPTY_COMMANDS_F=5,
    OCCUPIED_POS_F=6,
    EMPTY_POS_F=7,
    SAVE_COMMAND_F=8,
    ERASE_COMMAND_F=9,
    READ_SERIAL_F=10,
    NUM_COMMANDS_W=11,
    NUM_EMPTY_COMMANDS_W=12,
    OCCUPIED_POS_W=13,
    EMPTY_POS_W=14,
    SAVE_COMMAND_W=15,
    ERASE_COMMAND_W=16,
    READ_SERIAL_W=17
};

/*
 *\brief package that contains data for eusart transmission
 */
struct package_t{
    //public
    enum functioncode_t functioncode;
    uint8_t address;
    union packagedata_t data;


    //private
    uint8_t startbyte;
    uint8_t endbyte;
    bool valid;
};

#define BUFFER_SIZE 8

struct packagebuffer_t{
	struct package_t buffer[BUFFER_SIZE];
	uint8_t writeByteIndex;
	uint8_t writePackageIndex;
	uint8_t readPackageIndex;
};

/*
 *\brief sets the start and end bytes and validates the package
 */
void init_package(struct package_t* package);

/*
 *\brief verifies if the package is valid
 */
bool valid_package(const struct package_t package);

bool ack_package(const struct package_t package);

bool nack_package(const struct package_t package);

#if DIRECT_PACKAGE_COMMUNICATION==1
	/*
	 *\brief reads a package
	 */
	struct package_t read_package();

	/*
	 *\brief writes a package
	 */
	void write_package(const struct package_t package);
#endif

#if PACKAGE_COMMUNICATION_DEVICE==2

	struct package_t read_package(struct packagebuffer_t* packageBuffer);

	void write_package(uart_port_t uart_num, const struct package_t package);

#endif

void in(void);

void init_packageBuffer(struct packagebuffer_t* packageBuffer);

void add_buffer(struct packagebuffer_t* packageBuffer, uint8_t byte);

int read_buffer(struct packagebuffer_t* packageBuffer, struct package_t* package);

int bufferIsEmpty(const struct packagebuffer_t packageBuffer);



#ifdef	__cplusplus
}
#endif

#endif /* MAIN_EUSARTPACKAGE_H_ */
