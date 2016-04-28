// GameObject.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Object.h>
#include <Core/Math/Mat4.h>
#include "config.h"
#include "Forwards/Engine.h"

namespace willow
{
	/** Base for all "Objects" in the game (Entities, Components, etc). */
	class ENGINE_API GameObject : public Object
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Object)
		friend class World;

		/////////////////
		///   Types   ///
	public:

		/** Unique identifier for GameObjects. */
		using ID = uint64;

		/** The possible states for a GameObject to exist in, in order. */
		enum class State : byte
		{
			/** This GameObject has just been constructed, but has not been initialized yet. You may not make any assertions about the
			* validity of its state at this point in time. */
			Uninitialized,

			/** This GameObject has been initialized. It has an ID and exists in a World, and is hooked up to the required systems.
			* However, it may not have had its starting properties set yet. */
			Initialized,

			/** This GameObject is currently executing its 'on_spawn' handler. */
			Spawning,

			/** This GameObject has been successfully spawned, you may now consider it a fully-active GameObject. */
			Spawned,

			/** This GameObject has been destroyed, and will be deconstructed at the end of the frame. */
			Destroyed
		};

		////////////////////////
		///   Constructors   ///
	public:

		GameObject();

		///////////////////
		///   Methods   ///
	public:

		virtual void ToArchive(ArchiveWriter& writer) const;

		virtual void FromArchive(const ArchiveReader& reader);

		/** Returns the ID of this GameObject. */
		FORCEINLINE ID get_id() const
		{
			return this->_id;
		}

		/** Returns the current state of this GameObject. */
		FORCEINLINE State get_state() const
		{
			return this->_state;
		}

		/** Returns a reference to the World that this GameObject belongs to. */
		FORCEINLINE World& get_world()
		{
			return *this->_world;
		}

		/** Returns a reference to the World that this GameObject belongs to. */
		FORCEINLINE const World& get_world() const
		{
			return *this->_world;
		}

		/** Returns whether this GameObject has been initialized. */
		FORCEINLINE bool is_initialized() const
		{
			return this->get_state() >= State::Initialized;
		}

		/** Return whether this GameObject is currently spawning. */
		FORCEINLINE bool is_spawning() const
		{
			return this->get_state() == State::Spawning;
		}

		/** Returns whether this GameObject has completed its spawning procedure. */
		FORCEINLINE bool has_spawned() const
		{
			return this->get_state() >= State::Spawned;
		}

		/** Returns whether this GameObject has been destroyed. */
		FORCEINLINE bool is_destroyed() const
		{
			return this->get_state() == State::Destroyed;
		}

		/** Clones this GameObject, returning a new instance in the 'Initialized' state.
		* 'world' - The world to clone this GameObject into. */
		Owned<GameObject> clone(World& world) const;

		/** Destroys this GameObject. TODO: Add delay */
		void destroy();

	protected:

		/** Handles initialization procedure. */
		virtual void on_initialize();

		/** Handles spawning procedure. */
		virtual void on_spawn();

		/** Handles destruction procedure. */
		virtual void on_destroy();

		virtual void on_clone(const GameObject& old);

		/////////////////////
		///   Operators   ///
	public:

		GameObject& operator=(const GameObject& copy);

		////////////////
		///   Data   ///
	private:

		ID _id;
		World* _world;
		State _state;
	};
}

REFLECTABLE_ENUM(ENGINE_API, willow::GameObject::State)
