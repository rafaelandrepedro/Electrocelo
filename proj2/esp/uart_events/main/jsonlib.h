/*
 * json.h
 *
 *  Created on: 22/07/2022
 *      Author: rafael pedro
 */

#ifndef MAIN_JSONLIB_H_
#define MAIN_JSONLIB_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define JSON_SIZE 256*8
#define NAME_SIZE 64
#define NUMSTR_SIZE 10

struct Jsonstring_t {
    char json[JSON_SIZE];
};

enum jsontype_t {
    JSON_NULL_T = -1,
    JSON_PRIMITIVE_T = 0,
    JSON_OBJECT_T = 1,
    JSON_ARRAY_T = 2,
    JSON_STRING_T = 3,
    JSON_INTEGER_T = 4,
    JSON_FLOAT_T = 5
};

enum primitivetype_t {
    PRIMITIVE_FALSE = 0,
    PRIMITIVE_TRUE = 1,
    PRIMITIVE_NULL = 2
};

/*
 * @brief resets the json string with an empty scope
 * @param jsonstring the json string address
 */
void init_json(struct Jsonstring_t* jsonstring);

/*
 * @brief returns the number of elements in all scopes of the json string
 * @param jsonstring the json string
 */
uintmax_t json_size(const struct Jsonstring_t jsonstring);

/*
 * @brief returns the number of elements in the first scope of the json string
 * @param jsonstring the json string address
 */
int json_sizefirstscope(const struct Jsonstring_t* jsonstring);

/*
 * @brief returns a token from the json string
 * @param jsonstring the json string address
 * @param pos position of the token
 * @param token the taken token
 */
void json_taketoken(const struct Jsonstring_t* jsonstring, uintmax_t pos, char* token);

/*
 * @brief divides a json token into name + value
 * @param token the token that is divided
 * @param name the name of the parameter
 * @param value the value of the parameter (string format)
 * @param jsonstring the json string address
 * @return
 */
void json_dividetoken(char* token, char* name, char* value, enum jsontype_t* jsontype);

/*
 * @brief Adds a primitive value to the json string
 * @param jsonstring the json string address
 * @param name the name of the parameter
 * @param token the value of the token
 * @return
 */
void add_primitive(struct Jsonstring_t* jsonstring, const char* name, const enum primitivetype_t token);

/*
 * @brief Adds an object to the json string
 * @param jsonstring the json string address
 * @param name the name of the parameter
 * @param token the value of the token
 * @return
 */
void add_object(struct Jsonstring_t* jsonstring, const char* name, const struct Jsonstring_t token);

/*
 * @brief Adds a string to the json string
 * @param jsonstring the json string address
 * @param name the name of the parameter
 * @param token the value of the token
 * @return
 */
void add_string(struct Jsonstring_t* jsonstring, const char* name, const char* token);

/*
 * @brief Adds a integer value to the json string
 * @param jsonstring the json string address
 * @param name the name of the parameter
 * @param token the value of the token
 * @return
 */
void add_integer(struct Jsonstring_t* jsonstring, const char* name, const uintmax_t token);

/*
 * @brief Adds a float value to the json string
 * @param jsonstring the json string address
 * @param name the name of the parameter
 * @param token the value of the token
 * @return
 */
void add_float(struct Jsonstring_t* jsonstring, const char* name, const float token);




#endif /* MAIN_JSONLIB_H_ */
