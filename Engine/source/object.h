#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>

#define REGISTER(T)			\
	public:					\
	std::string getType()	\
	{						\
		return #T;			\
	}

class object
{
public:
	virtual std::string getType() = 0;
};

#endif