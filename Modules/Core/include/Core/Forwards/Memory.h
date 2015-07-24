// Memory.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

/////////////////
///   Types   ///

/** Defined in 'Memory/OwnerPtr.h' */
template <typename T>
struct OwnerPtr;

/** Defined in 'Memory/SharedPtr.h' */
template <typename T>
struct SharedPtr;

/** Defined in 'Memory/Ptr.h' */
template <class T>
struct Ptr;

/** Defined in 'Memory/New.h' */
template <typename T>
struct NewPtr;

/////////////////////
///   Functions   ///

/** Defined in 'Memory/New.h' */
template <typename T, typename ... Arg>
NewPtr<T> New(Arg&& ... args);
