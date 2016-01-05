// ToArchive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Operations.h"
#include "../ArchiveNode.h"

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
		FORCEINLINE static auto Impl(Preferred, const F& value, ArchiveNode& node) -> decltype(value.F::ToArchive(node))
		{
			return value.ToArchive(node);
		}

		/** Implementation for types that do not defined their own 'ToArchive' method. */
		template <typename F>
		FORCEINLINE static auto Impl(Fallback, const F& value, ArchiveNode& node) -> void
		{
			Default::ToArchive(value, node);
		}

	public:

		/** Entry point for the implementatin. */
		FORCEINLINE static void Function(const T& value, ArchiveNode& node)
		{
			Impl(0, value, node);
		}
	};

	/** Implementation of 'ToArchive' for Array. */
	template <typename T>
	struct ToArchive < Array<T> > final
	{
		FORCEINLINE static void Function(const Array<T>& array, ArchiveNode& node)
		{
			for (const auto& item : array)
			{
				auto child = node.AddChild("item");
				::ToArchive(item, *child);
			}
		}
	};
}

/////////////////////
///   Functions   ///

/** Serializes the given value to the given archive node. */
template <typename T>
FORCEINLINE void ToArchive(const T& value, ArchiveNode& node)
{
	Implementation::ToArchive<T>::Function(value, node);
}
