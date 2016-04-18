// Player.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Entity.h"

namespace willow
{
	class ENGINE_API Player : public Entity
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_CLASS
		EXTENDS(Entity)
		friend class World;

		///////////////////
		///   Methods   ///
	public:

		/** Returns the ID of this player. */
		uint16 get_player_id() const
		{
			return this->_player_id;
		}

	protected:

		/** Handles when this player is given an ID. */
		virtual void on_assign_id();

		////////////////
		///   Data   ///
	private:

		uint16 _player_id;
	};
}
