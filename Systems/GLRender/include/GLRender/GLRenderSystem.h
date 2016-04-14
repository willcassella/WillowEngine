// GLRenderSystem.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Vec3.h>
#include <Engine/World.h>
#include <Engine/Systems/RenderSystem.h>
#include <Engine/Assets/Shader.h>
#include <Engine/Assets/Texture.h>
#include <Engine/Assets/Material.h>
#include <Engine/Assets/StaticMesh.h>
#include "GLShader.h"
#include "GLTexture.h"
#include "GLMaterial.h"
#include "GLStaticMesh.h"

namespace Willow
{
	class GLRENDER_API GLRenderSystem final : public RenderSystem
	{
		////////////////////////
		///   Constructors   ///
	public:

		GLRenderSystem(uint32 width, uint32 height);
		~GLRenderSystem() override;

		///////////////////
		///   Methods   ///
	public:

		void RenderWorld(const World& world) override;

		void DrawDebugLine(const DebugLine& line) override;

		/** Finds or loads a GLShader from the given Shader asset. */
		GLShader& FindShader(const Shader& asset);

		/** Finds or loads a GLTexture based on the given Texture asset. */
		GLTexture& FindTexture(const Texture& asset);

		/** Finds or loads a GLMaterial based on the given Texture asset. */
		GLMaterial& FindMaterial(const Material& asset);

		/** Finds or loads a GLMaterial based on the given Static Mesh asset. */
		GLStaticMesh& FindStaticMesh(const StaticMesh& asset);

		////////////////
		///   Data   ///
	private:

		Table<Asset::ID, GLShader> _shaders;
		Table<Asset::ID, GLTexture> _textures;
		Table<Asset::ID, GLMaterial> _materials;
		Table<Asset::ID, GLStaticMesh> _staticMeshes;

		// The default framebuffer
		GLInteger _defaultFrameBuffer;

		// GBuffer layers
		BufferID _gBuffer;
		BufferID _depthBuffer;
		BufferID _positionBuffer;
		BufferID _diffuseBuffer;
		BufferID _normalBuffer;
		BufferID _specularBuffer;
		BufferID _metallicBuffer;
		BufferID _roughnessBuffer;

		// Screen data
		uint32 _width;
		uint32 _height;

		// Screen quad buffers
		BufferID _screenQuadVAO;
		BufferID _screenQuadVBO;
		BufferID _screenQuadProgram;

		// Debug draw
		Array<DebugLine> _debugLines;
	};
}
