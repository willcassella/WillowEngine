// GHandle.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "GameObject.h"

namespace Willow
{
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
		GHandle(const T* value)
			: _id{ value ? value->GameObject::GetID() : 0 }
		{
			assert(!value || _id != 0 /** You may not add create a handle to a GameObject that has not been initialized. */);
		}
		GHandle(const T& value)
			: _id(value.GameObject::GetID())
		{
			assert(_id != 0 /** You may not add create a handle to a GameObject that has not been initialized. */);
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

	/** Convenient alias for Entity handles. */
	using EntityHandle = GHandle<Entity>;

	/** Convenient alias for Component handles. */
	using ComponentHandle = GHandle<Component>;
}
