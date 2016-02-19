// SerializeableStruct.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <type_traits>
#include "../Forwards/Operations.h"

/** Convenience class for serializeable structs to inherit. If you don't want to/can't use this,
* you can just implement the 'ToArchive' and 'FromArchive' member functions yourself. */
template <class T>
struct SerializeableStruct
{
	////////////////////////
	///   Constructors   ///
public:

	constexpr SerializeableStruct()
	{
		static_assert(std::is_base_of<SerializeableStruct, T>::value, "'SerializeableStruct' relies on the curiously recurring template pattern.");
	}

	///////////////////
	///   Methods   ///
public:

	/** Serializes the state of this struct to the given Archive. */
	void ToArchive(ArchiveWriter& writer) const
	{
		Operations::Default::ToArchive(static_cast<const T&>(*this), writer);
	}

	/** Deserializes the state of this struct from the given Archive. */
	void FromArchive(const ArchiveReader& reader)
	{
		Operations::Default::FromArchive(static_cast<T&>(*this), reader);
	}
};
