// Memory.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

/////////////////
///   Types   ///

/** Defined in 'Memory/MemoryBlockController.h' */
struct MemoryBlockController;

/** Defined in 'Memory/MemoryManager.h' */
struct MemoryManager;

/** Defined in 'Memory/New.h' */
template <typename T>
struct NewPtr;

/** Defined in 'Memory/UniquePtr.h' */
template <typename T>
struct UniquePtr;

/** Defined in 'Memory/Ptr.h' */
template <class T>
struct Ptr;

/////////////////////
///   Functions   ///

/** Defined in 'Memory/New.h' */
template <typename T, typename ... Arg>
NewPtr<T> New(Arg&& ... args);
