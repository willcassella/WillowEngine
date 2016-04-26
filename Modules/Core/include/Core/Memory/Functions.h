// Functions.h
#pragma once

#include <utility>

/** Aligns the given offset to the given boundary.
* NOTE: 'boundary' must be a power of 2. */
inline std::size_t align_offset(std::size_t offset, std::size_t bound)
{
	return (offset + bound - 1) & ~(bound - 1);
}
