// Component.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "Entity.h"

namespace willow
{
	class ENGINE_API Component : public GameObject
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(GameObject)
		friend class World;

		////////////////////////
		///   Constructors   ///
	public:

		Component();
		~Component() override = 0;

		///////////////////
		///   Methods   ///
	public:

		void FromArchive(const ArchiveReader& reader) override;

		/** Returns the Entity that this Component is a part of. */
		FORCEINLINE Entity& get_entity()
		{
			return *this->_entity;
		}

		/** Returns the Entity that this Component is a part of. */
		FORCEINLINE const Entity& get_entity() const
		{
			return *this->_entity;
		}

	protected:

		void on_destroy() override;

		////////////////
		///   Data   ///
	private:

		Entity* _entity;
	};

	inline Component::~Component()
	{
		// 'Component' is abstract
	}
}
