// Game.h
#pragma once

#include "config.h"
#include "Scene.h"

namespace Willow
{
	// @TODO: Make this actually useful
	class CORE_API Game
	{
		////////////////////////
		///   Constructors   ///
	protected:

		Game();

		///////////////////
		///   Methods   ///
	public:

		static Game& Instance();

		/** Returns a reference to the currently simulated scene */
		Scene& GetCurrentScene();
		const Scene& GetCurrentScene() const;

		/** Sets the currently simulated scene to an old one @TODO: This needs work */
		void SetCurrentScene(Scene& scene);

		//////////////////
		///   Data   ///
	protected:

		Scene* _currentScene;
	};
}