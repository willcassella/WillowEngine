// AssetManager.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <memory>
#include <Core/Containers/Table.h>
#include "ResourceHandle.h"

namespace willow
{
	/////////////////
	///   Types   ///

	/** The status of the resource. */
	enum class ResourceStatus : byte
	{
		/** The resource has not yet begun loading. */
		Not_Loaded,

		/** The resource is currently in the process of loading. */
		Loading,

		/** The resource has loaded and is ready for use. */
		Loaded,
	};

	/** Singleton responsible for loading and unloading assets as they are needed. */
	class RESOURCE_API ResourceManager final
	{
		/////////////////
		///   Types   ///
	public:

		/** Information about a resource. */
		struct ResourceInfoBase
		{
			////////////////////////
			///   Constructors   ///
		public:

			ResourceInfoBase() = default;
			ResourceInfoBase(const ResourceInfoBase& copy) = delete;
			virtual ~ResourceInfoBase() = default;

			///////////////////
			///   Methods   ///
		public:

			/** Returns the type of resource. */
			virtual const TypeInfo& get_resource_type() const = 0;

			/** Returns the status of this Resource. */
			virtual ResourceStatus get_status() const = 0;

			/** Returns whether this Resource was loaded from a path. */
			virtual bool loaded_from_path() const = 0;

			/** Returns the path to the given resource.
			* NOTE: If this resource was not loaded from a path, returns 'null'. */
			virtual Path get_path() const = 0;
		};

		/** Information about a type of resource. */
		template <class T>
		struct TResourceInfo : ResourceInfoBase
		{
			////////////////////////
			///   Constructors   ///
		public:

			TResourceInfo()
				: _status{ ResourceStatus::Not_Loaded }
			{
				// All done
			}
			~TResourceInfo()
			{
				assert(this->get_status() == ResourceStatus::Loaded);
				this->_resource.template GetPointer<T>()->~T();
			}

			///////////////////
			///   Methods   ///
		public:

			const TypeInfo& get_resource_type() const final override
			{
				return TypeOf<T>();
			}

			ResourceStatus get_status() const final override
			{
				return this->_status;
			}

			/** Returns a pointer to the resource if it has been loaded. */
			const T* get_resource() const
			{
				if (this->get_status() == ResourceStatus::Loaded)
				{
					return this->_resource.template GetPointer<T>();
				}
				else
				{
					return nullptr;
				}
			}

		protected:

			/** Loads the resource with the given arguments. */
			template <typename ... Args>
			void load(Args&& ... args)
			{
				this->_status = ResourceStatus::Loading;
				this->_resource.template Emplace<T>(std::forward<Args>(args)...);
				this->_status = ResourceStatus::Loaded;
			}

			////////////////
			///   Data   ///
		private:

			StaticBufferFor<T> _resource;
			ResourceStatus _status;
		};

		/** Type used for "custom" resources (those loaded by copy or with custom arguments). */
		template <class T>
		struct TCustomResourceInfo final : TResourceInfo<T>
		{
			////////////////////////
			///   Constructors   ///
		public:

			template <typename ... Args>
			TCustomResourceInfo(Args&& ... args)
			{
				this->load(std::forward<Args>(args)...);
			}
			
			///////////////////
			///   Methods   ///
		public:

			bool loaded_from_path() const override
			{
				return false;
			}

			Path get_path() const override
			{
				return{};
			}
		};

		/** Type used for resources loaded from paths. */
		template <class T>
		struct TPathedResourceInfo final : TResourceInfo<T>
		{
			////////////////////////
			///   Constructors   ///
		public:

			TPathedResourceInfo(Path path)
				: _path(std::move(path))
			{
				this->load(this->_path);
				Console::WriteLine("@ at '@' loaded successfully", TypeOf<T>().GetName(), this->_path);
			}

			///////////////////
			///   Methods   ///
		public:

			bool loaded_from_path() const override
			{
				return true;
			}

			Path get_path() const override
			{
				return this->_path;
			}

			////////////////
			///   Data   ///
		private:

			const Path _path;
		};

		////////////////////////
		///   Constructors   ///
	private:

		ResourceManager();
		ResourceManager(const ResourceManager& copy) = delete;

		///////////////////
		///   Methods   ///
	public:

		/** Creates a new resource out of the given value. */
		template <class T>
		static ResourceHandle<T> add_resource(T resource)
		{
			auto id = get_instance()._next_resource_id++;
			auto info = std::make_unique<TCustomResourceInfo<T>>(std::move(resource));
			get_instance()._resources[id] = std::move(info);

			return ResourceHandle<T>{ id };
		}

		/** Loads a new instance of the given resource asynchronously from the given path.
		* NOTE: If the given path does not point to a file, this returns a null handle.
		* NOTE: If a resource of the given type and path already exists, this will just return a handle to that. */
		template <class T>
		static ResourceHandle<T> load_resource(Path path)
		{
			// Make sure the file exists
			if (!path.points_to_file())
			{
				Console::Warning("@ at '@' could not be found.", TypeOf<T>().GetName(), path);
				return ResourceHandle<T>{};
			}

			auto pathKey = MakePair(std::move(path), TypePtr<>{ TypeOf<T>() });
			auto id = get_instance()._resource_paths[pathKey];
			
			// If this resource doesn't exist
			if (id == 0)
			{
				// Add it to the table FIRST (in case constructor in turn creates resources)
				id = get_instance()._next_resource_id++;
				get_instance()._resource_paths[pathKey] = id;

				// Create it
				auto info = std::make_unique<TPathedResourceInfo<T>>(pathKey.First);
				get_instance()._resources[id] = std::move(info);
			}

			return ResourceHandle<T>{ id };
		}

		template <class T, typename ... Args>
		static ResourceHandle<T> load_resource(Args&& ... args)
		{
			auto id = get_instance()._next_resource_id++;
			auto info = std::make_unique<TCustomResourceInfo<T>>(std::forward<Args>(args)...);
			get_instance()._resources[id] = std::move(info);

			return ResourceHandle<T>{ id };
		}

		/** Returns a pointer to a resource, given the handle.
		* NOTE: If the resource has been destroyed, this returns 'null'. */
		template <class T >
		static const T* get_resource(ResourceHandle<T> handle)
		{
			const auto& info = get_resource_info(handle);
			return info.get_resource();
		}

		/** Returns the status of the given resource.
		* NOTE: The given handle may not be null. */
		template <class T>
		static const TResourceInfo<T>& get_resource_info(ResourceHandle<T> handle)
		{
			const auto& info = *get_instance()._resources[handle.get_id()];
			return static_cast<const TResourceInfo<T>&>(info);
		}
	
	private:

		static ResourceManager& get_instance();

		/////////////////////
		///   Operators   ///
	public:

		ResourceManager& operator=(const ResourceManager& copy) = delete;

		////////////////
		///   Data   ///
	private:

		ResourceID _next_resource_id;
		Table<ResourceID, std::unique_ptr<ResourceInfoBase>> _resources;
		Table<Pair<Path, TypePtr<>>, ResourceID> _resource_paths;
	};

	////////////////////////
	///   Constructors   ///

	template <class T>
	ResourceHandle<T>::ResourceHandle(Path path)
	{
		*this = ResourceManager::load_resource<T>(std::move(path));
	}

	///////////////////
	///   Methods   ///

	template <class T>
	String ResourceHandle<T>::ToString() const
	{
		if (this->_id != 0)
		{
			const auto& info = ResourceManager::get_resource_info(*this);

			if (info.loaded_from_path())
			{
				return ::ToString(info.get_path());
			}
			else
			{
				return ::ToString(this->_id);
			}
		}

		return "null";
	}

	template <class T>
	void ResourceHandle<T>::ToArchive(ArchiveWriter& writer) const
	{
		if (this->_id != 0)
		{
			const auto& info = ResourceManager::get_resource_info(*this);
			
			if (info.loaded_from_path())
			{
				info.get_path().ToArchive(writer);
			}
		}
	}

	template <class T>
	void ResourceHandle<T>::FromArchive(const ArchiveReader& reader)
	{
		Path path;
		path.FromArchive(reader);

		if (!path.is_empty())
		{
			*this = ResourceManager::load_resource<T>(std::move(path));
		}
	}

	/////////////////////
	///   Operators   ///

	template <class T>
	ResourceHandle<T>& ResourceHandle<T>::operator=(Path path)
	{
		*this = ResourceManager::load_resource<T>(std::move(path));
		return *this;
	}
}
