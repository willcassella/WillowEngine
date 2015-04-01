// Variant.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "VoidInfo.h"

/////////////////
///   Types   ///

/** Basically a reference to a value of any type
* NOTE: Does not have ownership over the value it references! */
struct CORE_API Variant final
{
	///////////////////////
	///   Information   ///
public:

	template <typename AnyType, typename TargetType> friend struct Implementation::Cast;

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs an immutable Variant to 'void' */
	Variant()
		: _value(nullptr), _type(&TypeOf<void>()), _isImmutable(true)
	{
		// All done
	}

	/** Constructs a mutable Variant */
	template <typename AnyType>
	Variant(AnyType& value)
		: _value(&value), _type(&TypeOf(value)), _isImmutable(false)
	{
		// All done
	}

	/** Constructs an immutable Variant */
	template <typename AnyType>
	Variant(const AnyType& value)
		: _value(const_cast<AnyType*>(&value)), _type(&TypeOf(value)), _isImmutable(true)
	{
		// All done
	}

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

	/** Calls the destructor on the referenced value
	* Returns: Whether destruction completed successfully
	* NOTE: Does nothing if the value is immutable */
	FORCEINLINE bool Destroy()
	{
		if (_isImmutable)
		{
			return false;
		}
		else
		{
			bool sucess = _type->_destructor(_value);

			if (sucess)
			{
				_value = nullptr;
				_type = &TypeOf<void>();
				_isImmutable = true;
			}
			return sucess;
		}
	}

	/////////////////////
	///   Operators   ///
public:

	/** Assigns this Variant to a mutable value */
	template <typename AnyType>
	Variant& operator=(AnyType& value)
	{
		_value = &value;
		_type = &TypeOf(value);
		_isImmutable = false;
		return This;
	}

	/** Assigns this Variant to an immutable value */
	template <typename AnyType>
	Variant& operator=(const AnyType& value)
	{
		_value = &value;
		_type = &TypeOf(value);
		_isImmutable = true;
		return This;
	}

	////////////////
	///   Data   ///
private:

	void* _value;
	const TypeInfo* _type;
	bool _isImmutable;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	template <typename TargetType>
	struct Cast < Variant, TargetType >
	{
		FORCEINLINE static TargetType* Function(Variant value)
		{
			// @TODO: Implement this
		}
	};
}