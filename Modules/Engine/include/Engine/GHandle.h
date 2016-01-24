// GHandle.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "GameObject.h"

/** Handle that can reference an object in a World, independent of frame. */
template <class T>
struct GHandle final
{
	////////////////////////
	///   Constructors   ///
public:

	GHandle()
		: _id(0)
	{
		// All done
	}
	GHandle(T& value)
		: _id(value.GetID())
	{
		assert(_id != 0 /** You may not add create a handle to an Object that does not exist within the world. */);
	}
	GHandle(std::nullptr_t)
		: GHandle()
	{
		// All done
	}

	template <class F>
	GHandle(GHandle<F> copy)
		: _id(copy.GetID())
	{
		static_assert(std::is_base_of<T, F>::value, "Incompatible handle types");
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the ID of the object this handle currently refers to. */
	FORCEINLINE GameObject::ID GetID() const
	{
		return _id;
	}

	/** Returns whether this handle refers to an object at all. */
	FORCEINLINE bool IsNull() const
	{
		return _id == 0;
	}

	/////////////////////
	///   Operators   ///
public:

	friend bool operator==(GHandle lhs, GHandle rhs)
	{
		return lhs.GetID() == rhs.GetID();
	}
	friend bool operator!=(GHandle lhs, GHandle rhs)
	{
		return lhs.GetID() != rhs.GetID();
	}
	friend bool operator==(GHandle lhs, std::nullptr_t)
	{
		return lhs.GetID() == 0;
	}
	friend bool operator!=(GHandle lhs, std::nullptr_t)
	{
		return lhs.GetID() != 0;
	}

	////////////////
	///   Data   ///
private:

	GameObject::ID _id;
};
