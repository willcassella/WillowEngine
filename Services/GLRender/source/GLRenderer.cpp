// GLRender.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/IO/Console.h>
#include <Engine/Components/StaticMeshComponent.h>
#include <Engine/Components/CameraComponent.h>
#include "glew.h"
#include "../include/GLRender/GLRenderer.h"

static_assert(!std::is_same<Scalar, long double>::value, "The renderer does not yet support 'long double' as a Scalar type.");

////////////////////////
///   Constructors   ///

GLRenderer::GLRenderer(uint32 width, uint32 height)
{
	// Spawn GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// Spawn OpenGL
	glClearColor(0, 0, 0, 1);
	glClearDepth(1.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_STENCIL_TEST);

	// Create a framebuffer for deferred rendering (GBuffer)
	glGenFramebuffers(1, &_gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);

	// Create a depth buffer for the GBuffer
	glGenTextures(1, &_depthBuffer);
	glBindTexture(GL_TEXTURE_2D, _depthBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, nullptr); // 1 32-bit unsigned integer component for depth
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthBuffer, 0);

	// Create a position buffer for the GBuffer
	glGenTextures(1, &_positionBuffer);
	glBindTexture(GL_TEXTURE_2D, _positionBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, nullptr); // 3 32-bit floating point components for position
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _positionBuffer, 0);

	// Create a diffuse buffer for the GBuffer
	glGenTextures(1, &_diffuseBuffer);
	glBindTexture(GL_TEXTURE_2D, _diffuseBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); // 4 8-bit unsigned integer components for diffuse
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, _diffuseBuffer, 0);

	// Create a normal buffer for the GBuffer
	glGenTextures(1, &_normalBuffer);
	glBindTexture(GL_TEXTURE_2D, _normalBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, nullptr); // 3 32-bit floating point components for normal
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, _normalBuffer, 0);

	// Create a specular buffer for the GBuffer
	glGenTextures(1, &_specularBuffer);
	glBindTexture(GL_TEXTURE_2D, _specularBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, nullptr); // 1 32-bit floating point component for specular
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, _specularBuffer, 0);

	// Create a metallic buffer for the GBuffer
	glGenTextures(1, &_metallicBuffer);
	glBindTexture(GL_TEXTURE_2D, _metallicBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, nullptr); // 1 32-bit floating point component for metallic
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, _metallicBuffer, 0);

	// Create a roughness buffer for the GBuffer
	glGenTextures(1, &_roughnessBuffer);
	glBindTexture(GL_TEXTURE_2D, _roughnessBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, nullptr); // 1 32-bit floating point component for roughness
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, _roughnessBuffer, 0);

	// Make sure the GBuffer was constructed successfully
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		Console::WriteLine("GBuffer created successfully");
	}
	else
	{
		Console::WriteLine("Error creating the GBuffer");
	}
//
//	// Create a VAO for screen quad
//	glGenVertexArrays(1, &screenQuadVAO);
//	glBindVertexArray(screenQuadVAO);
//
//	// Create and upload a VBO for screen quad
//	glGenBuffers(1, &screenQuadVBO);
//	glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
//	float screenQuadData[] = {
//		-1.f, 1.f, 0.f, 1.f, // Top-left point
//		-1.f, -1.f, 0.f, 0.f, // Bottom-left point
//		1.f, -1.f, 1.f, 0.f, // Bottom-right point
//		1.f, 1.f, 1.f, 1.f // Top-right point
//	};
//	glBufferData(GL_ARRAY_BUFFER, sizeof(screenQuadData), screenQuadData, GL_STATIC_DRAW);
//
//	// Create and upload a shader program for the screen quad
//	GLShader vShader("data/viewport.vert");
//	GLShader fShader("data/viewport.frag");
//	screenQuadProgram = glCreateProgram();
//	glAttachShader(screenQuadProgram, vShader.GetID());
//	glAttachShader(screenQuadProgram, fShader.GetID());
//	glLinkProgram(screenQuadProgram);
//	glUseProgram(screenQuadProgram);
//
//	// Specify shader data
//	GLint positionAttrib = glGetAttribLocation(screenQuadProgram, "position");
//	glEnableVertexAttribArray(positionAttrib);
//	glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, false, sizeof(float)*4, 0);
//
//	GLint coordinateAttrib = glGetAttribLocation(screenQuadProgram, "vTexCoord");
//	glEnableVertexAttribArray(coordinateAttrib);
//	glVertexAttribPointer(coordinateAttrib, 2, GL_FLOAT, false, sizeof(float)*4, (void*)(sizeof(float)*2));
//
//	float lightPos[] = { 0.f, 1.f, 0.f };
//	glUniform1i(glGetUniformLocation(screenQuadProgram, "positionBuffer"), 0);
//	glUniform1i(glGetUniformLocation(screenQuadProgram, "diffuseBuffer"), 1);
//	glUniform1i(glGetUniformLocation(screenQuadProgram, "normalBuffer"), 2);
//	glUniform1i(glGetUniformLocation(screenQuadProgram, "specularBuffer"), 3);
//	glUniform3fv(glGetUniformLocation(screenQuadProgram, "lightPos"), 1, lightPos);
}

GLRenderer::~GLRenderer()
{
	// Todo
}

///////////////////
///   Methods   ///

void GLRenderer::RenderWorld(const World& world)
{
	// Clear color and depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Get first camera in the World
	const auto* cam = world.Enumerate<CameraComponent>().FirstOrDefault();

	// We can't render the World without a camera
	if (!cam)
		return;

	Mat4 view = cam->GetTransformationMatrix().Inverse();
	Mat4 proj = cam->GetPerspective();

	// Render each StaticMeshComponent in the World
	for (auto staticMesh : world.Enumerate<StaticMeshComponent>())
	{
		if (!staticMesh->Visible)
			continue;

		Mat4 model = staticMesh->GetTransformationMatrix();
		
		// Bind the mesh and material
		auto& mesh = FindStaticMesh(*staticMesh->Mesh);
		mesh.Bind();
		FindMaterial(*staticMesh->Material).Bind(staticMesh->InstanceParams);

		// Upload transformation matrices
		glUniformMatrix4fv(0, 1, false, (const float*)&model);
		glUniformMatrix4fv(1, 1, false, (const float*)&view);
		glUniformMatrix4fv(2, 1, false, (const float*)&proj);

		glDrawElements(GL_TRIANGLES, mesh.GetNumElements(), GL_UNSIGNED_INT, nullptr);
	}
}

GLShader& GLRenderer::FindShader(const Shader& asset)
{
	if (auto pShader = _shaders.Find(asset.GetID()))
	{
		return *pShader;
	}
	else
	{
		return _shaders.Insert(asset.GetID(), GLShader(*this, asset));
	}
}

GLTexture& GLRenderer::FindTexture(const Texture& asset)
{
	if (auto pTexture = _textures.Find(asset.GetID()))
	{
		return *pTexture;
	}
	else
	{
		return _textures.Insert(asset.GetID(), GLTexture(*this, asset));
	}
}

GLMaterial& GLRenderer::FindMaterial(const Material& asset)
{
	if (auto pMaterial = _materials.Find(asset.GetID()))
	{
		return *pMaterial;
	}
	else
	{
		return _materials.Insert(asset.GetID(), GLMaterial(*this, asset));
	}
}

GLStaticMesh& GLRenderer::FindStaticMesh(const StaticMesh& asset)
{
	if (auto pMesh = _staticMeshes.Find(asset.GetID()))
	{
		return *pMesh;
	}
	else
	{
		return _staticMeshes.Insert(asset.GetID(), GLStaticMesh(*this, asset));
	}
}

//void BeginFrame()
//{
//	glEnable(GL_DEPTH_TEST);
//
//	// Bind the GBuffer and its sub-buffers for drawing
//	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _gBuffer);
//	BufferID drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5 };
//	glDrawBuffers(6, drawBuffers);
//
//	// Clear the GBuffer
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//void EndFrame(const Vec3& camPos)
//{
//	// Bind the default framebuffer for drawing
//	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
//
//	// Clear the frame
//	glDisable(GL_DEPTH_TEST);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	// Bind the screen quad
//	glBindVertexArray(screenQuadVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
//	glUseProgram(screenQuadProgram);
//
//	// Upload the camera's position
//	float cam[] = { camPos.X, camPos.Y, camPos.Z };
//	glUniform3fv(glGetUniformLocation(screenQuadProgram, "camPos"), 1, cam);
//
//	// Bind the GBuffer's sub-buffers as textures for reading
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, _positionBuffer);
//	
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, _diffuseBuffer);
//	
//	glActiveTexture(GL_TEXTURE2);
//	glBindTexture(GL_TEXTURE_2D, _normalBuffer);
//
//	glActiveTexture(GL_TEXTURE3);
//	glBindTexture(GL_TEXTURE_2D, _specularBuffer);
//
//	// Draw the screen quad
//	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
//}
