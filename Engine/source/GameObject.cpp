#include <string>
#include "GameObject.h"
#include "Vec3.h"

////////////////////////
///   Constructors   ///

GameObject::GameObject( const std::string& _NAME )
{
	name = _NAME;
}

///////////////////
///   Methods   ///

void GameObject::tick( float timeInterval )
{
	// Do nothing
}