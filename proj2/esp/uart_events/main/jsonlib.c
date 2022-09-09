/*
 * json.c
 *
 *  Created on: 26/07/2022
 *      Author: rafaelpetter
 */

#include <jsonlib.h>

void init_json(struct Jsonstring_t* jsonstring) {
    strcpy(jsonstring->json, "{\n}");
}

uintmax_t json_size(const struct Jsonstring_t jsonstring) {
    if (strlen(jsonstring.json) == 3)
        return 0;
    const char* ch;
    ch = jsonstring.json;
    uintmax_t scope = 0;
    uintmax_t size = 0;
    while (*ch != '\0') {
        if (*ch == '{')
            scope++;
        if (*ch == '}')
            scope--;
        if (*ch == ',' || *ch == '{')
            size++;
        ch++;
    }
    return size;
}

int json_sizefirstscope(const struct Jsonstring_t* jsonstring) {
    if (strlen((*jsonstring).json) == 3)
        return 0;
    const char* ch;
    ch = jsonstring->json;
    int scope = 0;
    int size = 0;

    while (*ch != '\0') {
        if (*ch == '{')
            scope++;
        if (*ch == '}')
            scope--;
        if ((*ch == ',' || *ch == '{')&& scope==1)
            size++;
        ch++;
    }

    return size;
}

void json_taketoken(const struct Jsonstring_t* jsonstring, uintmax_t pos, char* token) {
    if (pos + 1 > json_sizefirstscope(jsonstring))
        return;
    const char* ch;
    ch = (*jsonstring).json;
    uintmax_t scope = 1;
    while (*ch != '{') {
        ch++;
    }
    ch++;
    while (pos != 0) {
        if (*ch == '{')
            scope++;
        if (*ch == '}')
            scope--;
        if ((*ch == ',' || *ch == '{') && scope == 1)
            pos--;
        ch++;
    }
    ch++;
    uintmax_t i = 0;
    for (; (*ch != ',' || scope != 1) && scope != 0; i++, ch++) {
        if (*ch == '{')
            scope++;
        if (*ch == '}')
            scope--;
        token[i] = *ch;
    }
    if(token[i-1]=='}'){
        token[i-2] = '\0';
    }
    else
        token[i] = '\0';
    return;
}

void json_dividetoken(char* token, char* name, char* value, enum jsontype_t* jsontype) {
    const char* ch;
    ch = token + 1;
    char marker = '\0';
    int floattype = 0;
    *jsontype = JSON_NULL_T;
    uintmax_t i = 0;
    for (; *ch != ':'; i++, ch++){
        if (*ch == '\n')
            ch++;
        name[i] = *ch;
    }
    name[i-1] = '\0';
    ch++;

    if (*ch == '\"') {
        marker = '\"';
        ch++;
    }

    if (*ch == '{') {
        *jsontype = JSON_OBJECT_T;
    }

    i = 0;
    for (; ch != token + strlen(token); i++, ch++) {
        if (*ch == '\n')
            ch++;
    	if (*ch == ','||*ch == '}')
    	    break;
        value[i] = *ch;
        if (*ch == '.')
            floattype = 1;
    }

    if (marker!='\0')
        value[i - 1] = '\0';
    else
        value[i] = '\0';


    if(*jsontype==JSON_NULL_T){
        if (marker!='\0')
            if(marker=='\"')
                if (strcmp(value, "TRUE")==0 || strcmp(value, "FALSE") == 0 || strcmp(value, "NULL") == 0)
                    *jsontype = JSON_PRIMITIVE_T;
                else
                    *jsontype = JSON_STRING_T;
            else
                *jsontype = JSON_ARRAY_T;
        else
            if (floattype)
                *jsontype = JSON_FLOAT_T;
            else
                *jsontype = JSON_INTEGER_T;
    }


}

void add_primitive(struct Jsonstring_t* jsonstring, const char* name, const enum primitivetype_t token) {

    uint32_t len = strlen(jsonstring->json);
    char newjson[JSON_SIZE];
    strncpy(newjson, jsonstring->json, len - 1);
    if (jsonstring->json[len - 3] == '{') {
        newjson[len - 1] = '\0';
    }
    else {
        newjson[len - 2] = ',';
        newjson[len - 1] = '\n';
        newjson[len] = '\0';
    }
    //<token>
        //generic
    strcat(newjson, "\"");
    strcat(newjson, name);
    strcat(newjson, "\":");
    //specific
    strcat(newjson, "\"");
    switch (token) {
    case PRIMITIVE_FALSE:
        strcat(newjson, "FALSE");
        break;
    case PRIMITIVE_TRUE:
        strcat(newjson, "TRUE");
        break;
    case PRIMITIVE_NULL:
        strcat(newjson, "NULL");
        break;
    };

    strcat(newjson, "\"\n");
    //<\token>
    strcat(newjson, jsonstring->json + len - 1);
    strcpy(jsonstring->json, newjson);
}

void add_object(struct Jsonstring_t* jsonstring, const char* name, const struct Jsonstring_t token) {

    uint32_t len = strlen(jsonstring->json);
    char newjson[JSON_SIZE];
    strncpy(newjson, jsonstring->json, len - 1);
    if (jsonstring->json[len - 3] == '{') {
        newjson[len - 1] = '\0';
    }
    else {
        newjson[len - 2] = ',';
        newjson[len - 1] = '\n';
        newjson[len] = '\0';
    }
    //<token>
        //generic
    strcat(newjson, "\"");
    strcat(newjson, name);
    strcat(newjson, "\":");
    //specific
    strcat(newjson, token.json);
    strcat(newjson, "\n");
    //<\token>
    strcat(newjson, jsonstring->json + len - 1);
    strcpy(jsonstring->json, newjson);
}

void add_string(struct Jsonstring_t* jsonstring, const char* name, const char* token) {

    uint32_t len = strlen(jsonstring->json);
    char newjson[JSON_SIZE];
    strncpy(newjson, jsonstring->json, len - 1);
    if (jsonstring->json[len - 3] == '{') {
        newjson[len - 1] = '\0';
    }
    else {
        newjson[len - 2] = ',';
        newjson[len - 1] = '\n';
        newjson[len] = '\0';
    }
    //<token>
        //generic
    strcat(newjson, "\"");
    strcat(newjson, name);
    strcat(newjson, "\":");
    //specific
    strcat(newjson, "\"");
    strcat(newjson, token);
    strcat(newjson, "\"\n");
    //<\token>
    strcat(newjson, jsonstring->json + len - 1);
    strcpy(jsonstring->json, newjson);
}

void add_integer(struct Jsonstring_t* jsonstring, const char* name, const uintmax_t token) {
    char* tokenaux=(char*)malloc(NUMSTR_SIZE*sizeof(char));
    char* newjson=(char*)malloc(JSON_SIZE*sizeof(char));
    sprintf(tokenaux, "%u", (uint32_t)token);
    uint32_t len = strlen(jsonstring->json);
    strncpy(newjson, jsonstring->json, len - 1);
    if (jsonstring->json[len - 3] == '{') {
        newjson[len - 1] = '\0';
    }
    else {
        newjson[len - 2] = ',';
        newjson[len - 1] = '\n';
        newjson[len] = '\0';
    }
    //<token>
        //generic
    strcat(newjson, "\"");
    strcat(newjson, name);
    strcat(newjson, "\":");
    //specific
    strcat(newjson, tokenaux);
    strcat(newjson, "\n");
    //<\token>
    strcat(newjson, jsonstring->json + len - 1);
    strcpy(jsonstring->json, newjson);
    free(tokenaux);
    free(newjson);
}

void add_float(struct Jsonstring_t* jsonstring, const char* name, const float token) {
    char tokenaux[NUMSTR_SIZE];
    sprintf(tokenaux, "%f", token);
    uint32_t len = strlen(jsonstring->json);
    char newjson[JSON_SIZE];
    strncpy(newjson, jsonstring->json, len - 1);
    if (jsonstring->json[len - 3] == '{') {
        newjson[len - 1] = '\0';
    }
    else {
        newjson[len - 2] = ',';
        newjson[len - 1] = '\n';
        newjson[len] = '\0';
    }
    //<token>
        //generic
    strcat(newjson, "\"");
    strcat(newjson, name);
    strcat(newjson, "\":");
    //specific
    strcat(newjson, tokenaux);
    strcat(newjson, "\n");
    //<\token>
    strcat(newjson, jsonstring->json + len - 1);
    strcpy(jsonstring->json, newjson);
}

