//GlobalFunctions.h

#ifndef GLOBAL_FUNCTIONS_H_
#define GLOBAL_FUNCTIONS_H_

#include <string>
#include "angelscript.h"

//Global print function
void print(std::string &str);

//Compiler callback function
void MessageCallback(const asSMessageInfo *msg, void *param);

#endif