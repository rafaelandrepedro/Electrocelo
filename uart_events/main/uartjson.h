/*
 * uartjson.h
 *
 *  Created on: 22/07/2022
 *      Author: rafael pedro
 */

#ifndef MAIN_UARTJSON_H_
#define MAIN_UARTJSON_H_

#define TIMEOUT_TIME 20

#include "jsonlib.h"
#include "eusartpackage.h"

extern struct packagebuffer_t packageBuffer;

//variables with multiple bytes shall occupy multiple indexes


void requestjson(uart_port_t uart_num, struct Jsonstring_t* jsonstring);

uint8_t sendjson(uart_port_t uart_num, struct Jsonstring_t* jsonstring);

#endif /* MAIN_UARTJSON_H_ */
