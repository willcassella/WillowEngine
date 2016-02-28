// Component.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/Component.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Willow::Component)
.Data("Entity", &Component::_entity);

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

	void Component::FromArchive(const ArchiveReader& reader)
	{
		Base::FromArchive(reader);
		_entity->_components.Add(this);
	}
}
