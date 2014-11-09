// Resource.h
#pragma once

#include "Reflection\Reflection.h"

namespace Willow
{
	class UTILITY_API Resource
	{
		///////////////////////
		///   Information   ///
	public:
		
		template <class T> friend class ResourcePtr;

		////////////////////////
		///   Constructors   ///
	public:

		Resource(const String& path);
		virtual ~Resource();

		///////////////////
		///   Methods   ///
	public:

		String GetPath() const;
		
	private:

		static Resource* FindLoadedResource(const String& path);

		////////////////
		///   Data   ///
	private:

		const String _path;
		uint32 _refs = 0;
	};

	NON_REFLECTABLE(Willow::Resource)
}