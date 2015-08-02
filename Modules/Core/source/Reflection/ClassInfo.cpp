// ClassInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Reflection/InterfaceInfo.h"

///////////////////////
///   Information   ///

BUILD_REFLECTION(ClassInfo);

////////////////////////
///   Constructors   ///

TypeInfoBuilder<Object, ClassInfo>::TypeInfoBuilder()
	: TypeInfoBuilderBase<Object, ClassInfo>("Object")
{
	_data.Base = nullptr;
}

///////////////////
///   Methods   ///

bool ClassInfo::IsCastableTo(const TypeInfo& type) const
{
	// If the given type is this type
	if (type == self)
	{
		return true;
	}
	// If the given type is a class
	else if (const ClassInfo* pType = Cast<ClassInfo>(type))
	{
		// Check if this class is the given class or extends the given class
		return Extends(*pType);
	}
	// If the given type is an interface
	else if (const InterfaceInfo* pType = Cast<InterfaceInfo>(type))
	{
		// Check if this class implements the given interface
		return Implements(*pType);
	}
	else
	{
		// If none of the above is true, the types are definitely not compatible
		return false;
	}
}

Array<PropertyInfo> ClassInfo::GetProperties() const
{
	if (GetBase())
	{
		return Base::GetProperties() + GetBase()->GetProperties();
	}
	else
	{
		return Base::GetProperties();
	}
}

const PropertyInfo* ClassInfo::FindProperty(const String& name) const
{
	const PropertyInfo* property = Base::FindProperty(name);

	if (property)
	{
		return property;
	}
	else if (GetBase())
	{
		return GetBase()->FindProperty(name);
	}
	else
	{
		return nullptr;
	}
}

bool ClassInfo::Extends(const ClassInfo& type) const
{
	if (GetBase())
	{
		// If the base class is the type we're looking for
		if (*GetBase() == type)
		{
			// We extend that class
			return true;
		}
		else
		{
			// The base class might extend that class
			return GetBase()->Extends(type);
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
	for (auto implementedInterf : _data.Interfaces)
	{
		if (*implementedInterf == interf)
		{
			return true;
		}
	}

	// Check if the base class implements this interface
	if (GetBase())
	{
		return GetBase()->Implements(interf);
	}
	else
	{
		return false;
	}
}