// Serialization.cpp

#include "../../include/Utility/Reflection/Serialization.h"
#include <fstream>
using namespace Willow;

/////////////////////
///   Functions   ///

void FindPointers(List<byte*>& references, const object& root)
{
	for (const auto& field : root.GetType().GetAllFields())
	{
		const Type& fieldType = field.GetFieldType();

		if (fieldType.IsA<PointerType>())
		{
			references.Add(Convert<byte*>(field.GetValueString(root)));
		}
		else if (fieldType.IsA<ClassType>())
		{
			FindPointers(references, field.GetValue(root));
		}
	}
}


void RecursiveSerialize(const object& root, List<byte*>& references, std::ofstream& file)
{
	for (const auto& field : root.GetType().GetAllFields())
	{
		const Type& fieldType = field.GetFieldType();

		file << "'" << field.GetName().Cstr() << "'";

		if (references.HasElement

		if (fieldType.IsA<ClassType>())
		{
			file << std::endl << "{ " << std::endl;
			RecursiveSerialize()
		}
	}
}

void Willow::Serialize(const object& root)
{
	List<byte*> references;

	// Search for pointers
	FindPointers(references, root);

	std::ofstream file;

	file.open("test.lvl", std::ios::out);

	// Serialize the object
	RecursiveSerialize(root, references, file);
}



////////////////////////
///   DeSerializer   ///

object& DeSerializer::DeSerialize()
{
	
}