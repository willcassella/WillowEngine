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
	static PointerInfo Create(bool isConst)
	{
		if (isConst)
		{
			/** @TODO: Update this */
			return PointerInfo(sizeof(const PointedType*), &StackFactory<const PointedType*>, &HeapFactory<const PointedType*>, &TypeOf<PointedType>(), true);
		}
		else
		{
			return PointerInfo(sizeof(PointedType*), &StackFactory<PointedType*>, &HeapFactory<PointedType*>, &TypeOf<PointedType>(), false);
		}
	}

	PointerInfo(const PointerInfo& copy) = delete;
	PointerInfo(PointerInfo&& move);

private:

	PointerInfo(uint32 size, Value(*stackFactory)(), Reference(*heapFactory)(), const TypeInfo* pointedType, bool isConst);

	///////////////////
	///   Methods   ///
public:

	String GetName() const override;

	/** Returns whether this type is castable (via reinterpret_cast) to the given type */
	bool IsCastableTo(const TypeInfo& type) const override;

	/** Returns whether this pointer points to an immutable value (e.g 'const int*' vs 'int*') */
	bool IsConst() const;

	/** Returns the type pointed to by this pointer */
	const TypeInfo& GetPointedType() const;

	/////////////////////
	///   Operators   ///
public:

	PointerInfo& operator=(const PointerInfo& copy) = delete;
	PointerInfo& operator=(PointerInfo&& move) = delete;

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
	/** TypeInfo for non-const pointers */
	template <typename AnyType>
	struct TypeOf < AnyType* >
	{
		static const PointerInfo StaticPointerInfo;

		inline static const TypeInfo& Function()
		{
			return StaticPointerInfo;
		}

		inline static const TypeInfo& Function(AnyType* value)
		{
			return StaticPointerInfo;
		}
	};

	/** Initialize non-const pointer information */
	template <typename AnyType>
	const PointerInfo TypeOf<AnyType*>::StaticPointerInfo = PointerInfo::Create<AnyType>(false);

	/** TypeInfo for const pointers */
	template <typename AnyType>
	struct TypeOf < const AnyType* >
	{
		static const PointerInfo StaticPointerInfo;

		inline static const TypeInfo& Function()
		{
			return StaticPointerInfo;
		}

		inline static const TypeInfo& Function(const AnyType* value)
		{
			return StaticPointerInfo;
		}
	};

	/** Initialize const pointer information */
	template <typename AnyType>
	const PointerInfo TypeOf<const AnyType*>::StaticPointerInfo = PointerInfo::Create<AnyType>(true);

	// @TODO: Support for nullptr and void*
}