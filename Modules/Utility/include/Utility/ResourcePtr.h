// ResourcePtr.h
#pragma once

#include "Resource.h"

namespace Willow
{
	/** An opaque pointer to a resource
	* WARNING: ResourceType must be a subclass of Resource */
	template <class ResourceType>
	class ResourcePtr : public object
	{
		///////////////////////
		///   Information   ///

		REFLECTABLE
		EXTENDS(object)

		////////////////////////
		///   Constructors   ///
	public:

		ResourcePtr(const String& path = "")
		{
			this->AssignResource(path);
		}
		ResourcePtr(const ResourcePtr<ResourceType>& copy)
		{
			this->_resource = copy._resource;
			if (_resource)
			{
				_resource->_refs++;
			}
		}
		ResourcePtr(ResourcePtr<ResourceType>&& other)
		{
			this->_resource = other._resource;
			other._resource = nullptr;
		}
		~ResourcePtr()
		{
			this->DeassignResource();
		}

		///////////////////
		///   Methods   ///
	public:

		void MakeUnique()
		{
			// @TODO: Make this resource pointer unique
		}
		bool IsLoaded() const
		{
			// @TODO: Maybe do something else with this?
			return _resource != nullptr;
		}

	private:

		void AssignResource(const String& path)
		{
			// Assign to a new resource
			if (path.IsNullOrEmpty())
			{
				this->_resource = nullptr;
				return;
			}

			// Check if this resource has been already created
			Resource* res = Resource::FindLoadedResource(path);
			if (!res)
			{
				// Create a new resource
				res = new ResourceType(path);
			}

			// increase the ref count and point to the resource
			this->_resource = (ResourceType*)res;
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

		ResourceType& operator*()
		{
			return *_resource;
		}
		const ResourceType& operator*() const
		{
			return *_resource;
		}
		ResourceType* operator->()
		{
			return _resource;
		}
		const ResourceType* operator->() const
		{
			return _resource;
		}
		ResourcePtr<ResourceType>& operator=(const String& path)
		{
			this->DeassignResource();
			this->AssignResource(path);
			return *this;
		}
		ResourcePtr<ResourceType>& operator=(const ResourcePtr<ResourceType>& rhs)
		{
			if (this != &rhs)
			{
				this->DeassignResource();
				this->_resource = rhs._resource;

				if (_resource)
				{
					_resource->_refs++;
				}
			}
			return *this;
		}
		ResourcePtr<ResourceType>& operator=(ResourcePtr<ResourceType>&& other)
		{
			if (this != &other)
			{
				this->DeassignResource();
				this->_resource = other._resource;
				other._resource = nullptr;
			}
			return *this;
		}
		bool operator==(const ResourcePtr<ResourceType>& rhs) const
		{
			return _resource == rhs._resource;
		}
		bool operator!=(const ResourcePtr<ResourceType>& rhs) const
		{
			return _resource != rhs._resource;
		}

		////////////////
		///   Data   ///
	private:

		ResourceType* _resource = nullptr;
	};

	BEGIN_TEMPLATE_INFO(Willow::ResourcePtr, typename T)
	HAS_FACTORY
	END_REFLECTION_INFO
}