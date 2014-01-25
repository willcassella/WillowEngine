#include "GameObject.h"
#include "Renderer.h"

#include "Vec3.h"

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
	//transform.orientation.rotateByAxisAngle( Vec3( 0, 1, 0 ), 0.0005f );
}