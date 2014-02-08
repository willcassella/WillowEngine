//Scripting.cpp

#include "..\include\Scripting.h"
#include "GlobalFunctions.h"

#include <iostream>
#include <string>
#include <assert.h>

#include "angelscript.h"
#include "scriptstdstring.h"

//Declare the scripting engine and components
asIScriptEngine *engine;
asIScriptContext *context;
asIScriptFunction *gMain;

//Function prototypes
int  CompileScript();


int InitScriptingModule()
{
	int error;

	// Initialize the scripting engine
	std::cout << "Initializing scripting engine..." << std::endl;
	engine = asCreateScriptEngine(ANGELSCRIPT_VERSION);
	if( engine == 0 )
	{
		std::cout << "Failed to create script engine." << std::endl;
		return -1;
	}

	// The script compiler will write any compiler messages to the callback.
	engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

	// Register the script string type
	// Look at the implementation for this function for more information  
	// on how to register a custom string type, and other object types.
	RegisterStdString(engine);

	// Register the functions that the scripts will be allowed to use.
	// Note how the return code is validated with an assert(). This helps
	// us discover where a problem occurs, and doesn't pollute the code
	// with a lot of if's. If an error occurs in release mode it will
	// be caught when a script is being built, so it is not necessary
	// to do the verification here as well.
	error = engine->RegisterGlobalFunction("void print(string &in)", asFUNCTION(print), asCALL_CDECL); assert( error >= 0 );
	//check for errors
	if( error < 0 )
	{
		engine->Release();
		return -1;
	}

	// Compile script code
	error = CompileScript();
	if( error < 0 )
	{
		engine->Release();
		return -1;
	}

	// Create a context that will execute the script.
	context = engine->CreateContext();
	if( context == 0 ) 
	{
		std::cout << "Failed to create the context." << std::endl;
		engine->Release();
		return -1;
	}

	// Find the function for the function we want to execute.
	gMain = engine->GetModule(0)->GetFunctionByDecl("void Main()");
	if( gMain == 0 )
	{
		std::cout << "The function 'void Main()' was not found." << std::endl;
		context->Release();
		engine->Release();
		return -1;
	}

	// Prepare the script context with the function we wish to execute. Prepare()
	// must be called on the context before each new script function that will be
	// executed. Note, that if you intend to execute the same function several 
	// times, it might be a good idea to store the function returned by 
	// GetFunctionByDecl(), so that this relatively slow call can be skipped.
	error = context->Prepare(gMain);
	if( error < 0 ) 
	{
		std::cout << "Failed to prepare the context." << std::endl;
		context->Release();
		engine->Release();
		return -1;
	}

	return 0;
}

int ExecuteMain()
{
	int error;
	error = context->Execute();
	if( error != asEXECUTION_FINISHED )
	{
		// The execution didn't finish as we had planned. Determine why.
		if( error == asEXECUTION_ABORTED )
			std::cout << "The script was aborted before it could finish. Probably it timed out." << std::endl;
		else if( error == asEXECUTION_EXCEPTION )
		{
			std::cout << "The script ended with an exception." << std::endl;

			// Write some information about the script exception
			asIScriptFunction *func = context->GetExceptionFunction();
			std::cout << "func: " << func->GetDeclaration() << std::endl;
			std::cout << "modl: " << func->GetModuleName() << std::endl;
			std::cout << "sect: " << func->GetScriptSectionName() << std::endl;
			std::cout << "line: " << context->GetExceptionLineNumber() << std::endl;
			std::cout << "desc: " << context->GetExceptionString() << std::endl;
		}
		else
			std::cout << "The script ended for some unforeseen reason (" << error << ")." << std::endl;
	}
	else
	{
		// Retrieve the return value from the context
		//unsigned long int returnValue = ctx->GetReturnDWord();
		//cout << "The script function returned: " << returnValue << endl;
	}

	return 0;
}

int CompileScript()
{
	int error;

	// We will load the script from a file on the disk.
	FILE *f = fopen("Main.as", "rb");
	if( f == 0 )
	{
		std::cout << "Failed to open the script file 'Main.as'." << std::endl;
		return -1;
	}

	// Determine the size of the file	
	fseek(f, 0, SEEK_END);
	int len = ftell(f);
	fseek(f, 0, SEEK_SET);

	std::string script;
	script.resize(len);
	int c =	(int)fread(&script[0], len, 1, f);
	fclose(f);

	if( c == 0 ) 
	{
		std::cout << "Failed to load script file." << std::endl;
		return -1;
	}

	// Add the script sections that will be compiled into executable code.
	// If we want to combine more than one file into the same script, then 
	// we can call AddScriptSection() several times for the same module and
	// the script engine will treat them all as if they were one. The script
	// section name, will allow us to localize any errors in the script code.
	asIScriptModule *mod = engine->GetModule(0, asGM_ALWAYS_CREATE);
	error = mod->AddScriptSection("script", &script[0], len);
	if( error < 0 ) 
	{
		std::cout << "AddScriptSection() failed" << std::endl;
		return -1;
	}

	// Compile the script. If there are any compiler messages they will
	// be written to the message stream that we set right after creating the 
	// script engine. If there are no errors, and no warnings, nothing will
	// be written to the stream.
	std::cout << "Compiling scripts..." << std::endl;
	error = mod->Build();
	if( error < 0 )
	{
		std::cout << "Build() failed" << std::endl;
		return -1;
	}

	// The engine doesn't keep a copy of the script sections after Build() has
	// returned. So if the script needs to be recompiled, then all the script
	// sections must be added again.

	// If we want to have several scripts executing at different times but 
	// that have no direct relation with each other, then we can compile them
	// into separate script modules. Each module use their own namespace and 
	// scope, so function names, and global variables will not conflict with
	// each other.

	return 0;
}