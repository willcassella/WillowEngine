// ToArchive.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Operations.h"
#include "../ArchNode.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Generic implementation of 'ToArchive' */
	template <typename T>
	struct ToArchive final
	{
	private:

		/** Implementation for types that define their own 'ToArchive' method. */
		template <typename F>
		FORCEINLINE static auto Impl(Preferred, const F& value, ArchNode& node) -> decltype(value.ToArchive(node))
		{
			return value.ToArchive(node);
		}

		/** Implementation for types that do not defined their own 'ToArchive' method. */
		template <typename F>
		FORCEINLINE static auto Impl(Fallback, const F& value, ArchNode& node) -> void
		{
			Default::ToArchive(value, node);
		}

	public:

		/** Entry point for the implementatin. */
		FORCEINLINE static void Function(const T& value, ArchNode& node)
		{
			Impl(0, value, node);
		}
	};
}

/////////////////////
///   Functions   ///

/** Serializes the given value to the given archive node. */
template <typename T>
FORCEINLINE void ToArchive(const T& value, ArchNode& node)
{
	Implementation::ToArchive<T>::Function(value, node);
}
