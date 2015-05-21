// Variant.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "TypeInfo.h"

/////////////////
///   Types   ///

/** Basically a smart wrapper over "void*" @TODO: Figure out a safer way of doing this */
struct CORE_API Variant final
{
	///////////////////////
	///   Information   ///
public:

	template <typename TargetType> friend TargetType* Cast(const Variant&);
	friend class FieldInfo; // @TODO: Figure out a way to get ride of this

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs an immutable Variant to 'void' */
	Variant();

	/** Constructs a mutable Variant to a value of any type with user-defined ownership
	* 'value' - The value to reference
	* 'type' - The type of the value
	* 'hasOwnership' - Whether this Variant is responsible for deleting the value */
	Variant(void* value, const TypeInfo& type, bool hasOwnership = false);

	/** Constructs an immutable Variant to a value of any type without ownership
	* 'value' - The value to reference 
	* 'type' - The type of the value */
	Variant(const void* value, const TypeInfo& type);

	/** Copies an existing variant, copying the value if that Variant has ownership */
	Variant(const Variant& copy);

	/** Moves an existing variant, taking ownership if necessary */
	Variant(Variant&& move);

	/** Constructs a mutable Variant without ownership */
	template <typename AnyType>
	Variant(AnyType& value)
		: _value(&value), _type(&TypeOf(value)), _isImmutable(false), _hasOwnership(false)
	{
		// All done
	}

	/** Constructs an immutable Variant without ownership */
	template <typename AnyType>
	Variant(const AnyType& value)
		: _value(const_cast<AnyType*>(&value)), _type(&TypeOf(value)), _isImmutable(true), _hasOwnership(false)
	{
		// All done
	}

	/** Construct a mutable Variant with ownership */
	template <typename AnyType>
	Variant(AnyType&& value)
		: _value(nullptr), _type(&TypeOf(value)), _isImmutable(false), _hasOwnership(true)
	{
		_value = Copy(std::move(value));
	}

	/** Destroys this Variant, as well as the value it references if it has ownership */
	~Variant();

	///////////////////
	///   Methods   ///
public:

	/** Returns the type of the referenced value */
	FORCEINLINE const TypeInfo& GetType() const
	{
		return *_type;
	}

	/** Returns whether this Variant references an immutable value */
	FORCEINLINE bool IsImmutable() const
	{
		return _isImmutable;
	}

	/** Returns whether this Variant has ownership over the object it references */
	FORCEINLINE bool HasOwnership() const
	{
		return _hasOwnership;
	}

	/** If this Variant does not currently hold ownership over the value it references, it copies the value and takes ownership
	* Returns: Whether this variant now has ownership over the value */
	bool TakeOwnership();

	/** If this variant currently has ownership over the value it references, releases ownership */
	FORCEINLINE void ReleaseOwnership()
	{
		_hasOwnership = false;
	}

	/** Calls the destructor on the referenced value
	* Returns: Whether destruction completed successfully
	* NOTE: Does nothing if the value is immutable or this Variant does not have ownership */
	bool Destroy();

	/////////////////////
	///   Operators   ///
public:

	Variant& operator=(const Variant& copy) = delete;
	Variant& operator=(Variant&& move) = delete;

	////////////////
	///   Data   ///
private:

	void* _value;
	const TypeInfo* _type;
	bool _isImmutable;
	bool _hasOwnership;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Implementation of "TypeOf" for "Variant" */
	template <>
	struct TypeOf < Variant >
	{
		static const TypeInfo& Function() = delete; // "Variant" has no static type information

		FORCEINLINE static const TypeInfo& Function(const Variant& variant)
		{
			return variant.GetType();
		}
	};
}

/////////////////////
///   Functions   ///

// @TODO: Documentation
template <typename TargetType>
FORCEINLINE TargetType* Cast(const Variant& value)
{
	if (!std::is_const<TargetType>::value && value.IsImmutable())
	{
		return nullptr;
	}
	else
	{
		if (value.GetType().IsCastableTo<TargetType>())
		{
			return static_cast<TargetType*>(value._value);
		}
		else
		{
			return nullptr;
		}
	}
}

// @TODO: Documentation
template <typename TargetType>
FORCEINLINE TargetType* Cast(Variant&& value)
{
	if (value.HasOwnership())
	{
		return nullptr; // Since 'value' is about to be deleted, returning a pointer to its owned data is not safe
	}
	else
	{
		return Cast<TargetType>(value);
	}
}
