#include "GameObject.h"
#include "Renderer.h"

GameObject::GameObject()
{
	// TODO: move this to scene class
	Renderer::rqueue.push( this );
}

GameObject::~GameObject()
{
	//Do nothing
}

void GameObject::Update()
{
	//Do nothing
}