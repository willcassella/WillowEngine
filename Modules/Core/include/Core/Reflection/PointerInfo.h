// PointerInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "PrimitiveInfo.h"

/////////////////
///   Types   ///

// TODO: Documentation
class CORE_API PointerInfo final : public PrimitiveInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(PrimitiveInfo)

	template <typename T, class TypeInfoT>
	friend struct TypeInfoBuilder;

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	template <typename PointerT>
	PointerInfo(TypeInfoBuilder<PointerT, PointerInfo>& builder)
		: Base(builder), _data(std::move(builder._data))
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	// TODO: Documentation
	String GetName() const override;

	/** Returns whether this type is castable (via reinterpret_cast) to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;

	/** Returns whether this pointer points to an immutable value (e.g 'const int*' vs 'int*') */
	FORCEINLINE bool IsConst() const
	{
		return _data.IsConst;
	}

	/** Returns the type pointed to by this pointer */
	FORCEINLINE const TypeInfo& GetPointedType() const
	{
		return *_data.PointedType;
	}

	////////////////
	///   Data   ///
private:

	struct Data
	{
		const TypeInfo* PointedType;
		bool IsConst;
		bool IsNullptr;
	} _data;
};

/** Generic TypeInfoBuilder for PointerInfo */
template <typename PointerT>
struct TypeInfoBuilder < PointerT, PointerInfo > final : TypeInfoBuilderBase<PointerT, PointerInfo>
{
	///////////////////////
	///   Information   ///
public:

	friend PointerInfo;

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	TypeInfoBuilder()
		: TypeInfoBuilderBase<PointerT, PointerInfo>("")
	{
		static_assert(std::is_pointer<PointerT>::value, "PointerTypes must be pointers");
		using PointedT = std::remove_pointer_t<PointerT>;

		_pointedType = &TypeOf<PointedT>();
		_isConst = std::is_const<PointedT>::value;
		_isNullPtr = false;
	}

	////////////////
	///   Data   ///
private:

	PointerInfo::Data _data;
};

// TODO: Documentation
template <>
struct TypeInfoBuilder < std::nullptr_t, PointerInfo > final : TypeInfoBuilderBase<std::nullptr_t, PointerInfo>
{
	///////////////////////
	///   Information   ///
public:

	friend PointerInfo;

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	TypeInfoBuilder();

	////////////////
	///   Data   ///
private:

	PointerInfo::Data _data;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Register TypeInfo for pointer */
	template <typename PointedT>
	const PointerInfo TypeOf<PointedT*>::StaticTypeInfo = TypeInfoBuilder<PointedT*>();
}