// Registration.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
/** This header contains all the macros for registering types */
#pragma once

#include "ClassInfo.h"
#include "StructInfo.h"
#include "InterfaceInfo.h"
#include "Factory.h"

//////////////////
///   Macros   ///

/** Put this macro in the source file of a struct you'd like to reflect
* NOTE: The struct must use the 'REFLECTABLE_STRUCT' flag in it's header */
#define STRUCT_REFLECTION(T) const ::StructInfo T::StaticTypeInfo = ::StructInfo::Create<T>(#T)

/** Put this macro into the source file of a class you'd like to reflect
* NOTE: The class muse use the 'REFLECTABLE_CLASS' flag in it's header */
#define CLASS_REFLECTION(T) const ::ClassInfo T::StaticTypeInfo = ::ClassInfo::Create<T>(#T)