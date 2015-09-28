// Memory.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

/////////////////
///   Types   ///

/** Defined in 'Memory/MemoryBlockHeader.h' */
struct MemoryBlockHeader;

/** Defined in 'Memory/MemoryManager.h' */
struct MemoryManager;

/** Defined in 'Memory/UniquePtr.h' */
template <typename T>
struct UniquePtr;

/** Defined in 'Memory/Ptr.h' */
template <class T>
struct Ptr;

/////////////////////
///   Functions   ///

/** Defined in 'Memory/UniquePtr.h' */
template <typename T, typename ... Arg>
UniquePtr<T> New(Arg&& ... args);
