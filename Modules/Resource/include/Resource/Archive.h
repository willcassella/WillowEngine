// Archive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Object.h>
#include <Core/Operations/FromArchive.h>
#include "Path.h"

namespace willow
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
		mutable Table<ArchiveRefID, void*> RefTable;

		///////////////////
		///   Methods   ///
	public:

		virtual bool load(const Path& path) = 0;

		virtual bool save(const Path& path) const = 0;

		template <typename T>
		void serialize(const T& value)
		{
			this->add_root([&value](ArchiveWriter& writer)
			{
				::ToArchive(value, writer);
			});
		}

		template <typename T>
		void deserialize(T& value)
		{
			this->get_root([&value](const ArchiveReader& reader)
			{
				::FromArchive(value, reader);
			});
		}

	private:

		virtual void add_root(FunctionView<void, ArchiveWriter&> handler) = 0;

		virtual void get_root(FunctionView<void, const ArchiveReader&> handler) const = 0;
	};
}
