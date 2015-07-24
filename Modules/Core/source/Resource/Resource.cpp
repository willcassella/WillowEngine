// Resource.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Core/Resource/Resource.h"
#include "../../include/Core/Reflection/ClassInfo.h"
#include "../../include/Core/Containers/Table.h"

///////////////////
///   Statics   ///

Table<String, Resource*> resourceTable;

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Resource);

////////////////////////
///   Constructors   ///

Resource::Resource(const String& uri)
	: _uri(uri), _refs(0)
{
	resourceTable[_uri] = this;
}

Resource::~Resource()
{
	resourceTable[_uri] = nullptr;
}

Resource* Resource::FindLoadedResource(const String& uri)
{
	auto res = resourceTable.Find(uri);

	if (res)
	{
		return *res;
	}
	else
	{
		return nullptr;
	}
}