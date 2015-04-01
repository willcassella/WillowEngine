// ResourceHandle.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../Reflection/Registration.h"

/////////////////
///   Types   ///

/** An opaque pointer to a Resource
* NOTE: ResourceType must be a subclass of 'Resource' */
template <class ResourceType>
struct ResourceHandle
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT;

	////////////////////////
	///   Constructors   ///
public:

	ResourceHandle()
		: _resource(nullptr)
	{
		// All done
	}
	ResourceHandle(const String& path)
		: _resource(nullptr)
	{
		AssignResource(path);
	}
	ResourceHandle(const ResourceHandle& copy)
		: _resource(copy._resource)
	{
		if (_resource)
		{
			_resource->_refs++;
		}
	}
	ResourceHandle(ResourceHandle&& move)
		: _resource(move._resource)
	{
		move._resource = nullptr;
	}
	~ResourceHandle()
	{
		DeassignResource();
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns whether the SystemResource this ResourceHandle points to has been fully loaded */
	bool IsLoaded() const
	{
		// @TODO: Maybe implemented a smarter version of this (to enable loading on a separate thread)
		return _resource != nullptr;
	}

private:

	/** Assigns this ResourceHandle to the system resource at the given path */
	void AssignResource(const String& path)
	{
		// Assign to a new resource
		if (path.IsEmpty())
		{
			_resource = nullptr;
			return;
		}

		// Check if this resource has been already created
		SystemResource* res = SystemResource::FindLoadedResource(path);
		if (!res)
		{
			// Create a new resource
			res = new ResourceType(path);
		}

		// increase the ref count and point to the resource
		_resource = (ResourceType*)res;
		_resource->_refs++;
	}

	void DeassignResource()
	{
		if (_resource)
		{
			_resource->_refs--;

			if (_resource->_refs <= 0)
			{
				delete _resource;
			}
		}
	}

	/////////////////////
	///   Operators   ///
public:

	const ResourceType& operator*() const
	{
		return *_resource;
	}
	const ResourceType* operator->() const
	{
		return _resource;
	}
	ResourceHandle& operator=(const String& path)
	{
		this->DeassignResource();
		this->AssignResource(path);
		return This;
	}
	ResourceHandle& operator=(const ResourceHandle& copy)
	{
		if (this != &copy)
		{
			DeassignResource();
			_resource = copy._resource;

			if (_resource)
			{
				_resource->_refs++;
			}
		}
		return This;
	}
	ResourceHandle& operator=(ResourceHandle&& move)
	{
		if (this != &move)
		{
			this->DeassignResource();
			this->_resource = move._resource;
			move._resource = nullptr;
		}
		return *this;
	}

	friend inline bool operator==(const ResourceHandle& lhs, const ResourceHandle& rhs)
	{
		return lhs._resource == rhs._resource;
	}
	friend inline bool operator!=(const ResourceHandle& lhs, const ResourceHandle& rhs)
	{
		return lhs._resource != rhs._resource;
	}

	////////////////
	///   Data   ///
private:

	ResourceType* _resource;
};

//////////////////////
///   Reflection   ///

template <class ResourceType>
const ClassInfo ResourceHandle<ResourceType>::StaticTypeInfo = ClassInfo::Create<ResourceType>(String::Format("ResourceHandle<@>", TypeOf<ResourceType>().GetName()));