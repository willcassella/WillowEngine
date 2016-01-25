// CapsuleComponent.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "PhysicalComponent.h"

class ENGINE_API CapsuleComponent : public PhysicalComponent
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_CLASS
	EXTENDS(PhysicalComponent)

	////////////////////////
	///   Constructors   ///
public:

	CapsuleComponent();
	~CapsuleComponent() override;

	///////////////////
	///   Methods   ///
public:

	/** Returns the radius of this CapsuleComponent. */
	Scalar GetRadius() const;

	/** Returns the height of this CapsuleComponent. */
	Scalar GetHeight() const;

	/** Sets the radius of this CapsuleComponent. */
	void SetRadius(Scalar radius);

	/** Sets the height of this CapsuleComponent. */
	void SetHeight(Scalar height);

private:

	btCollisionShape* GetShape() final override;

	////////////////
	///   Data   ///
private:

	std::unique_ptr<btCapsuleShape> _shape;
};
