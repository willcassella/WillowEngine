// Prop.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/GameObjects/Prop.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Prop)
.Field("Mesh", &Prop::MeshComponent, "");

////////////////////////
///   Constructors   ///

Prop::Prop(Scene& scene)
	: Base(scene)
{
	MeshComponent = New<StaticMeshComponent>(self);
}