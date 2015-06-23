// TypeTraits.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <type_traits>

//////////////////
///   Macros   ///

/** This macro makes std::enable_if a little easier on the eyes.
* It has to be a variadic macro, because otherwise the preprocessor interprets
* any commas in the template argument as separate macro arguments, and throws an error. 
* Unfortunately, Visual Studio's Intellisense has a hard time parsing this, and usually makes
* at least half of the argument uncolored. */
#define WHERE(...) typename = std::enable_if_t<__VA_ARGS__>
