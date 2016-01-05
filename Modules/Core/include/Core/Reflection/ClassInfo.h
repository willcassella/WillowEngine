// ClassInfo.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "InterfaceInfo.h"

/////////////////
///   Types   ///

/** Type information for classes */
class CORE_API ClassInfo : public CompoundInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(CompoundInfo)

	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	////////////////////////
	///   Constructors   ///
public:

	template <class ClassT>
	ClassInfo(const TypeInfoBuilder<ClassT, ClassInfo>& builder)
		: Base(builder), _data(std::move(builder._data))
	{
		static_assert(std::is_base_of<Object, ClassT>::value, "Classes must be extend 'Object'");
	}

	///////////////////
	///   Methods   ///
public:

	bool IsCastableTo(const TypeInfo& type) const override;

	bool IsStable() const final override;

	/** Returns all properties on this type (including base type properties). */
	Array<PropertyInfo> GetProperties() const final override;

	/** Searches for a property on this type by name (including base type properties). */
	const PropertyInfo* FindProperty(const String& name) const final override;

	/** Returns all data members on this type (including base type members). */
	Array<DataInfo> GetData() const final override;

	/** Searches for a data member on this type by name (including base type members). */
	const DataInfo* FindData(const String& name) const final override;

	/** Returns a pointer to the base class of this class. 
	* NOTE: In the case of 'Object', this returns null. */
	FORCEINLINE const ClassInfo* GetBase() const
	{
		return _data.Base;
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

	struct Data
	{
		Array<const InterfaceInfo*> Interfaces;
		const ClassInfo* Base;
	} _data;
};

/** Generic TypeInfoBuilder for ClassInfo */
template <class ClassT>
struct TypeInfoBuilder < ClassT, ClassInfo > : TypeInfoBuilderBase<ClassT, ClassInfo>
{
	///////////////////////
	///   Information   ///
public:

	friend ClassInfo;

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	TypeInfoBuilder(CString name)
		: TypeInfoBuilderBase<ClassT, ClassInfo>(name)
	{
		// Get the base type
		_data.Base = &TypeOf<BaseTypeOf<ClassT>>();

		// If this class adds new implemented interfaces
		if (!std::is_same<InterfaceTypesOf<BaseTypeOf<ClassT>>, InterfaceTypesOf<ClassT>>::value)
		{
			AddInterfaces(InterfaceTypesOf<ClassT>{});
		}
	}

	///////////////////
	///   Methods   ///
private:

	/** Adds all the interfaces within "type_sequence<...>" to this class's collection of implemented interfaces. */
	void AddInterfaces(stdEXT::type_sequence<>)
	{
		// Do nothing, no interfaces exist
	}

	/** Adds all the interfaces within "type_sequence<...>" to this class's collection of implemented interfaces. */
	template <class InterfaceT, class ... MoreInterfaceT>
	void AddInterfaces(stdEXT::type_sequence<InterfaceT, MoreInterfaceT...>)
	{
		static_assert(std::is_base_of<InterfaceT, ClassT>::value, "You must actually implement the interface.");
		static_assert(std::is_same<TypeInfoTypeOf<InterfaceT>, InterfaceInfo>::value, "The type given to 'AddInterface' must be an interface.");

		_data.Interfaces.Add(&TypeOf<InterfaceT>());
		AddInterface(stdEXT::type_sequence<MoreInterfaceT...>{});
	}

	////////////////
	///   Data   ///
private:

	mutable ClassInfo::Data _data;
};

// TODO: Documentation
template <>
struct CORE_API TypeInfoBuilder < Object, ClassInfo > final : TypeInfoBuilderBase<Object, ClassInfo>
{
	///////////////////////
	///   Information   ///
public:

	friend ClassInfo;

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	TypeInfoBuilder();

	////////////////
	///   Data   ///
private:

	ClassInfo::Data _data;
};
