// ClassInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/Registration.h"
#include "../../include/Core/Reflection/InterfaceInfo.h"

///////////////////////
///   Information   ///

CLASS_REFLECTION(ClassInfo);

////////////////////////
///   Constructors   ///

ClassInfo::ClassInfo(uint32 size, const String& name, const ClassInfo* base, bool isAbstract)
	: Super(size, name), _base(base), _isAbstract(isAbstract), _isInstantiable(false), _stackFactory(nullptr), 
	_heapFactory(nullptr), _interfaces(), _fields()
{
	// All done
}

ClassInfo::ClassInfo(ClassInfo&& move)
	: Super(std::move(move)), _base(move._base), _isAbstract(move._isAbstract), _isInstantiable(move._isInstantiable), 
	_stackFactory(move._stackFactory), _heapFactory(move._heapFactory), _interfaces(std::move(move._interfaces)), _fields(std::move(move._fields))
{
	// All done
}

ClassInfo::~ClassInfo()
{
	for (auto field : _fields)
	{
		delete field.Second;
	}
}

///////////////////
///   Methods   ///

bool ClassInfo::IsAbstract() const
{
	return _isAbstract;
}

bool ClassInfo::IsPolymorphic() const
{
	return true;
}

bool ClassInfo::IsInstantiable() const
{
	return _isInstantiable;
}

bool ClassInfo::IsCastableTo(const TypeInfo& type) const
{
	// If the given type is a class
	if (type.IsA<ClassInfo>())
	{
		// Check if this class is the given class or extends the given class
		return type == This || ExtendsClass(static_cast<const ClassInfo&>(type));
	}
	// If the given type is an interface
	else if (type.IsA<InterfaceInfo>())
	{
		// Check if this class implements the given interface
		return ImplementsInterface(static_cast<const InterfaceInfo&>(type));
	}

	// If neither is true, the types are definitely not compatible
	return false;
}

Value ClassInfo::StackInstance() const
{
	return _stackFactory();
}

Reference ClassInfo::HeapInstance() const
{
	return _heapFactory();
}

Array<const IFieldInfo*> ClassInfo::GetFields() const
{
	Array<const IFieldInfo*> fields(_fields.Size());

	for (auto field : _fields)
	{
		fields.Add(field.Second);
	}

	return fields;
}

bool ClassInfo::ExtendsClass(const ClassInfo& type) const
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
			return _base->ExtendsClass(type);
		}
	}
	else
	{
		// End of the line, we definitely don't extend that class
		return false;
	}
}

bool ClassInfo::ImplementsInterface(const InterfaceInfo& interf) const
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
		return _base->ImplementsInterface(interf);
	}
	else
	{
		return false;
	}
}

const IFieldInfo* ClassInfo::FindField(const String& name) const
{
	auto field = _fields.Find(name);

	if (field)
	{
		return *field;
	}
	else
	{
		return nullptr;
	}
}

ClassInfo&& ClassInfo::SetFactory(Value(*stackFactory)(), Reference(*heapFactory)())
{
	_isInstantiable = true;
	_stackFactory = stackFactory;
	_heapFactory = heapFactory;
	return std::move(This);
}