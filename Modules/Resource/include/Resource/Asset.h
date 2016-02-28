// Asset.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Reflection/ClassInfo.h>
#include "Path.h"

namespace Willow
{
	class RESOURCE_API Asset : public Object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Object)

		/////////////////
		///   Types   ///
	public:

		/** Uniquely identifies each asset. */
		using ID = uint32;

		////////////////////////
		///   Constructors   ///
	public:

		Asset(const Path& path);

		///////////////////
		///   Methods   ///
	public:

		/** Returns the path for this Asset. */
		FORCEINLINE const Path& GetPath() const
		{
			return _path;
		}

		/** Returns the Unique ID for this asset. */
		FORCEINLINE ID GetID() const
		{
			return _id;
		}

		////////////////
		///   Data   ///
	private:

		Path _path;
		ID _id;
	};
}
