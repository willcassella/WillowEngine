// Unpack.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Exception.h"
#include "TypeInfo.h"
#include "Value.h"
#include "Reference.h"

/////////////////
///   Types   ///

/** Exception thrown after an attempt to unpack a Value/Reference to an incompatible type */
class CORE_API IncompatibleUnpackException final : public Exception
{
	////////////////////////
	///   Constructors   ///
public:

	/** Construct an IncompatibleUnpackException
	* "actualType" - the type actually held by the Value/Reference
	*  "attemptedUnpackType" - The type the Value/Reference was attempted to be unpacked as */
	IncompatibleUnpackException(const TypeInfo& actualType, const TypeInfo& attemptedUnpackType);

	///////////////////
	///   Methods   ///
public:

	/** Returns the error message */
	String GetError() const override;

	/** Returns the actual type Value/Reference held */
	const TypeInfo& GetActualType() const;

	/** Returns the type the Value/Reference was attempted to be unpacked as */
	const TypeInfo& GetAttemptedUnpackType() const;

	////////////////
	///   Data   ///
private:

	const TypeInfo* _actualType;
	const TypeInfo* _attemptedUnpackType;
};

/** Exception thrown after an attempt to interact with a null Value */
class CORE_API NullValueException final : public Exception
{
	///////////////////
	///   Methods   ///
public:

	/** Returns the error message */
	String GetError() const override;
};

/** Exception thrown after an attempt to interact with a null Reference */
class CORE_API NullReferenceException final : public Exception
{
	///////////////////
	///   Methods   ///
public:

	/** Returns the error message */
	String GetError() const override;
};

/** Exception thrown after an attempt to unpack a immutable Reference as non-immutable reference */
class CORE_API ImmutableReferenceException final : public Exception
{
	///////////////////
	///   Methods   ///
public:

	/** Returns the error message */
	String GetError() const override;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Unpack as value type */
	template <typename TargetType>
	struct Unpack
	{
		/** Unpack a Value */
		static TargetType Function(const Value& value)
		{
			if (value.IsNull())
			{
				throw NullValueException();
			}
			else if (!value.GetType().IsCastableTo<TargetType>())
			{
				throw IncompatibleUnpackException(value.GetType(), ::TypeOf<TargetType>());
			}
			else
			{
				return *static_cast<TargetType*>(value._value->GetValue());
			}
		}

		/** Unpack a Reference */
		static TargetType Function(const Reference& value)
		{
			if (value.IsNull())
			{
				throw NullReferenceException();
			}
			else if (!value.GetType().IsCastableTo<TargetType>())
			{
				throw IncompatibleUnpackException(value.GetType(), ::TypeOf<TargetType>());
			}
			else
			{
				return *static_cast<TargetType*>(value._value->GetValue());
			}
		}
	};

	/** Unpack as reference */
	template <typename TargetType>
	struct Unpack < TargetType& >
	{
		/** Unpack a Value */
		static TargetType& Function(Value& value)
		{
			if (value.IsNull())
			{
				throw NullValueException();
			}
			else if (!value.GetType().IsCastableTo<TargetType>())
			{
				throw IncompatibleUnpackException(value.GetType(), ::TypeOf<TargetType>());
			}
			else
			{
				return *static_cast<TargetType*>(value._value->GetValue());
			}
		}

		/** Unpack a Reference */
		static TargetType& Function(const Reference& value)
		{
			if (value.IsNull())
			{
				throw NullReferenceException();
			}
			else if (value.IsImmutable())
			{
				throw ImmutableReferenceException();
			}
			else if (!value.GetType().IsCastableTo<TargetType>())
			{
				throw IncompatibleUnpackException(value.GetType(), ::TypeOf<TargetType>());
			}
			else
			{
				return *static_cast<TargetType*>(value._value->GetValue());
			}
		}
	};

	/** Unpack as immutable reference */
	template <typename TargetType>
	struct Unpack < const TargetType& >
	{
		/** Unpack a Value */
		static const TargetType& Function(const Value& value)
		{
			if (value.IsNull())
			{
				throw NullValueException();
			}
			else if (!value.GetType().IsCastableTo<TargetType>())
			{
				throw IncompatibleUnpackException(value.GetType(), ::TypeOf<TargetType>());
			}
			else
			{
				return *static_cast<TargetType*>(value._value->GetValue());
			}
		}

		/** Unpack a Reference */
		static const TargetType& Function(const Reference& value)
		{
			if (value.IsNull())
			{
				throw NullReferenceException();
			}
			else if (!value.GetType().IsCastableTo<TargetType>())
			{
				throw IncompatibleUnpackException(value.GetType(), ::TypeOf<TargetType>());
			}
			else
			{
				return *static_cast<TargetType*>(value._value->GetValue());
			}
		}
	};
}

/////////////////////
///   Functions   ///

/** Unpack Value */
template <typename TargetType>
FORCEINLINE TargetType Unpack(Value& value)
{
	return Implementation::Unpack<TargetType>::Function(value);
}

/** Unpack immutable Value */
template <typename TargetType>
FORCEINLINE TargetType Unpack(const Value& value)
{
	return Implementation::Unpack<TargetType>::Function(value);
}

/** Unpack Reference */
template <typename TargetType>
FORCEINLINE TargetType Unpack(const Reference& value)
{
	return Implementation::Unpack<TargetType>::Function(value);
}