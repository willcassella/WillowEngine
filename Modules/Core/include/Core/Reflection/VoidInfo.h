// VoidInfo.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "PrimitiveInfo.h"

/////////////////
///   Types   ///

// TODO: Description
class CORE_API VoidInfo final : public TypeInfo
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(TypeInfo)

	////////////////////////
	///   Constructors   ///
public:

	// TODO: Documentation
	VoidInfo(const TypeInfoBuilder<void, VoidInfo>& builder);

	///////////////////
	///   Methods   ///
public:

	// TODO: Documentation
	bool IsCastableTo(const TypeInfo& type) const override;

	// TODO: Documentation
	bool IsStable() const override;
};

// TODO: Documentation
template <>
struct CORE_API TypeInfoBuilder < void, TypeInfo >
{
	///////////////////////
	///   Information   ///
public:

	friend TypeInfo;

	////////////////////////
	///   Constructors   ///
public:

	TypeInfoBuilder();

	////////////////
	///   Data   ///
private:

	mutable TypeInfo::Data _data;
};

// TODO: Documentation
template <>
struct TypeInfoBuilder < void, VoidInfo > : TypeInfoBuilderBase<void, VoidInfo>
{};
