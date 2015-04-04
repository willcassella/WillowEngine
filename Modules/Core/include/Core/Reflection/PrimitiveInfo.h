// PrimitiveInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "TypeInfo.h"

/////////////////
///   Types   ///

class CORE_API PrimitiveInfo : public TypeInfo
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
	template <typename AnyPrimitiveType>
	static PrimitiveInfo Create(const String& name)
	{
		AnyPrimitiveType* dummy = nullptr;
		return PrimitiveInfo(dummy, name);
	}

	PrimitiveInfo(const PrimitiveInfo& copy) = delete;
	PrimitiveInfo(PrimitiveInfo&& move) = default;

protected:

	template <typename AnyPrimitiveType>
	PrimitiveInfo(AnyPrimitiveType* dummy, const String& name)
		: Super(dummy, name)
	{
		static_assert(std::is_arithmetic<AnyPrimitiveType>::value || 
			std::is_pointer<AnyPrimitiveType>::value ||
			std::is_fundamental<AnyPrimitiveType>::value,
			"Primitives types must be primitive");
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type is castable (via reinterpret_cast) to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;

	/////////////////////
	///   Operators   ///
public:

	PrimitiveInfo& operator=(const PrimitiveInfo& copy) = delete;
	PrimitiveInfo& operator=(PrimitiveInfo&& move) = delete;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** TypeInfo for bool */
	template <>
	struct CORE_API TypeOf < bool >
	{
		/** Defined in 'PrimitiveInfo.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(bool value)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for char */
	template <>
	struct CORE_API TypeOf < char >
	{
		/** Defined in 'PrimitiveInfo.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(char value)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for byte */
	template <>
	struct CORE_API TypeOf < byte >
	{
		/** Defined in 'PrimitiveInfo.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(byte value)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for 16-bit integer */
	template <>
	struct CORE_API TypeOf < int16 >
	{
		/** Defined in 'PrimitiveInfo.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(int16 value)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for 32-bit integer */
	template <>
	struct CORE_API TypeOf < int32 >
	{
		/** Defined in 'PrimitiveInfo.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(int32 value)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for 64-bit integer */
	template <>
	struct CORE_API TypeOf < int64 >
	{
		/** Defined in 'PrimitiveInfo.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(int64 value)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for 16-bit unsigned integer */
	template <>
	struct CORE_API TypeOf < uint16 >
	{
		/** Defined in 'PrimitiveInfo.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(uint16 value)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for 32-bit unsigned integer */
	template <>
	struct CORE_API TypeOf < uint32 >
	{
		/** Defined in 'PrimitiveInfo.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(uint32 value)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for a 64-bit unsigned integer */
	template <>
	struct CORE_API TypeOf < uint64 >
	{
		/** Defined in 'PrimitiveInfo.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(uint64 value)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for a float */
	template <>
	struct CORE_API TypeOf < float >
	{
		/** Defined in 'PrimitiveInfo.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(float value)
		{
			return StaticTypeInfo;
		}
	};

	/** TypeInfo for a double */
	template <>
	struct CORE_API TypeOf < double >
	{
		/** Defined in 'PrimitiveInfo.cpp' */
		static const PrimitiveInfo StaticTypeInfo;

		FORCEINLINE static const PrimitiveInfo& Function()
		{
			return StaticTypeInfo;
		}

		FORCEINLINE static const PrimitiveInfo& Function(double value)
		{
			return StaticTypeInfo;
		}
	};
}