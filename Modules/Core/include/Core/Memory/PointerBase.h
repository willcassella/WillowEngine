// PointerBase.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

/** Wraps smart pointer access. */
template <typename T>
struct PointerBase
{
	
};

/** Smart pointers used for non-nullable borrows. Will be used in the future. */
template <typename T>
using ref = T&;

/** Smart pointer used for nullable borrows. Will be used in the future. */
template <typename T>
using ptr = T*;

template <typename T>
using weak_ptr = T*;
