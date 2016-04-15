// XMLArhive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <memory>
#include "../Archive.h"

namespace willow
{
	class RESOURCE_API XMLArchive final : public Archive
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Archive)

		////////////////////////
		///   Constructors   ///
	public:

		XMLArchive();
		~XMLArchive();

		///////////////////
		///   Methods   ///
	public:

		bool load(const Path& path) override;

		bool save(const Path& path) const override;

	private:

		void add_root(FunctionView<void, ArchiveWriter&> handler) override;

		void get_root(FunctionView<void, const ArchiveReader&> handler) const override;

		////////////////
		///   Data   ///
	private:

		std::unique_ptr<struct XMLDoc> _doc;
	};
}
