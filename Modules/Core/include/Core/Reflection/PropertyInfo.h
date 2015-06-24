// PropertyInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <functional>
#include "Variant.h"

/** A class representing the information for a Property.
* This unfortunately does not model all the const/reference overload
* possibilities for getters and setters, */
struct CORE_API PropertyInfo final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;
	friend CompoundInfo;

	////////////////////////
	///   Constructors   ///
private:

	PropertyInfo(const String& name, const String& description);
	
	///////////////////
	///   Methods   ///
public:

	/** Returns the name of this Property. */
	FORCEINLINE const String& GetName() const
	{
		return _name;
	}

	/** Returns a description of this Property. */
	FORCEINLINE const String& GetDescription() const
	{
		return _description;
	}

	/** Returns the type information for this Property. */
	FORCEINLINE const TypeInfo& GetPropertyType() const
	{
		return _propertyType;
	}

	/** Returns the type information for the owner of this Property. */
	FORCEINLINE const CompoundInfo& GetOwnerType() const
	{
		return *_ownerType;
	}

	/** Returns whether this Property has an immutable getter. */
	FORCEINLINE bool HasMutableGetter() const
	{
		return _mutableGetter != nullptr;
	}

	/** Returns whether this Property has a getter. */
	FORCEINLINE bool HasGetter() const
	{
		return _getter != nullptr;
	}

	/** Returns whether this Property has a setter. */
	FORCEINLINE bool HasSetter() const
	{
		return _setter != nullptr;
	}

	/** Returns whether this property is a field.
	* If a property is a field, then it lives within the owner object and can be serialized recursively without creating cycles.
	* NOTE: If this is false, that does not imply that the above is not true, but you should not rely on it.
	* NOTE: Just because a property is a field does not imply that it is mutably gettable. It may be a const field, or a field with a custom setter. */
	FORCEINLINE bool IsField() const
	{
		return _isField;
	}

	/** Returns whether this property may be polymorphic.
	* If this property is retrieved via a getter method that returns a reference to a polymorphic type (class or interface),
	* then this property is considered polymorphic. That means that the type returned by "PropertyType" may not be the most specific type
	* of the actual value that is returned by this getter, you must check the returned value to decided that. 
	* NOTE: If "IsField" is true, then this is always false. */
	FORCEINLINE bool IsPolymorphic() const
	{
		return _isPolymorphic;
	}

	/** Returns a Variant to the value of this Property on the given Variant.
	* NOTE: If this Property has no mutable getter, returns a Variant to 'void' (check 'HasMutableGetter' first).
	* NOTE: The value referenced by 'owner' must be of the same or extension of the type referenced by 'GetOwnerType'. */
	Variant GetMutableValue(const Variant& owner) const;

	/** Returns an ImmutableVariant to the value of this Property on the given ImmutableVariant.
	* NOTE: If this Property has no getter, returns an ImmutableVariant to 'void' (check 'HasGetter' first).
	* NOTE: The value referenced by 'owner' must be of the same or extension of the type referenced by 'GetOwnerType'. */
	ImmutableVariant GetValue(const ImmutableVariant& owner) const;

	/** Copies the value of this Property on the given ImmutableVariant.
	* NOTE: If the type of this property is not copy-constructible, returns a Variant to 'void' (check 'IsCopyable' first). 
	* NOTE: The value referenced by 'owner' must be of the same or extension of the type referenced by 'GetOwnerType'. */
	Variant CopyValue(const ImmutableVariant& owner) const;

	/** Sets the value of this Property on the given Variant to the given value.
	* NOTE: If this Property has no setter, does nothing (check 'HasSetter' first).
	* NOTE: The value referenced by 'owner' must be of the same or extension of the type referenced by 'GetOwnerType'.
	* NOTE: The value referenced by 'value' must be of the same or extension of the type referenced by 'GetFieldType'. */
	void SetValue(const Variant& owner, const ImmutableVariant& value) const;

private:

	/** Sets the mutable getter to return a field */
	template <class OwnerType, typename FieldType>
	void SetMutableGetter(FieldType OwnerType::*field)
	{
		_mutableGetter = [field](void* owner) -> Variant
		{
			auto pOwner = static_cast<OwnerType*>(owner);
			return Variant(&(pOwner->*field), TypeOf<FieldType>());
		};
	}

	/** Sets the mutable getter to do nothing */
	template <class OwnerType, typename FieldType>
	void SetMutableGetter(const FieldType OwnerType::* /*field*/)
	{
		// Do nothing (field is const, so can't return mutable variant)
	}

	/** Sets the getter to return a field */
	template <class OwnerType, typename FieldType>
	void SetGetter(FieldType OwnerType::*field)
	{
		_getter = [field](const void* owner) -> ImmutableVariant
		{
			auto pOwner = static_cast<const OwnerType*>(owner);
			return ImmutableVariant(&(pOwner->*field), TypeOf<FieldType>());
		};
	}

	/** Sets the getter to call a getter method that returns by reference */
	template <class OwnerType, typename PropertyType>
	void SetGetter(PropertyType& (OwnerType::*getter)() const)
	{
		_getter = [getter](const void* owner) -> ImmutableVariant
		{
			auto pOwner = static_cast<const OwnerType*>(owner);
			PropertyType& value = (pOwner->*getter)();
			return ImmutableVariant(&value, TypeOf(value));
		};
	}

	/** Sets the getter to call a getter method that returns by value */
	template <class OwnerType, typename PropertyType>
	void SetGetter(PropertyType (OwnerType::*getter)() const)
	{
		_getter = [getter](const void* owner) -> ImmutableVariant
		{
			auto pOwner = static_cast<const OwnerType*>(owner);
			auto pValue = new PropertyType((pOwner->*getter)());
			return ImmutableVariant(pValue, TypeOf<PropertyType>());
		};
	}

	/** Sets the setter to set to a field */
	template <class OwnerType, typename FieldType>
	void SetSetter(FieldType OwnerType::*field)
	{
		_setter = [field](void* owner, const void* value) -> void
		{
			auto pOwner = static_cast<OwnerType*>(owner);
			auto pValue = static_cast<const FieldType*>(value);
			(pOwner->*field) = *pValue;
		};
	}

	/** Sets the setter to do nothing */
	template <class OwnerType, typename FieldType>
	void SetSetter(const FieldType OwnerType::* /*field*/)
	{
		// Do nothing (field is const, so it can't be set)
	}

	/** Sets the setter to call a setter method */
	template <class OwnerType, typename PropertyType>
	void SetSetter(void (OwnerType::*setter)(PropertyType))
	{
		_setter = [setter](void* owner, const void* value) -> void
		{
			auto pOwner = static_cast<OwnerType*>(owner);
			auto pValue = static_cast<const std::decay_t<PropertyType>*>(value);
			(pOwner->*setter)(*pValue);
		};
	}

	////////////////
	///   Data   ///
private:

	String _name;
	String _description;
	TypeIndex _propertyType;
	const CompoundInfo* _ownerType;
	std::function<Variant (void*)> _mutableGetter;
	std::function<ImmutableVariant (const void*)> _getter;
	std::function<void (void*, const void*)> _setter;
	bool _isField;
	bool _isPolymorphic;
	bool _requiresCopy;
};
