// ClassInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "CompoundInfo.h"

/** Type information for classes */
class CORE_API ClassInfo : public CompoundInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(CompoundInfo);

	////////////////////////
	///   Constructors   ///
public:

	/** Creates reflection information for the given class
	* NOTE: Do not use this outside of the registration function for a class
	* 'name' - The fully-qualified name of the class */
	template <class ClassT>
	static ClassInfo Create(CString name)
	{
		ClassT* dummy = nullptr;
		return ClassInfo(dummy, name);
	}

protected:

	// @TODO: Documentation
	template <class ClassT>
	ClassInfo(ClassT* dummy, CString name)
		: Super(dummy, name), _base(&ClassT::Super::StaticTypeInfo)
	{
		static_assert(std::is_base_of<Object, ClassT>::value, "Classes must be extend 'Object'");
	}

private:

	/** Special constructor used to construct TypeInfo for "Object" class */
	explicit ClassInfo(Object* dummy, CString name);

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type castable (via reinterpret_cast) to the given type. */
	bool IsCastableTo(const TypeInfo& type) const override;

	/** Returns all properties on this type (including base type properties). */
	Array<PropertyInfo> GetProperties() const override;

	/** Searches for a property on this type by name (including base type properties). */
	const PropertyInfo* FindProperty(const String& name) const override;

	/** Returns a pointer to the base class of this class. */
	FORCEINLINE const ClassInfo* GetBase() const
	{
		return _base;
	}

	/** Returns whether this class extends the given class */
	bool Extends(const ClassInfo& base) const;

	/** Returns whether this class implements the given interface */
	bool Implements(const InterfaceInfo& interf) const;

	/** Returns whether this class extends the given class */
	template <class ClassT>
	FORCEINLINE bool Extends() const
	{
		return Extends(ClassT::StaticTypeInfo);
	}
	
	/** Returns whether this class implements the given interface */
	template <class InterfaceT>
	FORCEINLINE bool Implements() const
	{
		return Implements(InterfaceT::StaticTypeInfo);
	}

	////////////////
	///   Data   ///
protected:

	Array<const InterfaceInfo*> _interfaces;
	const ClassInfo* _base;
};

//////////////////
///   Macros   ///

/** Put this macro into the source file of a class you'd like to reflect
* NOTE: The class muse use the 'REFLECTABLE_CLASS' flag in its header */
#define CLASS_REFLECTION(T) const ::ClassInfo T::StaticTypeInfo = ::ClassInfo::Create<T>(#T)
