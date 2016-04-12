// GHandle.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "GameObject.h"

namespace Willow
{
	/** Handle that can reference an object in a World, independent of frame. */
	template <class T>
	struct GHandle final
	{
		///////////////////////
		///   Information   ///
	public:

		/** Different instantiations of GHandle
		* need to access eachother's members. */
		template <typename F>
		friend struct GHandle;

		REFLECTABLE_STRUCT

			////////////////////////
			///   Constructors   ///
	public:

		GHandle()
			: _id{ 0 }
		{
			// All done
		}
		GHandle(const T* value)
			: _id{ value ? value->GameObject::GetID() : 0 }
		{
			assert(!value || _id != 0 /** You may not add create a handle to a GameObject that has not been initialized. */);
		}
		GHandle(const T& value)
			: _id{ value.GameObject::GetID() }
		{
			assert(_id != 0 /** You may not add create a handle to a GameObject that has not been initialized. */);
		}
		GHandle(std::nullptr_t)
			: GHandle{}
		{
			// All done
		}

		template <class F>
		explicit GHandle(GHandle<F> copy)
			: _id{ copy.GetID() }
		{
			static_assert(std::is_base_of<T, F>::value, "Incompatible handle type.");
		}

		///////////////////
		///   Methods   ///
	public:

		void ToArchive(ArchiveWriter& writer) const
		{
			writer.SetValue(_id);
		}

		void FromArchive(const ArchiveReader& reader)
		{
			reader.GetValue(_id);
		}

		/** Returns the ID of the object this handle currently refers to. */
		FORCEINLINE GameObject::ID GetID() const
		{
			return _id;
		}

		/** Returns whether this handle does not refer to an object. */
		FORCEINLINE bool IsNull() const
		{
			return _id == 0;
		}

		/** Explicitly casts this handle to a handle of the given type. */
		template <class F>
		GHandle<F> CastTo() const
		{
			GHandle<F> result;
			result._id = _id;
			return result;
		}

		/////////////////////
		///   Operators   ///
	public:

		/** Comparison operators. */
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

	template <class T>
	BUILD_TEMPLATE_REFLECTION(GHandle, T);
}
