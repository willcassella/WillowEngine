#ifndef FIELD_H_
#define FIELD_H_

#include <vector>
#include <string>
#include "object.h"

struct Type
{
	std::string name;

};

struct Field
{
	Type* type;
};


#endif