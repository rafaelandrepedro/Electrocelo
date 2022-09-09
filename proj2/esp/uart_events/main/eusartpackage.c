/*
 * File:   eusartpackage.c
 * Author: rafael pedro
 *
 * @version v1.1
 *
 * Created on July 14, 2022, 10:12 AM
 */

#include "eusartpackage.h"

#define PACKAGE_COMMUNICATION_DEVICE 2

void init_package(struct package_t* package){
	package->startbyte=STARTBYTE;
	package->endbyte=ENDBYTE;
	package->valid=TRUE;
}

bool valid_package(const struct package_t package){
	return package.valid;
}

bool ack_package(const struct package_t package){
	return (package.functioncode==0x03&&package.data.data16!=0x0000);
}

bool nack_package(const struct package_t package){
	return (package.functioncode==0x03&&package.data.data16==0x0000);
}

#if PACKAGE_COMMUNICATION_DEVICE==1
	struct package_t read_package(){
		struct package_t package;
		//verify start byte
		if(EUSART1_Read()!=STARTBYTE){
			package.valid=FALSE;
			return package;
		}
		else
			package.startbyte=STARTBYTE;

		//read package
		package.functioncode=EUSART1_Read();
		package.address=EUSART1_Read();
		package.data.data8[0]=EUSART1_Read();
		package.data.data8[1]=EUSART1_Read();

		//verify end byte
		if(EUSART1_Read()!=ENDBYTE){
			package.valid=FALSE;
			return package;
		}
		else
			package.endbyte=ENDBYTE;

		//valid package
		package.valid=TRUE;
		return package;
	}

	void write_package(const struct package_t package){
		//verify if its valid
		if(package.valid==FALSE)
			return;

		//send package
		EUSART1_Write(package.startbyte);
		EUSART1_Write(package.functioncode);
		EUSART1_Write(package.address);
		EUSART1_Write(package.data.data8[0]);
		EUSART1_Write(package.data.data8[1]);
		EUSART1_Write(package.endbyte);

		return;
	}
#endif

#if PACKAGE_COMMUNICATION_DEVICE==2

	struct package_t read_package(struct packagebuffer_t* packageBuffer){
		struct package_t package;
		package.valid=read_buffer(packageBuffer, &package);
		return package;
	}

	void write_package(uart_port_t uart_num, const struct package_t package){
		//verify if its valid
		if(package.valid==FALSE)
			return;

		//send package
		uart_write_bytes(uart_num, (const char*) &(package.startbyte), 1);	//print
		uart_write_bytes(uart_num, (const char*) &(package.functioncode), 1);	//print
		uart_write_bytes(uart_num, (const char*) &(package.address), 1);			//print
		uart_write_bytes(uart_num, (const char*) &(package.data.data8[1]), 1);	//print
		uart_write_bytes(uart_num, (const char*) &(package.data.data8[0]), 1);	//print
		uart_write_bytes(uart_num, (const char*) &(package.endbyte), 1);	//print

		return;
	}
#endif

void init_packageBuffer(struct packagebuffer_t* packageBuffer){

	packageBuffer->readPackageIndex=0;
	packageBuffer->writeByteIndex=0;
	packageBuffer->writePackageIndex=0;

}


void add_buffer(struct packagebuffer_t* packageBuffer, uint8_t byte){
	if((packageBuffer->writeByteIndex==0&&byte!=STARTBYTE)||(packageBuffer->writeByteIndex==5&&byte!=ENDBYTE)){		//STARTBYTE or ENDBYTE failed
		packageBuffer->writeByteIndex=0;
		return;
	}
	if(packageBuffer->readPackageIndex==(packageBuffer->writePackageIndex+1)%BUFFER_SIZE)							//full
		return;
	switch(packageBuffer->writeByteIndex){
	case 0://startbyte
		packageBuffer->buffer[packageBuffer->writePackageIndex].startbyte=STARTBYTE;
		break;
	case 1://functioncode
		packageBuffer->buffer[packageBuffer->writePackageIndex].functioncode=byte;
		break;
	case 2://address
		packageBuffer->buffer[packageBuffer->writePackageIndex].address=byte;
		break;
	case 3://data[1]
		packageBuffer->buffer[packageBuffer->writePackageIndex].data.data8[1]=byte;
		break;
	case 4://data[0]
		packageBuffer->buffer[packageBuffer->writePackageIndex].data.data8[0]=byte;
		break;
	case 5://endbyte
		packageBuffer->buffer[packageBuffer->writePackageIndex].endbyte=ENDBYTE;
		packageBuffer->buffer[packageBuffer->writePackageIndex].valid=TRUE;
		packageBuffer->writePackageIndex=(packageBuffer->writePackageIndex+1)%BUFFER_SIZE;
		break;
	}
	packageBuffer->writeByteIndex=(packageBuffer->writeByteIndex+1)%6;
	return;

}

int read_buffer(struct packagebuffer_t* packageBuffer, struct package_t* package){

	if(!bufferIsEmpty(*packageBuffer)){
		*package=packageBuffer->buffer[packageBuffer->readPackageIndex];
		packageBuffer->readPackageIndex=(packageBuffer->readPackageIndex+1)%BUFFER_SIZE;
		return 1;
	}
	return 0;
}

int bufferIsEmpty(const struct packagebuffer_t packageBuffer){

	return packageBuffer.readPackageIndex==packageBuffer.writePackageIndex;

}
