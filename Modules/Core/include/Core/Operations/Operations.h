// Operations.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** "Operations" are a collection of generic functions that can be performed on polymorphic and non-polymorphic types.
* These functions can see through polymorphism (using the reflection system), so even if the visible type doesn't implement 
* the desired function, it can still be called if the derived type does. */
#pragma once

////////////////////////////////
///   Forward-declarations   ///

/** Defined in 'String.h' */
struct String;

/////////////////////
///   Functions   ///

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
AnyType* Construct();

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
AnyType* Copy(const AnyType& copy);

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
AnyType* Copy(AnyType&& move);

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
bool Assign(AnyType& value, const AnyType& copy);

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
bool Assign(AnyType& value, AnyType&& move);

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
bool Destroy(AnyType& value);

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
String ToString(const AnyType& value);

/** Defined in 'TypeInfo.h' */
template <typename AnyType>
String FromString(AnyType& value, const String& string);
