// InterfaceInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "TypeInfo.h"

/** Type information for interfaces */
class CORE_API InterfaceInfo final : public TypeInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(TypeInfo);

	////////////////////////
	///   Constructors   ///
public:

	// @TODO: Documentation
	template <class AnyInterfaceType>
	static InterfaceInfo Create(const String& name)
	{
		return InterfaceInfo(sizeof(AnyInterfaceType), name);
	}

	InterfaceInfo(const InterfaceInfo& copy) = delete;
	InterfaceInfo(InterfaceInfo&& move);

private:

	InterfaceInfo(uint32 size, const String& name);

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type is abstract
	* NOTE: Always returns true - interfaces are always abstract */
	bool IsAbstract() const override;

	/** Returns whether this type is polymorphic
	* NOTE: Always returns true - interfaces are always polymorphic */
	bool IsPolymorphic() const override;

	/** Returns whether this type is instantiable
	* NOTE: Always returns false - interfaces are never instantiable */
	bool IsInstantiable() const override;

	bool IsCastableTo(const TypeInfo& type) const override;

	Value StackInstance() const override;

	Reference HeapInstance() const override;

	/////////////////////
	///   Operators   ///
public:

	InterfaceInfo& operator=(const InterfaceInfo& copy) = delete;
	InterfaceInfo& operator=(InterfaceInfo&& move) = delete;
};