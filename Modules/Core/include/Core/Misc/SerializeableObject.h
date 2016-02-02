// SerializeableObject.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Forwards/Operations.h"
#include "../STDE/TypeTraits.h"

/** Convenience class for serializeable classes to inherit. If you don't want to/can't use this,
* you can just implement the 'ToArchive' and 'FromArchive' member functions yourself. */
template <class T>
class SerializeableObject
{
	////////////////////////
	///   Constructors   ///
public:

	constexpr SerializeableObject()
	{
		static_assert(std::is_base_of<SerializeableObject, T>::value, "'SerializeableObject' relies on the curiously recurring template pattern.");
	}
	virtual ~SerializeableObject() = 0;

	///////////////////
	///   Methods   ///
public:

	/** Serializes the state of this Object to an Archive. */
	virtual void ToArchive(ArchiveWriter& writer) const
	{
		Operations::Default::ToArchive(static_cast<const T&>(*this), writer);
	}

	/** Deserializes the state of this Object from an Archive. */
	virtual void FromArchive(const ArchiveReader& reader)
	{
		Operations::Default::FromArchive(static_cast<T&>(*this), reader);
	}
};

template <class T>
SerializeableObject<T>::~SerializeableObject()
{
	// SerializeableObject is abstract
}
