// Owned.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../../../include/Core/IO/Console.h"
#include "../../../include/Core/Reflection/StructInfo.h"
#include "../../../include/Core/Memory/Pointers/Owned.h"
#include "../../../include/Core/Reflection/VoidInfo.h"
#include "../../../include/Core/Reflection/Variant.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Owned<void>);

/////////////////////
///   Operators   ///

Variant Owned<void>::operator*()
{
	assert(*this != nullptr);
	return Variant(_value, *_type);
}

ImmutableVariant Owned<void>::operator*() const
{
	assert(*this != nullptr);
	return ImmutableVariant(_value, *_type);
}

//////////////////////
///   Operations   ///

namespace Operations
{
	void ToArchive<Owned<void>>::Function(const Owned<void>& value, ArchiveWriter& writer)
	{
		if (value)
		{
			auto v = *value;

			if (v.HasToArchiveImplementation())
			{
				writer.PushValue(v.GetType().GetName(), v);
			}
			else
			{
				Console::Warning("Attempt to perform 'ToArchive' a Owned<void> to type '@', which does not support 'ToArchive'.", v.GetType().GetName());
			}
		}

		writer.SetValue(nullptr);
	}

	void FromArchive<Owned<void>>::Function(Owned<void>& value, const ArchiveReader& reader)
	{
		if (!reader.IsNull())
		{
			reader.GetFirstChild([&](const ArchiveReader& child)
			{
				auto type = Application::FindType(child.GetName());

				if (!type)
				{
					Console::Warning("Type '@' no longer exists!", child.GetName());
				}
				else if (!type->HasDynamicConstructor() || !type->IsDefaultConstructible())
				{
					Console::Warning("Cannot create instance of type '@'", type->GetName());
				}
				else if (!type->HasFromArchiveImplementation())
				{
					Console::Warning("Type '@' does not support 'FromArchive'", type->GetName());
				}
				else
				{
					
				}
			});
		}

		value = nullptr;
	}
}
