// Render.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "glew.h"
#include "../include/Render/Render.h"

void SetupRenderer()
{
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	ClearScreen();
}

void ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//void Render()
//{
//	auto meshes = StaticMeshComponent::GetAllStaticMeshComponents();
//
//	if (!meshes.IsEmpty())
//	{
//		Mat4 view = meshes.First()->GetOwner().GetScene().Cameras[0]->Transform.GetTransfomationMatrix().Inverse();
//		Mat4 proj = meshes.First()->GetOwner().GetScene().Cameras[0]->GetPerspective();
//
//		for (const auto mesh : meshes)
//		{
//			if (mesh->Mesh.IsLoaded())
//			{
//				mesh->Mesh->Render(mesh->GetOwner().Transform.GetTransfomationMatrix(), view, proj);
//			}
//		}
//	}
//}