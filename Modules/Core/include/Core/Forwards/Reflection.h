// Reflection.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

/////////////////
///   Types   ///

/** Defined in 'Reflection/TypeInfo.h' */
class TypeInfo;

/** Defined in 'Reflection/VoidInfo.h' */
class VoidInfo;

/** Defined in 'Reflection/PrimitiveInfo.h' */
class PrimitiveInfo;

/** Defined in 'Reflection/EnumInfo.h' */
class EnumInfo;

/** Defined in 'Reflection/PointerInfo.h' */
class PointerInfo;

/** Defined in 'Reflection/CompoundInfo.h' */
class CompoundInfo;

/** Defined in 'Reflection/StructInfo.h' */
class StructInfo;

/** Defined in 'Reflection/ClassInfo.h' */
class ClassInfo;

/** Defined in 'Reflection/InterfaceInfo.h' */
class InterfaceInfo;

/** Defined in 'Reflection/Variant.h' */
struct Variant;

/** Defined in 'Reflection/Variant.h' */
struct ImmutableVariant;

/////////////////////
///   Functions   ///

/** Defined in 'Reflection/Reflection.h' */
template <typename AnyType>
const auto& TypeOf(const AnyType& value);

/** Defined in 'Reflection/Reflection.h' */
template <typename AnyType>
const auto& TypeOf();

/** Defined in 'TypeInfo.h' */
template <typename TargetType, typename AnyType>
TargetType* Cast(AnyType& value);

/** Defined in 'TypeInfo.h' */
template <typename TargetType, typename AnyType>
const TargetType* Cast(const AnyType& value);

/** r-value references cannot be safely casted */
template <typename TargetType, typename AnyType>
auto Cast(AnyType&& value) = delete;
