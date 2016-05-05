// Component.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/Component.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::Component)
.Data("entity", &Component::_entity);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	Component::Component()
		: _entity{ nullptr }
	{
		// All done
	}

	///////////////////
	///   Methods   ///

	void Component::FromArchive(const ArchiveReader& reader)
	{
		this->Base::FromArchive(reader);
		this->_entity->_components.Add(this);
	}

	void Component::on_destroy()
	{
		this->Base::on_destroy();
		_entity->_components.DeleteFirst(this);
	}
}
