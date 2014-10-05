// Game.cpp

#include "..\include\Core\Game.h"
using namespace Willow;

////////////////////////
///   Constructors   ///

Game::Game()
{
	this->_currentScene = new Scene();
}

///////////////////
///   Methods   ///

Game& Game::Instance()
{
	static Game instance;
	return instance;
}

Scene& Game::GetCurrentScene()
{
	return *_currentScene;
}

const Scene& Game::GetCurrentScene() const
{
	return *_currentScene;
}

void Game::SetCurrentScene(Scene& scene)
{
	delete _currentScene;
	_currentScene = &scene;
}