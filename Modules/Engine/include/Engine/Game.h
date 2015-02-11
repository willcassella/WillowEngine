// Game.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "config.h"
#include "Scene.h"

// @TODO: Make this actually useful
class ENGINE_API Game
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

	/** Sets the currently simulated scene */
	void SetCurrentScene(Scene& scene);

	//////////////////
	///   Data   ///
protected:

	Scene* _currentScene;
};