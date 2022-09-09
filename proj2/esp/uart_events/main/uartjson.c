/*
 * uartjson.c
 *
 *  Created on: 26/07/2022
 *      Author: rafaelpetter
 */

#include "uartjson.h"

#ifndef VARNAME
#define VARNAME

enum VarSize{
    B8=0,
    B16,
    B32
};

struct Parameter{
    char name[64];
    uint8_t byte;
    uint8_t key;
    enum VarSize size;
};

const struct Parameter systemVarNames[]={
	{"decelarationOpen", 1, 0x10, B8},
	{"decelarationClose", 0, 0x10, B8},
	{"motorPower", 1, 0x11, B8},
	{"motorSensitivity", 0, 0x11, B8},
    {"walkTime", 0, 0x12, B8},
    {"autoTimeFullClose", 1, 0x13, B8},
    {"autoTimeWalkClose", 0, 0x13, B8},
    {"photoCellIsON", 1, 0x14, B8},
    {"photoCellInOpen", 0, 0x14, B8},
    {"securityBandIsON", 1, 0x15, B8},
    {"securityBandType", 0, 0x15, B8},
    {"securityBandInOpen", 0, 0x16, B8},
    {"operationMode", 0, 0x17, B8},
    {"flashLightMode", 0, 0x18, B8},
    {"programmingDistance", 0, 0x19, B8},
    {"decelarationSensivity", 0, 0x1A, B8},

    {"homemPresente", 0, 0x1B, B8},
    {"logicDigital", 0, 0x1C, B8},
    {"softStart", 1, 0x1D, B8},
    {"softstop", 0, 0x1D, B8},
    {"ligthTime", 0, 0x1E, B8},
    {"folow_me", 0, 0x1F, B8},
    {"Stopboton", 0, 0x20, B8},
    {"electricBrake", 0, 0x21, B8},
    {"velocityDecelaration", 0, 0x22, B8},
    {"flashRGBMode", 0, 0x23, B8},
    {"Direction_motor", 0, 0x24, B8},
    {"TypeofMotor", 0, 0x25, B8},

    {"positionRemotesFull", 1, 0x26, B8},
    {"positionRemotesWalk", 0, 0x26, B8},
    {"counterMoves", 0, 0x27, B32},
    {"OnlyRollingCode", 0, 0x29, B8},
    {"learningCurrentDecelarationClose", 0, 0x2A, B32},
    {"learningCurrentDecelarationOpen", 0, 0x2C, B32},

    {"learningCurrentNormalClose", 0, 0x2E, B16},
    {"learningCurrentNormalOpen", 0, 0x2F, B16},
    {"learningTimeToOpen", 0, 0x30, B32},
    {"learningTimeToClose", 0, 0x32, B32},

    {"RFFull", 0, 0x34, B8},

    {"photoCellIsObstructed", 1, 0x35, B8},
    {"SecurityBarIsObstructed", 0, 0x35, B8},
    {"FimCurso_CloseIsEnabled", 1, 0x36, B8},
    {"FimCurso_OpenIsEnabled", 0, 0x36, B8},
    {"Statedoorcontrol", 0, 0x37, B8},
    {"PositionActual", 0, 0x38, B32},
    {"PositionIsLost", 1, 0x3A, B8},
    {"StateVersion", 0, 0x3A, B8},

    {"gateDelay", 1, 0x3B, B8},
    {"photoCellType", 0, 0x3B, B8},
    {"gateDelayOpen", 1, 0x3C, B8},
    {"gateNum", 0, 0x3C, B8},

    {"electricLock", 1, 0x3D, B8},
    {"pushInOpen", 0, 0x3D, B8},
    {"pushInClose", 1, 0x3E, B8},
    {"schemeDeceleration", 0, 0x3E, B8},

    {"gate1_time_fullpower_in_open", 0, 0x3F, B16},
    {"gate2_time_fullpower_in_open", 0, 0x40, B16},
    {"gate1_time_fullpower_in_close", 0, 0x41, B16},
    {"gate2_time_fullpower_in_close", 0, 0x42, B16},
    {"gate1_time_softpower_in_open", 0, 0x43, B16},
    {"gate2_time_softpower_in_open", 0, 0x44, B16},
    {"gate1_time_softpower_in_close", 0, 0x45, B16},
    {"gate2_time_softpower_in_close", 0, 0x46, B16},
};
#endif

bool programmer_mode_package(uart_port_t uart_num, bool state){

	//printf("AQUI\n");
	int timeout=TIMEOUT_TIME*10;
	bool progState;
	struct package_t package;
	do{
		init_package(&package);
		package.functioncode=0x02;
		package.address=0x00;
		package.data.data16=0x0000;
		vTaskDelay(5);
		write_package(uart_num, package);	//10 2 0 0 13

		do{
			package=read_package(&packageBuffer);
			timeout--;
			if(!timeout){
				printf("Timeout [request to change programming mode]\n");
				return 0;
			}
			vTaskDelay(1);
		}while(valid_package(package)==FALSE||package.functioncode!=0X02);
		//printf("Package state D1 %x %x %x\n", package.functioncode, package.address, package.data);	//10 2 0 x 13
		progState=package.data.data16;
		//printf("progState %d\n",progState);

		do{
			package=read_package(&packageBuffer);
			timeout--;
			if(!timeout){
				printf("Timeout [acknowledge of changing programming mode]\n");
				return 0;
			}
			vTaskDelay(1);
		}while(valid_package(package)==FALSE||package.functioncode!=0X03);
		//printf("Package ack D2 %x %x %x\n", package.functioncode, package.address, package.data);	//10 3 0 1 13

		if(nack_package(package)){
			printf("Nack [acknowledge failed when changing programming mode]\n");
			return 0;
		}

	}while(progState!=state);
	return 1;
}

void requestjson(uart_port_t uart_num, struct Jsonstring_t* jsonstring){
	struct package_t package1;
	init_package(&package1);

	uint32_t buffer[2];
	int timeout=TIMEOUT_TIME*100;

	package1.functioncode=0x02;
	package1.address=0x00;
	package1.data.data16=0x0000;
	//write_package(uart_num, package2);

	//printf("Package t %x %x %x\n", package1.functioncode, package1.address, package1.data.data16);

	printf("Json\n");
	for(int i=0;i<sizeof(systemVarNames)/sizeof(struct Parameter);i++){
		init_package(&package1);
		package1.functioncode=0x00;
		package1.address=systemVarNames[i].key;
		package1.data.data16=0x0000;
		write_package(uart_num, package1);
		do{
			package1=read_package(&packageBuffer);
			timeout--;
			if(!timeout){
				printf("Timeout [request reading]\n");
				return;
			}
			vTaskDelay(1);
		}while(valid_package(package1)==FALSE||(package1.functioncode!=0X00&&package1.functioncode!=0X03));
		if(package1.functioncode==0x00){
			printf("Variable in the system %d %s\n", i, systemVarNames[i].name);
			switch(systemVarNames[i].size){
			case B8:
				add_integer(jsonstring, systemVarNames[i].name, package1.data.data8[!systemVarNames[i].byte]);
				break;
			case B16:
				add_integer(jsonstring, systemVarNames[i].name, swapped(package1.data.data16));
				break;
			case B32:
				buffer[0]=swapped(package1.data.data16);
				do{
					package1=read_package(&packageBuffer);
					timeout--;
					if(!timeout){
						printf("Timeout [request reading of a 32 bit data]\n");
						return;
					}
					vTaskDelay(1);
				}while(package1.valid==FALSE);
				buffer[1]=swapped(package1.data.data16);
				add_integer(jsonstring, systemVarNames[i].name, (buffer[0]<<16)+buffer[1]);
				break;
			}
			do{
				package1=read_package(&packageBuffer);
				timeout--;
				if(!timeout){
					printf("Timeout [acknowledge reading]\n");
					return;
				}
				vTaskDelay(1);
			}while(valid_package(package1)==FALSE||package1.functioncode!=0X03);
		}
		else{
			printf("Variable not in the system %d %s\n", i, systemVarNames[i].name);
			add_integer(jsonstring, systemVarNames[i].name, 0);
		}
	}
	printf("Done\n");
	return;
}

uint8_t sendjson(uart_port_t uart_num, struct Jsonstring_t* jsonstring){


	int timeout=TIMEOUT_TIME*10;
    char token[NAME_SIZE+NUMSTR_SIZE];
    char name[NAME_SIZE];
    char value[NUMSTR_SIZE];

    uint16_t mask;

    struct package_t package;


	enum jsontype_t jsontype;


	for(int i=0;i<json_sizefirstscope(jsonstring);i++){
		timeout=TIMEOUT_TIME*10;
		//printf("Disassembling .json: %d/%d-----------------------------------\n",i+1,json_sizefirstscope(jsonstring));

		json_taketoken(jsonstring, i, token);
		json_dividetoken(token, name, value, &jsontype);
		//printf("Disassembled\n");
		printf("Token %s\n",token);
		//printf("Name %s Valor %x\n", name, (uint32_t)atoi(value));

		if(jsontype==JSON_INTEGER_T){
			for(uint8_t j=0;j<(sizeof(systemVarNames)/sizeof(char*));j++){
				if(strcmp(name, systemVarNames[j].name)==0){
					switch(systemVarNames[j].size){
					case B8:
						//printf("B8\n");

						init_package(&package);
						package.functioncode=0x00;
						package.address=systemVarNames[j].key;
						package.data.data16=0x0000;
						vTaskDelay(pdMS_TO_TICKS(5));
						write_package(uart_num, package);
						//printf("Package t %x %x %x %x %x\n", package.functioncode, package.address, package.data, i, j);

						do{
							package=read_package(&packageBuffer);
							timeout--;
							if(!timeout){
								printf("Timeout [request reading of a 8 bit data to mask]\n");
								return 0;
							}
							vTaskDelay(pdMS_TO_TICKS(1));
						}while(valid_package(package)==FALSE||(package.functioncode!=0X00&&package.functioncode!=0X03));
						if(package.functioncode==0X03)
							break;
						mask=package.data.data16;
						do{
							package=read_package(&packageBuffer);
							timeout--;
							if(!timeout){
								printf("Timeout [acknowledge reading of a 8 bit data to mask]\n");
								return 0;
							}
							vTaskDelay(pdMS_TO_TICKS(1));
						}while(valid_package(package)==FALSE||package.functioncode!=0X03);
						//printf("Package R %x %x %x %x %x\n", package.functioncode, package.address, package.data, i, j);

						package.address=systemVarNames[j].key;
						package.data.data16=mask;
						package.data.data8[!systemVarNames[j].byte]=(uint8_t)atoi(value);
						package.functioncode=0x01;
						//printf("SysVar %s %x %x %x\n", systemVarNames[j].name, systemVarNames[j].key, systemVarNames[j].byte, systemVarNames[j].size);
						//printf("Package R %x %x %x %x %x\n", package.functioncode, package.address, package.data, i, j);
						programmer_mode_package(uart_num, TRUE);
						//printf("CHANGED\n");

						vTaskDelay(pdMS_TO_TICKS(5));
						write_package(uart_num, package);
						do{
							package=read_package(&packageBuffer);
							timeout--;
							if(!timeout){
								printf("Timeout [update write 8 bit]\n");
								return 0;
							}
							vTaskDelay(pdMS_TO_TICKS(1));
						}while(valid_package(package)==FALSE||package.functioncode!=0X03);
						printf("Set %s to %x\n", systemVarNames[j].name, (uint8_t)atoi(value));
						//printf("CHANGED\n");
						programmer_mode_package(uart_num, FALSE);

						//printf("END\n");
						break;
					case B16:
						//printf("B16\n");
						init_package(&package);
						package.functioncode=0x01;
						package.address=systemVarNames[j].key;
						package.data.data16=swapped((uint16_t)atoi(value));
						programmer_mode_package(uart_num, TRUE);
						vTaskDelay(pdMS_TO_TICKS(5));
						write_package(uart_num, package);
						do{
							package=read_package(&packageBuffer);
							timeout--;
							if(!timeout){
								printf("Timeout [update write 16 bit]\n");
								return 0;
							}
							vTaskDelay(pdMS_TO_TICKS(1));
						}while(valid_package(package)==FALSE||package.functioncode!=0X03);
						printf("Set %s to %x\n", systemVarNames[j].name, (uint16_t)atoi(value));
						programmer_mode_package(uart_num, FALSE);
						break;
					case B32:
						//printf("B32\n");
						init_package(&package);
						package.functioncode=0x01;
						package.address=systemVarNames[j].key;
						package.data.data16=atoi(value)>>16;
						programmer_mode_package(uart_num, TRUE);
						vTaskDelay(pdMS_TO_TICKS(5));
						write_package(uart_num, package);
						do{
							package=read_package(&packageBuffer);
							timeout--;
							if(!timeout){
								printf("Timeout [update write 32 bit(1)]\n");
								return 0;
							}
							vTaskDelay(pdMS_TO_TICKS(1));
						}while(valid_package(package)==FALSE||package.functioncode!=0X03);
						if(package.data.data16==0X0000)
							break;
						programmer_mode_package(uart_num, FALSE);
						package.address=systemVarNames[j].key+1;
						package.data.data16=atoi(value);
						programmer_mode_package(uart_num, TRUE);
						vTaskDelay(pdMS_TO_TICKS(5));
						write_package(uart_num, package);
						do{
							package=read_package(&packageBuffer);
							timeout--;
							if(!timeout){
								printf("Timeout [update write 32 bit(2)]\n");
								return 0;
							}
							vTaskDelay(pdMS_TO_TICKS(1));
						}while(valid_package(package)==FALSE||package.functioncode!=0X03);
						printf("Set %s to %x\n", systemVarNames[j].name, atoi(value));
						programmer_mode_package(uart_num, FALSE);
						break;
					}
					break;
				}
				vTaskDelay(pdMS_TO_TICKS(1));
			}
		}
	}
	printf("Done\n");

	return 1;

}
