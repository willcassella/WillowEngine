// BinaryFile.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Resource.h"

namespace Willow
{
	class RESOURCE_API BinaryFile final : public Resource
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Resource)

		////////////////////////
		///   Constructors   ///
	public:

		BinaryFile(const Path& path);

		///////////////////
		///   Methods   ///
	public:

		const byte* GetData() const;

		/////////////////
		///   Data   ///
	private:

		DynamicBuffer _data;
	};
}
