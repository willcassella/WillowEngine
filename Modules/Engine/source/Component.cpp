// Component.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/Component.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::Component)
.Data("Entity", &Component::_entity, DF_Transient);

namespace Willow
{
	////////////////////////
	///   Constructors   ///

	Component::Component()
	{
		_entity = nullptr;
	}

	///////////////////
	///   Methods   ///

	void Component::ToArchive(ArchiveWriter& writer) const
	{
		Base::ToArchive(writer);

		writer.PushValue("EntityID", _entity->GetID());
	}
}
