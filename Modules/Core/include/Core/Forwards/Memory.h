// Memory.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

/////////////////
///   Types   ///

/** Defined in 'Memory/MemoryManager.h' */
struct MemoryManager;

/** Defined in 'Memory/ReferenceCounter.h' */
struct ReferenceCounter;

/** Defined in 'Memory/Pointers/Owned.h' */
template <typename T>
struct Owned;

/** Defined in 'Memory/Pointers/Weak.h' */
template <class T>
struct Weak;

/** Defined in 'Memory/Pointers/Borrowed.h' */
template <class T>
struct Borrowed;

/////////////////////
///   Functions   ///

/** Defined in 'Memory/New.h' */
template <typename T, typename ... Arg>
Owned<T> New(Arg&& ... args);
