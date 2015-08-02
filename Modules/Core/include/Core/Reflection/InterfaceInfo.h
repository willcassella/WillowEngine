// InterfaceInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Interface.h"
#include "CompoundInfo.h"

/** Type information for interfaces */
class CORE_API InterfaceInfo : public CompoundInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(CompoundInfo)

	////////////////////////
	///   Constructors   ///
public:

	/** Creates reflection information for the given interface
	* NOTE: Do not use this outside of the registration function for a interface
	* 'name' - The fully-qualified name of the interface */
	template <class InterfaceT>
	static InterfaceInfo Create(const String& name)
	{
		InterfaceT* dummy = nullptr;
		return InterfaceInfo(dummy, name);
	}

protected:

	/** Constructs a new instance of 'InterfaceInfo'.
	* 'dummy' - A pointer to an instance of the interface.
	* 'name' - The name of the interface. */
	template <class InterfaceT>
	InterfaceInfo(InterfaceT* dummy, const String& name)
		: Base(dummy, name)
	{
		static_assert(std::is_base_of<Interface, InterfaceT>::value, "Interfaces must extend the 'Interface' class.");
		static_assert(!std::is_base_of<Object, InterfaceT>::value, "Interfaces may not extend the 'Object' class.");
		static_assert(std::is_abstract<InterfaceT>::value, "Interfaces must be abstract.");
		static_assert(sizeof(InterfaceT) == sizeof(Interface), "Interfaces may not contain anything other than virtual members.");
	}

	///////////////////
	///   Methods   ///
public:
	
	bool IsCastableTo(const TypeInfo& type) const override;
};
