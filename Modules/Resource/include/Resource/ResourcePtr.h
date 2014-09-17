// ResourcePtr.h
#pragma once

#include "Resource.h"

namespace Willow
{
	// @TODO: Implement rule of 5
	template <class T> // T must be a child of Resource
	class ResourcePtr
	{
		////////////////////////
		///   Constructors   ///
	public:

		ResourcePtr(const String& path = "")
		{
			AssignResource(path);
		}
		~ResourcePtr()
		{
			DeassignResource();
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
			return _resource != nullptr;
		}

	private:

		void AssignResource(const String& path)
		{
			// Deassign from old resource (if any)
			DeassignResource();

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
		void operator=(const String& path)
		{
			AssignResource(path);
		}
		void operator=(const ResourcePtr<T>& rhs)
		{
			this->_resource = rhs._resource;

			if (_resource)
			{
				_resource->_refs++;
			}
		}

		////////////////
		///   Data   ///
	private:

		T* _resource = nullptr;
	};
}