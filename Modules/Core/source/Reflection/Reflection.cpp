// Reflection.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Reflection/VoidInfo.h"
#include "../../include/Core/Reflection/PrimitiveInfo.h"
#include "../../include/Core/Reflection/PointerInfo.h"
#include "../../include/Core/Reflection/StructInfo.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/////////////////////////////
	///   Fundamental Types   ///

	/** Register TypeInfo for void */
	const VoidInfo TypeOf<void>::StaticTypeInfo = TypeInfoBuilder<void>();

	/** Register TypeInfo for std::nullptr_t */
	const PointerInfo TypeOf<std::nullptr_t>::StaticTypeInfo = TypeInfoBuilder<std::nullptr_t>();

	///////////////////////////
	///   Primitive Types   ///

	/** Register TypeInfo for bool */
	const PrimitiveInfo TypeOf<bool>::StaticTypeInfo = TypeInfoBuilder<bool>("bool");

	/** Register TypeInfo for char */
	const PrimitiveInfo TypeOf<char>::StaticTypeInfo = TypeInfoBuilder<char>("char");

	/** Register TypeInfo for byte */
	const PrimitiveInfo TypeOf<byte>::StaticTypeInfo = TypeInfoBuilder<byte>("byte");

	/** Register TypeInfo for int16 */
	const PrimitiveInfo TypeOf<int16>::StaticTypeInfo = TypeInfoBuilder<int16>("int16");

	/** Register TypeInfo for int32 */
	const PrimitiveInfo TypeOf<int32>::StaticTypeInfo = TypeInfoBuilder<int32>("int32");

	/** Register TypeInfo for int64 */
	const PrimitiveInfo TypeOf<int64>::StaticTypeInfo = TypeInfoBuilder<int64>("int64");

	/** Register TypeInfo for uint16 */
	const PrimitiveInfo TypeOf<uint16>::StaticTypeInfo = TypeInfoBuilder<uint16>("uint16");

	/** Register TypeInfo for uint32 */
	const PrimitiveInfo TypeOf<uint32>::StaticTypeInfo = TypeInfoBuilder<uint32>("uint32");

	/** Register TypeInfo for uint64 */
	const PrimitiveInfo TypeOf<uint64>::StaticTypeInfo = TypeInfoBuilder<uint64>("uint64");

	/** Register TypeInfo for float */
	const PrimitiveInfo TypeOf<float>::StaticTypeInfo = TypeInfoBuilder<float>("float");

	/** Register TypeInfo for double */
	const PrimitiveInfo TypeOf<double>::StaticTypeInfo = TypeInfoBuilder<double>("double");

	/** Register TypeInfo for long double */
	const PrimitiveInfo TypeOf<long double>::StaticTypeInfo = TypeInfoBuilder<long double>("long double");

	/** Register TypeInfo for 'String' */
	const StructInfo TypeOf<String>::StaticTypeInfo = TypeInfoBuilder<String>("String");
}