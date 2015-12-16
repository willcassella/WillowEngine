// Prop.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/World.h"
#include "../../include/Engine/GameObjects/Prop.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Prop)
;//.Field("Mesh", &Prop::MeshComponent, "");

///////////////////
///   Methods   ///

void Prop::Build()
{
	Base::Build();
	MeshComponent = Attach<StaticMeshComponent>();
}
