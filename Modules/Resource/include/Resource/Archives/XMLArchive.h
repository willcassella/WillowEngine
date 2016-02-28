// XMLArhive.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <memory>
#include "../Archive.h"

namespace Willow
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

		bool Load(const Path& path) override;

		bool Save(const Path& path) const override;

	private:

		void AddRoot(FunctionView<void, ArchiveWriter&> handler) override;

		void GetRoot(FunctionView<void, const ArchiveReader&> handler) const override;

		////////////////
		///   Data   ///
	private:

		std::unique_ptr<struct XMLDoc> _doc;
	};
}
