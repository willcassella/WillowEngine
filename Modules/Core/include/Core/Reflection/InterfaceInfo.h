// InterfaceInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Interface.h"
#include "TypeInfo.h"

/** Type information for interfaces */
class CORE_API InterfaceInfo : public TypeInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(TypeInfo);

	////////////////////////
	///   Constructors   ///
public:

	/** Creates reflection information for the given interface
	* NOTE: Do not use this outside of the registration function for a interface
	* 'name' - The fully-qualified name of the interface */
	template <class AnyInterfaceType>
	static InterfaceInfo Create(const String& name)
	{
		AnyInterfaceType* dummy = nullptr;
		return InterfaceInfo(dummy, name);
	}

protected:

	// @TODO: Documentation
	template <class AnyInterfaceType>
	InterfaceInfo(AnyInterfaceType* dummy, const String& name)
		: Super(dummy, name)
	{
		static_assert(std::is_base_of<Interface, AnyInterfaceType>::value, "Interfaces must extend the 'Interface' class");
		static_assert(std::is_abstract<AnyInterfaceType>::value, "Interfaces must be abstract");
	}

	///////////////////
	///   Methods   ///
public:
	
	bool IsCastableTo(const TypeInfo& type) const override;
};