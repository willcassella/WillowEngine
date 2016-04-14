// GLRender.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include <Core/IO/Console.h>
#include <Engine/Components/Rendering/StaticMeshComponent.h>
#include <Engine/Components/Rendering/CameraComponent.h>
#include "glew.h"
#include "../include/GLRender/GLRenderSystem.h"

namespace Willow
{
	static_assert(!std::is_same<Scalar, long double>::value, "The renderer does not yet support 'long double' as a Scalar type.");
	static_assert(std::is_same<BufferID, GLuint>::value, "BufferID does not match GLuint.");
	static_assert(std::is_same<GLValue, GLuint>::value, "GLValue does not match GLuint.");
	static_assert(std::is_same<GLInteger, GLint>::value, "GLInteger does not match GLint.");

	BufferID lineBuffer;
	BufferID lineVAO;
	BufferID lineProgram;

	////////////////////////
	///   Constructors   ///

	GLRenderSystem::GLRenderSystem(uint32 width, uint32 height)
	{
		_width = width;
		_height = height;

		// Initialize GLEW
		glewExperimental = GL_TRUE;
		glewInit();
		glGetError(); // Sometimes GLEW initialization generates an error, get rid of it.

		// Initialize OpenGL
		glClearColor(0, 0, 0, 1);
		glClearDepth(1.f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glDisable(GL_STENCIL_TEST);
		glLineWidth(1.5f);

		// Get the default framebuffer
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_defaultFrameBuffer);

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

		// Create a VAO for screen quad
		glGenVertexArrays(1, &_screenQuadVAO);
		glBindVertexArray(_screenQuadVAO);

		// Create and upload a VBO for screen quad
		glGenBuffers(1, &_screenQuadVBO);
		glBindBuffer(GL_ARRAY_BUFFER, _screenQuadVBO);
		float screenQuadData[] = {
			-1.f, 1.f, 0.f, 1.f, // Top-left point
			-1.f, -1.f, 0.f, 0.f, // Bottom-left point
			1.f, -1.f, 1.f, 0.f, // Bottom-right point
			1.f, 1.f, 1.f, 1.f // Top-right point
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(screenQuadData), screenQuadData, GL_STATIC_DRAW);

		// Create and upload a shader program for the screen quad
		Shader vShader("Content/Shaders/viewport.vert");
		Shader fShader("Content/Shaders/viewport.frag");
		GLShader glVShader(*this, vShader);
		GLShader glFShader(*this, fShader);
		_screenQuadProgram = glCreateProgram();
		glAttachShader(_screenQuadProgram, glVShader.GetID());
		glAttachShader(_screenQuadProgram, glFShader.GetID());
		glLinkProgram(_screenQuadProgram);
		glDetachShader(_screenQuadProgram, glVShader.GetID());
		glDetachShader(_screenQuadProgram, glFShader.GetID());

		// Specify shader data
		GLint positionAttrib = glGetAttribLocation(_screenQuadProgram, "vPosition");
		glEnableVertexAttribArray(positionAttrib);
		glVertexAttribPointer(positionAttrib, 2, GL_FLOAT, false, sizeof(float) * 4, nullptr);

		GLint coordinateAttrib = glGetAttribLocation(_screenQuadProgram, "vTexCoord");
		glEnableVertexAttribArray(coordinateAttrib);
		glVertexAttribPointer(coordinateAttrib, 2, GL_FLOAT, false, sizeof(float) * 4, (void*)(sizeof(float) * 2));

		glUseProgram(_screenQuadProgram);
		glUniform1i(glGetUniformLocation(_screenQuadProgram, "positionBuffer"), 0);
		glUniform1i(glGetUniformLocation(_screenQuadProgram, "diffuseBuffer"), 1);
		glUniform1i(glGetUniformLocation(_screenQuadProgram, "normalBuffer"), 2);
		glUniform1i(glGetUniformLocation(_screenQuadProgram, "specularBuffer"), 3);

		auto error = glGetError();
		if (error != 0)
		{
			Console::WriteLine("An error occurred during startup: @", error);
		}

		/// DEBUG DRAW CODE
		glGenVertexArrays(1, &lineVAO);
		glBindVertexArray(lineVAO);
		
		glGenBuffers(1, &lineBuffer);
		Shader lineVShader{ "Content/Shaders/line.vert" };
		Shader lineFShader{ "Content/Shaders/line.frag" };
		GLShader glLineVShader{ *this, lineVShader };
		GLShader glLineFShader{ *this, lineFShader };
		lineProgram = glCreateProgram();
		glAttachShader(lineProgram, glLineVShader.GetID());
		glAttachShader(lineProgram, glLineFShader.GetID());
		glLinkProgram(lineProgram);
		glDetachShader(lineProgram, glLineVShader.GetID());
		glDetachShader(lineProgram, glLineFShader.GetID());
	}

	GLRenderSystem::~GLRenderSystem()
	{
		// Todo
	}

	///////////////////
	///   Methods   ///

	void GLRenderSystem::RenderWorld(const World& world)
	{
		// Bind the GBuffer and its sub-buffers for drawing
		glBindFramebuffer(GL_FRAMEBUFFER, _gBuffer);
		GLuint drawBuffers[] = { GL_COLOR_ATTACHMENT0 /*position*/, GL_COLOR_ATTACHMENT1 /*diffuse*/, GL_COLOR_ATTACHMENT2 /*normal*/, GL_COLOR_ATTACHMENT3 /*specular*/ };
		glDrawBuffers(4, drawBuffers);

		// Clear the GBuffer
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Get first camera in the World
		auto cameras = world.Enumerate<CameraComponent>();

		// We can't render the World without a camera
		if (cameras.IsEmpty())
		{
			return;
		}

		const uint32 frameHeight = _height / cameras.Size();

		// Render each camera
		for (std::size_t i = 0; i < cameras.Size(); ++i)
		{
			glViewport(0, frameHeight * i, _width, frameHeight * i + frameHeight);

			Mat4 view = cameras[i]->GetTransformationMatrix().Inverse();
			Mat4 proj = cameras[i]->GetPerspective();

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

				// Note: Because I kind of messed up my StaticMesh structure (ie, vertices are tied to specific UV coordinates)
				// I'm gonna be using GLDrawArrays for now, instead of GLDrawElements.
				// Luckily, I wasn't actually taking advantage of GLDrawElements before, so all the old mesh files still work
				glDrawArrays(GL_TRIANGLES, 0, mesh.GetNumVertices());
			}

			// Render debug lines
			glBindVertexArray(lineVAO);
			glUseProgram(lineProgram);
			glBindBuffer(GL_ARRAY_BUFFER, lineBuffer);

			{
				Array<Vec3> points(_debugLines.Size() * 2);

				for (const auto& line : _debugLines)
				{
					points.Add(line.Start);
					points.Add(line.Color);
					points.Add(line.End);
					points.Add(line.Color);
				}

				_debugLines.Clear();

				if (!points.IsEmpty())
				{
					auto linePos = glGetAttribLocation(lineProgram, "vPosition");
					glEnableVertexAttribArray(linePos);
					glVertexAttribPointer(linePos, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3) * 2, nullptr);

					auto lineColor = glGetAttribLocation(lineProgram, "vColor");
					glEnableVertexAttribArray(lineColor);
					glVertexAttribPointer(lineColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3) * 2, (void*)sizeof(Vec3));

					glUniformMatrix4fv(0, 1, false, (const float*)&view);
					glUniformMatrix4fv(1, 1, false, (const float*)&proj);
					glBufferData(GL_ARRAY_BUFFER, points.Size() * sizeof(Vec3), points.CArray(), GL_DYNAMIC_DRAW);
					glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(points.Size()));
				}
			}
		}

		glViewport(0, 0, _width, _height);

		// Bind the default framebuffer for drawing
		glBindFramebuffer(GL_FRAMEBUFFER, _defaultFrameBuffer);

		// Clear the frame
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glClear(GL_COLOR_BUFFER_BIT);

		// Bind the screen quad
		glBindVertexArray(_screenQuadVAO);
		glUseProgram(_screenQuadProgram);

		// Bind the GBuffer's sub-buffers as textures for reading
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _positionBuffer);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, _diffuseBuffer);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, _normalBuffer);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, _specularBuffer);

		// Draw the screen quad
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}

	void GLRenderSystem::DrawDebugLine(const DebugLine& line)
	{
		_debugLines.Add(line);
	}

	GLShader& GLRenderSystem::FindShader(const Shader& asset)
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

	GLTexture& GLRenderSystem::FindTexture(const Texture& asset)
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

	GLMaterial& GLRenderSystem::FindMaterial(const Material& asset)
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

	GLStaticMesh& GLRenderSystem::FindStaticMesh(const StaticMesh& asset)
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
}
