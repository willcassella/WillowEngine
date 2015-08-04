// ClassInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
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

	// @TODO: Documentation
	template <class ClassT>
	ClassInfo(const TypeInfoBuilder<ClassT, ClassInfo>& builder)
		: Base(builder), _data(std::move(builder._data))
	{
		static_assert(std::is_base_of<Object, ClassT>::value, "Classes must be extend 'Object'");
		static_assert(!std::is_copy_constructible<ClassT>::value, "Class types may not be copy-constructible.");
		static_assert(!std::is_copy_assignable<ClassT>::value, "Class types may not be copy-assignable.");
		static_assert(!std::is_move_assignable<ClassT>::value, "Class types may not be move-assignable.");
		static_assert(!std::is_move_constructible<ClassT>::value || std::is_base_of<TypeInfo, ClassT>::value,
			"Class types may not be move-constructible."); // Except for 'TypeInfo' types
	}

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
		// If this class adds new implemented interfaces
		if (!std::is_same<InterfacesOf<BaseOf<ClassT>>, InterfacesOf<ClassT>>::value)
		{
			AddInterfaces(InterfacesOf<ClassT>{});
		}
	}

	///////////////////
	///   Methods   ///
private:

	/** Adds all the interfaces within "type_sequence<...>" to this class's collection of implemented interfaces. */
	void AddInterfaces(stdEXT::type_sequence<>)
	{
		// Do nothing
	}

	/** Adds all the interfaces within "type_sequence<...>" to this class's collection of implemented interfaces. */
	template <class InterfaceT, class ... MoreInterfaceT>
	void AddInterfaces(stdEXT::type_sequence<InterfaceT, MoreInterfaceT...>)
	{
		static_assert(std::is_base_of<InterfaceT, ClassT>::value, "You must actually implement the interface.");
		static_assert(std::is_same<TypeInfoType<InterfaceT>, InterfaceInfo>::value, "The type given to 'AddInterface' must be an interface.");

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
