// Camera.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "..\include\Engine\Camera.h"

//////////////////////
///   Reflection   ///

CLASS_REFLECTION(Camera)
.AddField("VFOV", &Camera::VFOV)
.AddField("Ratio", &Camera::Ratio)
.AddField("ZMin", &Camera::ZMin)
.AddField("ZMax", &Camera::ZMax);

////////////////////////
///   Constructors   ///

Camera::Camera(const String& name, float vFOV, float ratio, float zMin, float zMax)
	: Super(name)
{
	this->VFOV = vFOV;
	this->Ratio = ratio;
	this->ZMin = zMin;
	this->ZMax = zMax;
}

///////////////////
///   Methods   ///

Mat4 Camera::GetPerspective() const
{
	return Mat4::PerspectiveVFOV(VFOV, Ratio, ZMin, ZMax);
}