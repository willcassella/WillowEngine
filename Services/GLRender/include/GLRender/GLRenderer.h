// GLRender.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Vec3.h>
#include <Engine/World.h>
#include <Engine/ServiceInterfaces/IRenderer.h>
#include <Engine/Assets/Shader.h>
#include <Engine/Assets/Texture.h>
#include <Engine/Assets/Material.h>
#include <Engine/Assets/StaticMesh.h>
#include "GLShader.h"
#include "GLTexture.h"
#include "GLMaterial.h"
#include "GLStaticMesh.h"

/////////////////
///   Types   ///

class GLRENDER_API GLRenderer final : public IRenderer
{
	////////////////////////
	///   Constructors   ///
public:

	GLRenderer(uint32 width, uint32 height);
	GLRenderer(const GLRenderer& copy) = delete;
	GLRenderer(GLRenderer&& move) = delete;
	~GLRenderer() override;

	///////////////////
	///   Methods   ///
public:

	/** Renders the given World. */
	void RenderWorld(const World& world) override;

	/** Finds or loads a GLShader from the given Shader asset. */
	GLShader& FindShader(const Shader& asset);

	/** Finds or loads a GLTexture based on the given Texture asset. */
	GLTexture& FindTexture(const Texture& asset);

	/** Finds or loads a GLMaterial based on the given Texture asset. */
	GLMaterial& FindMaterial(const Material& asset);

	/** Finds or loads a GLMaterial based on the given Static Mesh asset. */
	GLStaticMesh& FindStaticMesh(const StaticMesh& asset);

	/////////////////////
	///   Operators   ///
public:

	GLRenderer& operator=(const GLRenderer& copy) = delete;
	GLRenderer& operator=(GLRenderer&& move) = delete;

	////////////////
	///   Data   ///
private:

	Table<AssetID, GLShader> _shaders;
	Table<AssetID, GLTexture> _textures;
	Table<AssetID, GLMaterial> _materials;
	Table<AssetID, GLStaticMesh> _staticMeshes;
	BufferID _defaultFrameBuffer;
	BufferID _gBuffer;
	BufferID _depthBuffer;
	BufferID _positionBuffer;
	BufferID _diffuseBuffer;
	BufferID _normalBuffer;
	BufferID _specularBuffer;
	BufferID _metallicBuffer;
	BufferID _roughnessBuffer;
};
