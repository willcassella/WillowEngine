// Archive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Resource.h"

namespace Willow
{
	/** Represents an Archive as a whole.
	* TODO: Make this extend "Resource" */
	class RESOURCE_API Archive : public Object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Object)

		//////////////////
		///   Fields   ///
	public:

		// TODO: Figure out a better way of doing this
		mutable Table<std::uintptr_t, void*> RefTable;

		///////////////////
		///   Methods   ///
	public:

		virtual bool Load(const Path& path) = 0;

		virtual bool Save(const Path& path) const = 0;

		template <typename T>
		void Serialize(const T& value)
		{
			this->AddRoot([&value](ArchiveWriter& writer)
			{
				::ToArchive(value, writer);
			});
		}

		template <typename T>
		void Deserialize(T& value)
		{
			this->GetRoot([&value](const ArchiveReader& reader)
			{
				::FromArchive(value, reader);
			});
		}

	private:

		virtual void AddRoot(FunctionView<void, ArchiveWriter&> handler) = 0;

		virtual void GetRoot(FunctionView<void, const ArchiveReader&> handler) const = 0;
	};
}
