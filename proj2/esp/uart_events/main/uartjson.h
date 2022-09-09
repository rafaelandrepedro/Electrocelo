/*
 * uartjson.h
 *
 *  Created on: 22/07/2022
 *      Author: rafael pedro
 */

#ifndef MAIN_UARTJSON_H_
#define MAIN_UARTJSON_H_

#define TIMEOUT_TIME 500

#include "jsonlib.h"
#include "eusartpackage.h"

extern struct packagebuffer_t packageBuffer;

//variables with multiple bytes shall occupy multiple indexes

/*
 * @brief creates and sends a package that toggles the programmer mode to a desired state (from an uart port)
 * @param uart_num the number of the uart used
 * @param state desired programming state
 */
bool programmer_mode_package(uart_port_t uart_num, bool state);

/*
 * @brief requests a json file from the uart (assembles the structure)
 * @param uart_num the number of the uart used
 * @param jsonstring the json string address
 */
void requestjson(uart_port_t uart_num, struct Jsonstring_t* jsonstring);

/*
 * @brief sends a json file to the uart (disassembles the structure)
 * @param uart_num the number of the uart used
 * @param jsonstring the json string address
 * @return 0x00->fail 0x01->success
 */
uint8_t sendjson(uart_port_t uart_num, struct Jsonstring_t* jsonstring);

#endif /* MAIN_UARTJSON_H_ */
