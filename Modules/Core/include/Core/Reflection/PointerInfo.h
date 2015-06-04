// PointerInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "TypeIndex.h"
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
	template <typename PointedType> 
	friend struct Implementation::TypeOf; // @TODO: Figure out more specific way of doing this

	////////////////////////
	///   Constructors   ///
private:

	// @TODO: Documentation
	template <typename AnyPointerType>
	static PointerInfo Create()
	{
		AnyPointerType* dummy = nullptr;
		return PointerInfo(dummy);
	}

	template <typename AnyPointerType, typename PointedType = std::remove_pointer<AnyPointerType>::type>
	PointerInfo(AnyPointerType* dummy)
		: Super(dummy, ""), _pointedType(TypeOf<PointedType>())
	{
		static_assert(std::is_pointer<AnyPointerType>::value, "PointerTypes must be pointers");

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
	/** Register TypeInfo for pointer */
	template <typename PointedType>
	const PointerInfo TypeOf<PointedType*>::StaticTypeInfo = PointerInfo::Create<PointedType*>();
}