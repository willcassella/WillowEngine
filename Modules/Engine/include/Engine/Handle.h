// Handle.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "GameObject.h"

namespace Willow
{
	/** Handle that can reference an object in a World, independent of frame. */
	template <class T>
	struct Handle final
	{
		///////////////////////
		///   Information   ///
	public:

		/** Different instantiations of Handle
		* need to access eachother's members. */
		template <typename F>
		friend struct Handle;

		REFLECTABLE_STRUCT

			////////////////////////
			///   Constructors   ///
	public:

		Handle()
			: _id{ 0 }
		{
			// All done
		}
		Handle(const T* value)
			: _id{ value ? value->GameObject::GetID() : 0 }
		{
			assert(!value || _id != 0 /** You may not add create a handle to a GameObject that has not been initialized. */);
		}
		Handle(const T& value)
			: _id{ value.GameObject::GetID() }
		{
			assert(_id != 0 /** You may not add create a handle to a GameObject that has not been initialized. */);
		}
		Handle(std::nullptr_t)
			: Handle{}
		{
			// All done
		}

		template <class F>
		explicit Handle(Handle<F> copy)
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
		Handle<F> CastTo() const
		{
			Handle<F> result;
			result._id = _id;
			return result;
		}

		/////////////////////
		///   Operators   ///
	public:

		/** Comparison operators. */
		friend bool operator==(Handle lhs, Handle rhs)
		{
			return lhs.GetID() == rhs.GetID();
		}
		friend bool operator!=(Handle lhs, Handle rhs)
		{
			return lhs.GetID() != rhs.GetID();
		}
		friend bool operator==(Handle lhs, std::nullptr_t)
		{
			return lhs.GetID() == 0;
		}
		friend bool operator!=(Handle lhs, std::nullptr_t)
		{
			return lhs.GetID() != 0;
		}

		////////////////
		///   Data   ///
	private:

		GameObject::ID _id;
	};

	/** Convenient alias for Entity handles. */
	using EntityHandle = Handle<Entity>;

	/** Convenient alias for Component handles. */
	using ComponentHandle = Handle<Component>;

	template <class T>
	BUILD_TEMPLATE_REFLECTION(Handle, T);
}
