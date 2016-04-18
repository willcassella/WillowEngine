// PointerInfo.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
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
	PointerInfo(const TypeInfoBuilder<PointerT, PointerInfo>& builder)
		: Base(builder), _data(std::move(builder._data))
	{
		static_assert(std::is_pointer<PointerT>::value || std::is_same<PointerT, std::nullptr_t>::value, "PointerTypes must be pointers");
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether this type is castable (via reinterpret_cast) to the given type */
	bool is_castable_to(const TypeInfo& type) const override;

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

protected:

	String generate_name() const override;

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
		using PointedT = std::remove_pointer_t<PointerT>;

		_data.PointedType = &TypeOf<PointedT>();
		_data.IsConst = std::is_const<PointedT>::value;
		_data.IsNullptr = false;
	}

	////////////////
	///   Data   ///
private:

	mutable PointerInfo::Data _data;
};

// TODO: Documentation
template <>
struct CORE_API TypeInfoBuilder < std::nullptr_t, PointerInfo > final : TypeInfoBuilderBase<std::nullptr_t, PointerInfo>
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

	mutable PointerInfo::Data _data;
};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Register TypeInfo for pointer */
	template <typename PointedT>
	const PointerInfo TypeOf<PointedT*>::StaticTypeInfo = TypeInfoBuilder<PointedT*>();
}