//Scripting.h

#ifndef SCRIPTING_H_
#define SCRIPTING_H_

#include "..\..\source\angelscript.h"

int InitScriptingModule();

int ExecuteMain();

int RegisterGlobalFunction(const char* declaration, const asSFuncPtr &funcPointer, asDWORD callConv, void *objForThisCall = (void *)0);

#endif