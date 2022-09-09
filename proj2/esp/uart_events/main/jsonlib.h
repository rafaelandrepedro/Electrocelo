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

void init_json(struct Jsonstring_t* jsonstring);

uintmax_t json_size(const struct Jsonstring_t jsonstring);

int json_sizefirstscope(const struct Jsonstring_t* jsonstring);

void json_taketoken(const struct Jsonstring_t* jsonstring, uintmax_t pos, char* token);

void json_dividetoken(char* token, char* name, char* value, enum jsontype_t* jsontype);

void add_primitive(struct Jsonstring_t* jsonstring, const char* name, const enum primitivetype_t token);

void add_object(struct Jsonstring_t* jsonstring, const char* name, const struct Jsonstring_t token);

void add_string(struct Jsonstring_t* jsonstring, const char* name, const char* token);

void add_integer(struct Jsonstring_t* jsonstring, const char* name, const uintmax_t token);

void add_float(struct Jsonstring_t* jsonstring, const char* name, const float token);




#endif /* MAIN_JSONLIB_H_ */
