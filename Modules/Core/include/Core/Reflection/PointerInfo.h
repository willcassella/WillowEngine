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

	REFLECTABLE_CLASS
	EXTENDS(PrimitiveInfo)
	template <typename PointedT> 
	friend struct Implementation::TypeOf;

	////////////////////////
	///   Constructors   ///
private:

	/** Creates a new instance of 'PointerInfo'.
	* 'PointerT' - Any type of pointer. */
	template <typename PointerT>
	static PointerInfo Create()
	{
		PointerT* dummy = nullptr;
		return PointerInfo(dummy);
	}

	/** Constructs a new instance of 'PointerInfo'.
	* 'dummy' - A pointer to the ... pointer. */
	template <typename PointerT, typename PointedT = std::remove_pointer_t<PointerT>>
	PointerInfo(PointerT* dummy)
		: Super(dummy, ""), _pointedType(&TypeOf<PointedT>())
	{
		static_assert(std::is_pointer<PointerT>::value, "PointerTypes must be pointers");

		_isConst = std::is_const<PointedT>::value;
	}

	///////////////////
	///   Methods   ///
public:

	// @TODO: Documentation
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
		return *_pointedType;
	}

	////////////////
	///   Data   ///
private:

	const TypeInfo* _pointedType;
	bool _isConst;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Register TypeInfo for pointer */
	template <typename PointedT>
	const PointerInfo TypeOf<PointedT*>::StaticTypeInfo = PointerInfo::Create<PointedT*>();
}