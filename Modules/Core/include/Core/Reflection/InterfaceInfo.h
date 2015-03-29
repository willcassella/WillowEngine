// InterfaceInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

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

	InterfaceInfo(const InterfaceInfo& copy) = delete;
	InterfaceInfo(InterfaceInfo&& move);

protected:

	template <class AnyInterfaceType>
	InterfaceInfo(AnyInterfaceType* dummy, const String& name)
		: Super(dummy, name)
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type is abstract
	* NOTE: Always returns true - interfaces are always abstract */
	FORCEINLINE bool IsAbstract() const override
	{
		return true;
	}

	/** Returns whether this type is polymorphic
	* NOTE: Always returns true - interfaces are always polymorphic */
	FORCEINLINE bool IsPolymorphic() const override
	{
		return true;
	}
	
	bool IsCastableTo(const TypeInfo& type) const override;

	/////////////////////
	///   Operators   ///
public:

	InterfaceInfo& operator=(const InterfaceInfo& copy) = delete;
	InterfaceInfo& operator=(InterfaceInfo&& move) = delete;
};