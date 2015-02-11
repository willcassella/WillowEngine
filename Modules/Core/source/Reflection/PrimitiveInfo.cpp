// PrimitiveInfo.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/Registration.h"
#include "../../include/Core/Reflection/Factory.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(PrimitiveInfo);

////////////////////////
///   Constructors   ///

PrimitiveInfo::PrimitiveInfo(uint32 size, const String& name, Value(*stackFactory)(), Reference(*heapFactory)())
	: Super(size, name), _stackFactory(stackFactory), _heapFactory(heapFactory)
{
	// All done
}

PrimitiveInfo::PrimitiveInfo(PrimitiveInfo&& move)
	: Super(std::move(move)), _stackFactory(move._stackFactory), _heapFactory(move._heapFactory)
{
	// All done
}

///////////////////
///   Methods   ///

bool PrimitiveInfo::IsAbstract() const
{
	return false;
}

bool PrimitiveInfo::IsPolymorphic() const
{
	return false;
}

bool PrimitiveInfo::IsInstantiable() const
{
	return true;
}

bool PrimitiveInfo::IsCastableTo(const TypeInfo& type) const
{
	return type == This; // Primitives are not castable to anything other than themselves
}

Value PrimitiveInfo::StackInstance() const
{
	return _stackFactory();
}

Reference PrimitiveInfo::HeapInstance() const
{
	return _heapFactory();
}

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Register TypeInfo for bool */
	const PrimitiveInfo TypeOf<bool>::StaticTypeInfo = PrimitiveInfo::Create<bool>("bool");

	/** Register TypeInfo for char */
	const PrimitiveInfo TypeOf<char>::StaticTypeInfo = PrimitiveInfo::Create<char>("char");

	/** Register TypeInfo for byte */
	const PrimitiveInfo TypeOf<byte>::StaticTypeInfo = PrimitiveInfo::Create<byte>("byte");

	/** Register TypeInfo for int16 */
	const PrimitiveInfo TypeOf<int16>::StaticTypeInfo = PrimitiveInfo::Create<int16>("int16");

	/** Register TypeInfo for int32 */
	const PrimitiveInfo TypeOf<int32>::StaticTypeInfo = PrimitiveInfo::Create<int32>("int32");

	/** Register TypeInfo for int64 */
	const PrimitiveInfo TypeOf<int64>::StaticTypeInfo = PrimitiveInfo::Create<int64>("int64");

	/** Register TypeInfo for uint16 */
	const PrimitiveInfo TypeOf<uint16>::StaticTypeInfo = PrimitiveInfo::Create<uint16>("uint16");

	/** Register TypeInfo for uint32 */
	const PrimitiveInfo TypeOf<uint32>::StaticTypeInfo = PrimitiveInfo::Create<uint32>("uint32");

	/** Register TypeInfo for uint64 */
	const PrimitiveInfo TypeOf<uint64>::StaticTypeInfo = PrimitiveInfo::Create<uint64>("uint64");

	/** Register TypeInfo for float */
	const PrimitiveInfo TypeOf<float>::StaticTypeInfo = PrimitiveInfo::Create<float>("float");

	/** Register TypeInfo for double */
	const PrimitiveInfo TypeOf<double>::StaticTypeInfo = PrimitiveInfo::Create<double>("double");
}