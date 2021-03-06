// ClassInfo.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

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

bool ClassInfo::is_castable_to(const TypeInfo& type) const
{
	// If the given type is this type
	if (type == *this)
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

bool ClassInfo::is_stable() const
{
	return false;
}

Array<PropertyInfo> ClassInfo::GetProperties() const
{
	if (GetBase())
	{
		return GetBase()->GetProperties() + CompoundInfo::GetProperties();
	}
	else
	{
		return CompoundInfo::GetProperties();
	}
}

void ClassInfo::EnumerateProperties(const EnumeratorView<const PropertyInfo&>& enumerator) const
{
	if (GetBase())
	{
		return GetBase()->EnumerateProperties(enumerator);
	}

	CompoundInfo::EnumerateProperties(enumerator);
}

const PropertyInfo* ClassInfo::FindProperty(const String& name) const
{
	const PropertyInfo* property = CompoundInfo::FindProperty(name);

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

Array<DataInfo> ClassInfo::GetData() const
{
	if (GetBase())
	{
		return GetBase()->GetData() + CompoundInfo::GetData();
	}
	else
	{
		return CompoundInfo::GetData();
	}
}

void ClassInfo::EnumerateData(const EnumeratorView<const DataInfo&>& enumerator) const
{
	if (GetBase())
	{
		GetBase()->EnumerateData(enumerator);
	}
	
	CompoundInfo::EnumerateData(enumerator);
}

const DataInfo* ClassInfo::FindData(const String& name) const
{
	const DataInfo* data = CompoundInfo::FindData(name);

	if (data)
	{
		return data;
	}
	else if (GetBase())
	{
		return GetBase()->FindData(name);
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
