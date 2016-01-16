// Containers.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../env.h"

/////////////////
///   Types   ///

/** Defined in 'Containers/String.h' */
struct String;

/** Defined in 'Containers/DynamicBuffer.h' */
struct DynamicBuffer;

/** Defined in 'Containers/StaticBuffer.h' */
template <uint32 Size>
struct StaticBuffer;

/** Defined in 'Containers/Array.h' */
template <typename T>
struct Array;

/** Defined in 'Containers/List.h' */
template <typename T>
struct List;

/** Defined in 'Containers/Queue.h' */
template <typename T>
struct Queue;

/** Defined in 'Containers/Stack.h' */
template <typename T>
struct Stack;

/** Defined in 'Containers/Pair.h' */
template <typename A, typename B>
struct Pair;

/** Defined in 'Containers/Table.h' */
template <typename KeyT, typename ValueT>
struct Table;

/** Defined in 'Containers/Tuple.h' */
template <typename ... T>
struct Tuple;

/** Defined in 'Containers/Nullable.h' */
template <typename T>
struct Nullable;

/** Defined in 'Containers/Union.h' */
template <typename ... T>
struct Union;
