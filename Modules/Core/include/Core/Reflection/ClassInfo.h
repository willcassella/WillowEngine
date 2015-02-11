// ClassInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <type_traits>
#include "TypeInfo.h"
#include "FieldInfo.h"

/** Type information for classes */
class CORE_API ClassInfo final : public TypeInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(TypeInfo);
	friend Object;

	////////////////////////
	///   Constructors   ///
public:

	/** Creates reflection information for the given class
	* NOTE: Do not use this outside of the registration function for a class
	* 'name' - The fully-qualified name of the class */
	template <class AnyClass>
	static ClassInfo Create(const String& name)
	{
		return ClassInfo(sizeof(AnyClass), name, &AnyClass::Super::StaticTypeInfo, std::is_abstract<AnyClass>::value);
	}
	
	ClassInfo(const ClassInfo& copy) = delete;
	ClassInfo(ClassInfo&& move);
	~ClassInfo() override;

private:

	ClassInfo(uint32 size, const String& name, const ClassInfo* base, bool isAbstract);

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this class is abstract */
	bool IsAbstract() const override;

	/** Returns whether this class is polymorphic 
	* NOTE: Always returns true - classes are always polymorphic */
	bool IsPolymorphic() const override;

	/** Returns whether this class is instantiable */
	bool IsInstantiable() const override;

	/** Returns whether this type castable (via reinterpret_cast) to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;
		
	/** Returns an instance of this class, allocated on the stack
	* WARNING: Returns a null Value if this class is not instantiable (check 'IsInstantiable()') */
	Value StackInstance() const override;

	/** Returns a Reference to an instance of this class, allocated on the heap
	* WARNING: Callee has ownership over the lifetime of returned value (it must be deleted manually)
	* WARNING: Returns a null Reference if this class is not instantiable (check 'IsIntantiable()') */
	Reference HeapInstance() const override;

	/** Returns a list of all the fields of this type */
	Array<const IFieldInfo*> GetFields() const;

	/** Returns whether this class extends the given class */
	bool ExtendsClass(const ClassInfo& type) const;

	/** Returns whether this class implements the given interface */
	bool ImplementsInterface(const InterfaceInfo& interf) const;

	/** Searches for the field in this type */
	const IFieldInfo* FindField(const String& name) const;

	/** Sets the factory function for this type
	* NOTE: You should always call this with '&StackFactory<MyType>()', and '&HeapFactory<MyType>()'
	* NOTE: When using macros, this is automatically configured by using the 'HAS_FACTORY' flag */
	ClassInfo&& SetFactory(Value(*stackFactory)(), Reference(*heapFactory)());

	/** Adds a field to this type's fields
	* NOTE: Only register fields that were added by this class, DO NOT include base class fields. You can Register base classes with the SetBase() method 
	* NOTE: When using macros, this is automatically configured by using the 'FIELD(F)' macro */
	template <class OwnerType, typename FieldType>
	ClassInfo&& AddField(const String& name, FieldType OwnerType::*field)
	{
		_fields[name] = new FieldInfo<OwnerType, FieldType>(name, field);
		return std::move(This);
	}

	/////////////////////
	///   Operators   ///
public:

	ClassInfo& operator=(const ClassInfo& copy) = delete;
	ClassInfo& operator=(ClassInfo&& move) = delete;

	////////////////
	///   Data   ///
protected:

	const ClassInfo* _base;
	bool _isAbstract;
	bool _isInstantiable;
	Value(*_stackFactory)();
	Reference(*_heapFactory)();
	Array<const InterfaceInfo*> _interfaces;
	Table<String, IFieldInfo*> _fields;
};