// Handle.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "GameObject.h"

namespace willow
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

		////////////////////////
		///   Constructors   ///
	public:

		Handle()
			: _id{ 0 }
		{
			// All done
		}
		Handle(const T* value)
			: _id{ value ? value->GameObject::get_id() : 0 }
		{
			assert(!value || this->_id != 0 /** You may not add create a handle to a GameObject that has not been initialized. */);
		}
		Handle(const T& value)
			: _id{ value.GameObject::get_id() }
		{
			assert(this->_id != 0 /** You may not add create a handle to a GameObject that has not been initialized. */);
		}
		Handle(std::nullptr_t)
			: Handle{}
		{
			// All done
		}

		template <class F>
		explicit Handle(Handle<F> copy)
			: _id{ copy.get_id() }
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
		FORCEINLINE GameObject::ID get_id() const
		{
			return this->_id;
		}

		/** Returns whether this handle does not refer to an object. */
		FORCEINLINE bool is_null() const
		{
			return this->_id == 0;
		}

		/** Explicitly casts this handle to a handle of the given type. */
		template <class F>
		Handle<F> cast_to() const
		{
			Handle<F> result;
			result._id = this->_id;
			return result;
		}

		T* get_object(World& world) const;

		const T* get_object(const World& world) const;

		/////////////////////
		///   Operators   ///
	public:

		/** Comparison operators. */
		friend bool operator==(Handle lhs, Handle rhs)
		{
			return lhs.get_id() == rhs.get_id();
		}
		friend bool operator!=(Handle lhs, Handle rhs)
		{
			return lhs.get_id() != rhs.get_id();
		}
		friend bool operator==(Handle lhs, std::nullptr_t)
		{
			return lhs.get_id() == 0;
		}
		friend bool operator!=(Handle lhs, std::nullptr_t)
		{
			return lhs.get_id() != 0;
		}

		////////////////
		///   Data   ///
	private:

		GameObject::ID _id;
	};
}

/////////////////////
///   Operators   ///

namespace Implementation
{
	/** Implement 'TypeOf' operation for Handle<T> */
	template <class T>
	struct TypeOf< willow::Handle<T> > final
	{
		/** Defined below. */
		static const StructInfo StaticTypeInfo;

		static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		static const StructInfo& Function(willow::Handle<T> /*value*/)
		{
			return StaticTypeInfo;
		}
	};
	
	/** Register type information for Handle<T> */
	template <class T>
	const StructInfo TypeOf<willow::Handle<T>>::StaticTypeInfo = TypeInfoBuilder<willow::Handle<T>>("willow::Handle");
}
