// Reflection.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
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

/** Defined in 'Reflection/PropertyInfo.h' */
struct PropertyInfo;

/** Defined in 'Reflection/PropertyInfo.h' */
struct Property;

/** Defined in 'Reflection/PropertyInfo.h' */
struct ImmutableProperty;

/////////////////////
///   Functions   ///

/** Defined in 'Reflection/Reflection.h' */
template <typename T>
const auto& TypeOf();

/** Defined in 'Reflection/Reflection.h' */
template <typename T>
const auto& TypeOf(const T& value);

/** Defined in 'TypeInfo.h' */
template <typename TargetT, typename T>
auto* Cast(T& value);

/** r-value references cannot be safely casted. */
template <typename TargetT, typename T>
void Cast(const T&& value) = delete;
