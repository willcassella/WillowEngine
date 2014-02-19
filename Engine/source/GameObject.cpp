#include <string>
#include "GameObject.h"
#include "Vec3.h"

GameObject::GameObject( const std::string& _NAME )
{
	name = _NAME;
}

GameObject::GameObject( const std::string& _NAME, const StaticMesh& _MESH )
{
	
}

GameObject::~GameObject()
{
	//Do nothing
}

void GameObject::Update()
{
	//transform.orientation.rotateByAxisAngle( Vec3( 0, 1, 0 ), 0.0005f );
}