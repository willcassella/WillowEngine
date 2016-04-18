// InterfaceInfo.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
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

	// TODO: Update this to builder pattern
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
	
	bool is_castable_to(const TypeInfo& type) const override;
};
