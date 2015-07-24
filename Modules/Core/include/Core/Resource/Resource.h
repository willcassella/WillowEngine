// Resource.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Reflection/Reflection.h"
#include "../Object.h"
#include "../String.h"

class CORE_API Resource : public Object
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS;
	EXTENDS(Object);
	template <class T> friend struct ResourcePtr;

	////////////////////////
	///   Constructors   ///
public:

	Resource(const String& uri);
	Resource(const Resource& copy) = delete;
	Resource(Resource&& move) = delete;
	~Resource() override;

	///////////////////
	///   Methods   ///
public:

	/** Returns the Unique Resource Identifier for this Resource. */
	FORCEINLINE const String& GetURI() const
	{
		return _uri;
	}

	static Resource* FindLoadedResource(const String& uri);

	/////////////////////
	///   Operators   ///
public:

	Resource& operator=(const Resource& copy) = delete;
	Resource& operator=(Resource&& move) = delete;

	////////////////
	///   Data   ///
private:

	String _uri;
	uint32 _refs;
};
