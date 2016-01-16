// FromArchive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Operations.h"

//////////////////////////
///   Implementation   ///

namespace Implementation
{
	/** Generic implementation of 'FromArchive'. */
	template <typename T>
	struct FromArchive final
	{
	private:

		/** Implementation for if the type defines its own 'FromArchive' function (preferred). */
		template <typename F>
		FORCEINLINE static auto Impl(Preferred, F& value, const ArchiveNode& node) -> decltype(value.F::FromArchive(node))
		{
			return value.FromArchive(node);
		}

		/** Implementation for if the type does not define its own 'FromArchive' function (fallback). */
		template <typename F>
		FORCEINLINE static auto Impl(Fallback, F& value, const ArchiveNode& node) -> void
		{
			Default::FromArchive(value, node);
		}

	public:

		/** Entry point for the implementation. */
		FORCEINLINE static void Function(T& value, const ArchiveNode& node)
		{
			Impl(0, value, node);
		}
	};
}

/////////////////////
///   Functions   ///

/** TODO: Documentation */
template <typename T>
FORCEINLINE void FromArchive(T& value, const ArchiveNode& node)
{
	Implementation::FromArchive<T>::Function(value, node);
}
