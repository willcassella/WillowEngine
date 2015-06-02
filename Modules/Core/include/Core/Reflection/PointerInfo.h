// PointerInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "PrimitiveInfo.h"

/////////////////
///   Types   ///

class CORE_API PointerInfo final : public PrimitiveInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(PrimitiveInfo);

	////////////////////////
	///   Constructors   ///
public:

	// @TODO: Documentation
	template <typename PointedType>
	static PointerInfo Create()
	{
		PointedType** dummy = nullptr;
		return PointerInfo(dummy);
	}

private:

	template <typename PointedType>
	PointerInfo(PointedType** dummy)
		: Super(dummy, ""), _pointedType(TypeOf<PointedType>())
	{
		_isConst = std::is_const<PointedType>::value;
	}

	///////////////////
	///   Methods   ///
public:

	String GetName() const override;

	/** Returns whether this type is castable (via reinterpret_cast) to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;

	/** Returns whether this pointer points to an immutable value (e.g 'const int*' vs 'int*') */
	FORCEINLINE bool IsConst() const
	{
		return _isConst;
	}

	/** Returns the type pointed to by this pointer */
	FORCEINLINE const TypeInfo& GetPointedType() const
	{
		return _pointedType;
	}

	////////////////
	///   Data   ///
private:

	TypeIndex _pointedType;
	bool _isConst;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** TypeInfo for pointers */
	template <typename AnyType>
	struct TypeOf < AnyType* >
	{
		/** Defined below */
		static const PointerInfo StaticPointerInfo;

		FORCEINLINE static const PointerInfo& Function()
		{
			return StaticPointerInfo;
		}

		FORCEINLINE static const PointerInfo& Function(AnyType* value)
		{
			return StaticPointerInfo;
		}
	};

	/** Initialize pointer information */
	template <typename AnyType>
	const PointerInfo TypeOf<AnyType*>::StaticPointerInfo = PointerInfo::Create<AnyType>();

	/** TypeInfo for std::nullptr_t */
	template <>
	struct TypeOf < std::nullptr_t >
	{
		//@TODO: Implement this
	};
}