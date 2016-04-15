// ResourceHandle.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Forwards/Resource.h"
#include "Path.h"

namespace willow
{
	/////////////////
	///   Types   ///

	/** Unique identifier for resources. */
	using ResourceID = uint32;

	template <class T>
	struct ResourceHandle final
	{
		///////////////////////
		///   Information   ///
	public:

		/** Only the ResourceManager is allowed to create ResourceHandles from ids. */
		friend ResourceManager;

		////////////////////////
		///   Constructors   ///
	public:

		ResourceHandle()
			: _id{ 0 }
		{
			// All done
		}
		ResourceHandle(std::nullptr_t)
			: ResourceHandle{}
		{
			// All done
		}
		ResourceHandle(Path path);

	private:

		explicit ResourceHandle(ResourceID id)
			: _id{ id }
		{
			// All done
		}

		///////////////////
		///   Methods   ///
	public:

		String ToString() const;

		void ToArchive(ArchiveWriter& writer) const;

		void FromArchive(const ArchiveReader& reader);

		ResourceID get_id() const
		{
			return this->_id;
		}

		/////////////////////
		///   Operators   ///
	public:

		ResourceHandle& operator=(Path path);

		friend bool operator==(const ResourceHandle& lhs, const ResourceHandle& rhs)
		{
			return lhs._id == rhs._id;
		}
		friend bool operator!=(const ResourceHandle& lhs, const ResourceHandle& rhs)
		{
			return lhs._id != rhs._id;
		}
		bool operator==(std::nullptr_t)
		{
			return this->_id == 0;
		}
		bool operator!=(std::nullptr_t)
		{
			return this->_id != 0;
		}
		operator bool() const
		{
			return this->_id != 0;
		}

		////////////////
		///   Data   ///
	private:

		ResourceID _id;
	};
}

//////////////////////
///   Reflection   ///

namespace Implementation
{
	/** Reflection operation for 'ResourceHandle' */
	template <class T>
	struct TypeOf < willow::ResourceHandle<T> >
	{
		/** Defined below. */
		static const StructInfo StaticTypeInfo;

		static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		static const StructInfo& Function(willow::ResourceHandle<T> /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	template <class T>
	const StructInfo TypeOf<willow::ResourceHandle<T>>::StaticTypeInfo = TypeInfoBuilder<willow::ResourceHandle<T>>("willow::ResourceHandle");
}