// Entity.cpp - Copyright 2013-2016 Will Cassella, All Rights Reserved

#include "../include/Engine/Entity.h"
#include "../include/Engine/Component.h"

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(Entity)
.Data("Name", &Entity::_name)
.Data("Transform", &Entity::_transform)
.Data("Parent", &Entity::_parent, DF_Transient)
.Data("Children", &Entity::_children, DF_Transient)
.Data("Components", &Entity::_components, DF_Transient)
.Property("Name", &Entity::GetName, &Entity::Editor_SetName, "The name of this Entity", PF_EditorOnly);

////////////////////////
///   Constructors   ///

Entity::Entity()
{
	_world = nullptr;
	_parent = nullptr;
}

///////////////////
///   Methods   ///

void Entity::ToArchive(ArchiveWriter& writer) const
{
	Base::ToArchive(writer);

	if (_parent)
	{
		writer.PushValue("Parent", _parent->GetID());
	}
	else
	{
		writer.PushValue("Parent", 0);
	}

	writer.AddChild("Components", [&](ArchiveWriter& child)
	{
		for (auto component : _components)
		{
			child.PushValue("ID", component->GetID());
		}
	});
}

bool Entity::IsActor() const
{
	return this->GetType() != TypeOf<Entity>();
}

Entity* Entity::GetActor()
{
	if (this->IsActor())
	{
		return this;
	}
	else if (_parent)
	{
		return _parent->GetActor();
	}
	else
	{
		return nullptr;
	}
}

const Entity* Entity::GetActor() const
{
	if (this->IsActor())
	{
		return this;
	}
	else if (_parent)
	{
		return _parent->GetActor();
	}
	else
	{
		return nullptr;
	}
}

bool Entity::IsParentedTo(const Entity& entity) const
{
	for (auto ent = this; ent != nullptr; ent = ent->_parent)
	{
		if (ent == &entity)
		{
			return true;
		}
	}

	return false;
}

void Entity::SetParent(Entity* parent, SetParentOffsetMode /*mode*/) // TODO: Handle mode
{
	if (_parent != nullptr && parent->IsParentedTo(*this))
	{
		// This would create a parent cycle, abort
		Console::Warning("Attempt to parent entity '@' to '@' would create a parent cycle.", this->GetName(), parent->GetName());
		return;
	}

	// If we currently have a parent
	if (_parent)
	{
		_parent->_children.DeleteFirst(this);
	}

	// Assign the parent
	_parent = parent;

	// If we NOW have a parent
	if (_parent)
	{
		_parent->_children.Add(this);
	}
}

Vec3 Entity::GetLocation() const
{
	return _transform.GetLocation();
}

Vec3 Entity::GetWorldLocation() const
{
	if (this->HasParent())
	{
		return this->GetParent()->GetTransformationMatrix() * this->GetLocation();
	}
	else
	{
		return this->GetLocation();
	}
}

void Entity::SetLocation(const Vec3& location)
{
	_transform.SetLocation(location);
}

void Entity::SetWorldLocation(const Vec3&)
{
	// TODO
}

void Entity::Translate(const Vec3& vec)
{
	Vec3 newVec = Mat4::Rotate(this->GetWorldRotation()) * vec;
	_transform.SetLocation(_transform.GetLocation() + newVec);
}

void Entity::TranslateGlobal(const Vec3&)
{
	// TODO
}

Quat Entity::GetRotation() const
{
	return _transform.GetRotation();
}

Quat Entity::GetWorldRotation() const
{
	if (this->HasParent())
	{
		return this->GetParent()->GetWorldRotation() * _transform.GetRotation();
	}
	else
	{
		return _transform.GetRotation();
	}
}

void Entity::SetRotation(const Quat&)
{
	// TODO
}

void Entity::SetWorldRotation(const Quat&)
{
	// TODO
}

void Entity::Rotate(const Vec3& axis, Angle angle)
{
	auto rotation = _transform.GetRotation();
	rotation.RotateByAxisAngle(axis, angle, true);
	_transform.SetRotation(rotation);
}

void Entity::RotateGlobal(const Vec3& axis, Angle angle)
{
	auto rotation = _transform.GetRotation();
	rotation.RotateByAxisAngle(axis, angle, false);
	_transform.SetRotation(rotation);
}

Vec3 Entity::GetScale() const
{
	return _transform.GetScale();
}

void Entity::SetScale(const Vec3& scale)
{
	_transform.SetScale(scale);
}

void Entity::Scale(const Vec3& vec)
{
	auto newScale = _transform.GetScale() + vec;
	_transform.SetScale(newScale);
}

Mat4 Entity::GetTransformationMatrix() const
{
	if (this->HasParent())
	{
		return this->GetParent()->GetTransformationMatrix() * 
			Mat4::Translate(this->GetLocation()) * 
			Mat4::Rotate(this->GetRotation()) * 
			Mat4::Scale(this->GetScale());
	}
	else
	{
		return 	Mat4::Translate(this->GetLocation()) *
			Mat4::Rotate(this->GetRotation()) *
			Mat4::Scale(this->GetScale());
	}
}

void Entity::OnDestroy()
{
	for (auto child : _children)
	{
		child->Destroy();
	}

	for (auto component : _components)
	{
		component->Destroy();
	}
}

void Entity::Editor_SetName(String name)
{
	_name = std::move(name);
}
