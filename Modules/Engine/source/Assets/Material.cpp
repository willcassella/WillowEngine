// Material.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include "../../include/Engine/Assets/Material.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Material);

////////////////////////
///   Constructors   ///

Material::Material(const Path& path)
	: Base(path)
{
	VertexShader = "Content/Shaders/default.vert"_p;
	FragmentShader = "Content/Shaders/default.frag"_p;

	//for (const auto& line : file.GetLines())
	//{
	//	if (line == "Shaders:")
	//	{
	//		for (file.GetNextLine(line); !line.IsNullOrEmpty(); file.GetNextLine(line))
	//		{
	//			auto shader = String::ParseEquality(line);

	//			if (shader.First == "VertexShader")
	//			{
	//				this->VertexShader = shader.Second;
	//			}
	//			else if (shader.First == "FragmentShader")
	//			{
	//				this->FragmentShader = shader.Second;
	//			}
	//		}
	//	}
	//	else if (line == "Textures:")
	//	{
	//		for (file.GetNextLine(line); !line.IsNullOrEmpty(); file.GetNextLine(line))
	//		{
	//			auto texture = String::ParseEquality(line);

	//			this->Textures[texture.First] = texture.Second;
	//		}
	//	}
	//}
}
