// GLRenderSystem.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Engine/World.h>
#include <Engine/Systems/RenderSystem.h>
#include <Engine/Resources/Shader.h>
#include <Engine/Resources/Texture.h>
#include <Engine/Resources/Material.h>
#include <Engine/Resources/StaticMesh.h>
#include "GLShader.h"
#include "GLTexture.h"
#include "GLStaticMesh.h"
#include "GLMaterial.h"

namespace willow
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

		void render_world(const World& world) override;

		void draw_debug_line(const DebugLine& line) override;

		/** Finds or loads a GLShader from the given Shader handle. */
		GLShader& find_shader(ResourceHandle<Shader> handle);

		/** Finds or loads a GLTexture based on the given Texture asset. */
		GLTexture& find_texture(ResourceHandle<Texture> handle);

		/** Finds or loads a GLMaterial based on the given Texture asset. */
		GLMaterial& find_material(ResourceHandle<Material> handle);

		/** Finds or loads a GLMaterial based on the given Static Mesh asset. */
		GLStaticMesh& find_static_mesh(ResourceHandle<StaticMesh> handle);

		////////////////
		///   Data   ///
	private:

		Table<ResourceID, GLShader> _shaders;
		Table<ResourceID, GLTexture> _textures;
		Table<ResourceID, GLMaterial> _materials;
		Table<ResourceID, GLStaticMesh> _staticMeshes;

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
