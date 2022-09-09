/*
 * uartjson.c
 *
 *  Created on: 26/07/2022
 *      Author: rafaelpetter
 */

#include "uartjson.h"

#ifndef VARNAME
#define VARNAME
char* varname[]={
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"decelarationOpen",
		"decelarationClose",
		"motorPower",
		"motorSensitivity",
		"walkTime",
		"null",
		"autoTimeFullClose",
		"autoTimeWalkClose",
		"photoCellIsON",
		"photoCellInOpen",
		"securityBandIsON",
		"securityBandType",
		"securityBandInOpen",
		"null",
		"operationMode",
		"null",
		"flashLightMode",
		"null",
		"programmingDistance",
		"null",
		"decelarationSensivity",
		"null",
		"homemPresente",
		"null",
		"logicDigital",
		"null",
		"softStart",
		"softstop",
		"ligthTime",
		"null",
		"folow_me",
		"null",
		"Stopboton",
		"null",
		"electricBrake",
		"null",
		"velocityDecelaration",
		"null",
		"flashRGBMode",
		"null",
		"Direction_motor",
		"null",
		"TypeofMotor",
		"null",
		"positionRemotesFull",
		"positionRemotesWalk",
		"counterMoves",
		"counterMoves",
		"counterMoves",
		"counterMoves",
		"OnlyRollingCode",
		"null",
		"learningCurrentDecelarationClose",
		"learningCurrentDecelarationClose",
		"learningCurrentDecelarationClose",
		"learningCurrentDecelarationClose",
		"learningCurrentDecelarationOpen",
		"learningCurrentDecelarationOpen",
		"learningCurrentDecelarationOpen",
		"learningCurrentDecelarationOpen",
		"learningCurrentNormalClose",
		"learningCurrentNormalClose",
		"learningCurrentNormalOpen",
		"learningCurrentNormalOpen",
		"learningTimeToOpen",
		"learningTimeToOpen",
		"learningTimeToOpen",
		"learningTimeToOpen",
		"learningTimeToClose",
		"learningTimeToClose",
		"learningTimeToClose",
		"learningTimeToClose",

		"RFFull",
		"null",

		"photoCellIsObstructed",
		"SecurityBarIsObstructed",
		"FimCurso_CloseIsEnabled",
		"FimCurso_OpenIsEnabled",
		"Statedoorcontrol",
		"null",
		"PositionActual",
		"PositionActual",
		"PositionActual",
		"PositionActual",
		"PositionIsLost",
		"StateVersion",
		"null",
		"null"
};
#endif

void requestjson(uart_port_t uart_num, struct Jsonstring_t* jsonstring){
	struct package_t package1, package2;
	init_package(&package1);
	init_package(&package2);
	package2.functioncode=0x00;
	uint32_t var4bytes=0;
	bool var4bytesflag=FALSE;
	int timeout=TIMEOUT_TIME;
	int i=0x00;

	package1.functioncode=0x12;
	package1.address=0x00;
	package1.data.data16=0x0000;
	package2.address=0;
	write_package(uart_num, package2);
	while(1){
		if(i>0x3A){
			break;
		}
		package1=read_package(&packageBuffer);
		if(package1.valid==TRUE){
			if(package1.functioncode==0x03){
				if(package1.data.data16!=0x0000){
					if(i>0x3A){
						break;
					}
				}
			}
			else if(package1.functioncode!=0x00){

			}
			else{
				printf("Building .json: %d/%d\n", i, 0x3A);
				package2.address=i+1;
				write_package(uart_num, package2);
				//null
				if(!strcmp(varname[i*2],"null")&&!strcmp(varname[i*2+1],"null")){
				}
				//two variables same address
				else if(strcmp(varname[i*2],varname[i*2+1])){
					if(strcmp(varname[i*2],"null"))
						add_integer(jsonstring, varname[i*2], package1.data.data8[1]);
					if(strcmp(varname[i*2+1],"null"))
						add_integer(jsonstring, varname[i*2+1], package1.data.data8[0]);
				}
				//only one variable in the address
				else{
					//first variable
					if(i==0)
						//only 2 bytes
						if(strcmp(varname[i*2],varname[i*2+2])){
							add_integer(jsonstring, varname[i*2], swapped(package1.data.data16));
						}
						//4 bytes forward
						else{
							var4bytes+=((uint32_t)package1.data.data8[1])+((uint32_t)package1.data.data8[0]<<8);
							add_integer(jsonstring, varname[i*2], var4bytes);
							var4bytesflag=FALSE;
						}
					//not first variable
					else
						//only 2 bytes
						if(strcmp(varname[i*2],varname[i*2+2])&&strcmp(varname[i*2],varname[i*2-1])){
							add_integer(jsonstring, varname[i*2], swapped(package1.data.data16));
						}
						//4 bytes forward or backward
						else{
							//4 bytes forward
							if(var4bytesflag==FALSE){
								var4bytes=0x00000000;
								var4bytes+=((uint32_t)package1.data.data8[1]<<16)+((uint32_t)package1.data.data8[0]<<24);
								var4bytesflag=TRUE;

							}
							//4 bytes backward
							else{
								var4bytes+=((uint32_t)package1.data.data8[1])+((uint32_t)package1.data.data8[0]<<8);
								add_integer(jsonstring, varname[i*2], var4bytes);
								var4bytesflag=FALSE;

							}
						}
				}
				i++;
			}
		}
		else{
			printf("Waiting...\n");
			if(timeout==0){
				printf("Timeout\n");
				return;
			}
			timeout--;
		}
		vTaskDelay(5);
	}
	printf("Done\n");
	return;
}

uint8_t sendjson(uart_port_t uart_num, struct Jsonstring_t* jsonstring){


    char token[NAME_SIZE+NUMSTR_SIZE];
    char name[NAME_SIZE];
    char value[NUMSTR_SIZE];

    uint16_t mask;

    struct package_t package;


	enum jsontype_t jsontype;

	for(int i=0;i<json_sizefirstscope(jsonstring);i++){
		printf("Disassembling .json: %d/%d\n",i+1,json_sizefirstscope(jsonstring));

		json_taketoken(jsonstring, i, token);
		json_dividetoken(token, name, value, &jsontype);


		if(jsontype==JSON_INTEGER_T){
			for(uint8_t j=0;j<sizeof(varname)/sizeof(char*);j++){
				if(strcmp(name, varname[j])==0){

					//mask
					init_package(&package);
					package.functioncode=0x00;
					package.address=j/2;
					package.data.data16=0x0000;
					write_package(uart_num, package);
					while(1){
						package=read_package(&packageBuffer);
						if(package.valid==TRUE&&package.functioncode==0x00){
							mask=package.data.data16;
							break;
						}
					}

					//allow write
					package.functioncode=0x02;
					write_package(uart_num, package);
					while(1){
						package=read_package(&packageBuffer);
						if(package.valid==TRUE&&package.functioncode==0x02){
							if(package.data.data16==0x0000){
								write_package(uart_num, package);
								continue;
							}
							break;
						}
					}

					//write
					if(strcmp(varname[j], varname[j+1])){
						if(j%2==1){
							package.data.data16=(atoi(value)+(mask&0xFF00));
							package.address=j/2;
							package.functioncode=0x01;
							write_package(uart_num, package);
						}
						else{
							package.data.data16=((atoi(value)<<8)+(mask&0x00FF));
							package.address=j/2;
							package.functioncode=0x01;
							write_package(uart_num, package);
						}
					}
					else
						if(strcmp(name, varname[j+2])){
							package.data.data16=swapped((uint16_t)atoi(value));
							package.address=j/2;
							package.functioncode=0x01;
							write_package(uart_num, package);
						}
						else{
							package.data.data16=(uint32_t)atoi(value);
							package.address=j/2;
							package.functioncode=0x01;
							write_package(uart_num, package);
							package.data.data16=(uint32_t)(atoi(value)>>16);
							package.address=j/2;
							package.functioncode=0x01;
							write_package(uart_num, package);
						}


					//disallow write
					package.functioncode=0x02;
					write_package(uart_num, package);

					while(1){
						package=read_package(&packageBuffer);
						if(package.valid==TRUE&&package.functioncode==0x02){
							if(package.data.data16!=0x0000){
								write_package(uart_num, package);
								continue;
							}
							break;
						}
					}
					break;
				}
				vTaskDelay(pdMS_TO_TICKS(50));
			}
		}
	}
	printf("Done\n");

	return 1;

}
