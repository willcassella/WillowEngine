//GlobalFunctions.cpp

#include "GlobalFunctions.h"

#include <string>
#include <iostream>
#include "angelscript.h"

//Global print function
void print(std::string &str)
{
	std::cout << str << std::endl;
}

//Compiler callback function
void MessageCallback(const asSMessageInfo *msg, void *param)
{
	const char *type = "ERR ";
	if( msg->type == asMSGTYPE_WARNING ) 
		type = "WARN";
	else if( msg->type == asMSGTYPE_INFORMATION ) 
		type = "INFO";

	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}