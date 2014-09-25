// ResourcePtr.h
#pragma once

#include "Resource.h"

namespace Willow
{
	template <class T> // T must be a child of Resource
	class ResourcePtr
	{
		////////////////////////
		///   Constructors   ///
	public:

		ResourcePtr(const String& path = "")
		{
			this->AssignResource(path);
		}
		ResourcePtr(const ResourcePtr& copy)
		{
			this->_resource = copy._resource;
			if (_resource)
			{
				_resource->_refs++;
			}
		}
		ResourcePtr(ResourcePtr&& other)
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
			// Make this resource pointer unique
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
				res = new T(path);
			}

			// increase the ref count and point to the resource
			this->_resource = (T*)res;
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

		T& operator*()
		{
			return *_resource;
		}
		const T& operator*() const
		{
			return *_resource;
		}
		T* operator->()
		{
			return _resource;
		}
		const T* operator->() const
		{
			return _resource;
		}
		ResourcePtr<T>& operator=(const String& path)
		{
			this->DeassignResource();
			this->AssignResource(path);
			return *this;
		}
		ResourcePtr<T>& operator=(const ResourcePtr<T>& rhs)
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
		ResourcePtr<T>& operator=(ResourcePtr<T>&& other)
		{
			if (this != &other)
			{
				this->DeassignResource();
				this->_resource = other._resource;
				other._resource = nullptr;
			}
			return *this;
		}
		bool operator==(const ResourcePtr<T>& rhs) const
		{
			return _resource == rhs._resource;
		}
		bool operator!=(const ResourcePtr<T>& rhs) const
		{
			return _resource != rhs._resource;
		}

		////////////////
		///   Data   ///
	private:

		T* _resource = nullptr;
	};
}