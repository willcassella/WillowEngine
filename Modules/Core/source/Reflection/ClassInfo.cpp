// ClassInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/InterfaceInfo.h"

///////////////////////
///   Information   ///

CLASS_REFLECTION(ClassInfo);

////////////////////////
///   Constructors   ///

ClassInfo::ClassInfo(ClassInfo&& move)
	: Super(std::move(move)), _base(move._base), _isAbstract(move._isAbstract), _interfaces(std::move(move._interfaces)), _fields(std::move(move._fields))
{
	// All done
}

///////////////////
///   Methods   ///

bool ClassInfo::IsCastableTo(const TypeInfo& type) const
{
	// If the given type is a class
	if (type.GetType().Extends<ClassInfo>())
	{
		// Check if this class is the given class or extends the given class
		return type == This || Extends(static_cast<const ClassInfo&>(type));
	}
	// If the given type is an interface
	else if (type.GetType().Extends<InterfaceInfo>())
	{
		// Check if this class implements the given interface
		return Implements(static_cast<const InterfaceInfo&>(type));
	}

	// If neither is true, the types are definitely not compatible
	return false;
}

bool ClassInfo::Extends(const ClassInfo& type) const
{
	// If we have a base class
	if (_base)
	{
		// If the base class is the type we're looking for
		if (*_base == type)
		{
			// We extend that class
			return true;
		}
		else
		{
			// The base class might extend that class
			return _base->Extends(type);
		}
	}
	else
	{
		// End of the line, we definitely don't extend that class
		return false;
	}
}

bool ClassInfo::Implements(const InterfaceInfo& interf) const
{
	// Check if the interface is implemented at this level
	for (auto implementedInterf : _interfaces)
	{
		if (*implementedInterf == interf)
		{
			return true;
		}
	}

	// Check if the base class implements this interface
	if (_base)
	{
		return _base->Implements(interf);
	}
	else
	{
		return false;
	}
}