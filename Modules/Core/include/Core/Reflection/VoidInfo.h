// VoidInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "PrimitiveInfo.h"

/////////////////
///   Types   ///

//class CORE_API VoidInfo final : public TypeInfo
//{
//	///////////////////////
//	///   Information   ///
//public:
//
//	REFLECTABLE_CLASS;
//	EXTENDS(TypeInfo);
//	friend Implementation::TypeOf<void>;
//
//	////////////////////////
//	///   Constructors   ///
//public:
//
//	VoidInfo(const VoidInfo& copy) = delete;
//	VoidInfo(VoidInfo&& move);
//
//private:
//
//	VoidInfo();
//
//	///////////////////
//	///   Methods   ///
//public:
//
//	bool IsAbstract() const override;
//
//	bool IsPolymorphic() const override;
//
//	bool IsCastableTo(const TypeInfo& type) const override;
//
//	/////////////////////
//	///   Operators   ///
//public:
//
//	TypeInfo& operator=(const TypeInfo& copy) = delete;
//	TypeInfo& operator=(TypeInfo&& move) = delete;
//};

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** TypeOf for 'void' */
	template <>
	struct TypeOf < void >
	{
		/** Defined in 'VoidInfo.cpp' */
		//static const VoidInfo StaticTypeInfo;

		FORCEINLINE static const TypeInfo& Function()
		{
			return ::TypeOf<int>();
		}

		/** It is not possible to retrieve type data for an instance of 'void' */
	};
}