// Transform.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Math/Mat4.h>
#include "config.h"

struct ENGINE_API Transform final
{
	///////////////////////
	///   Information   ///
public:

	REFLECTABLE_STRUCT

		///////////////////
		///   Methods   ///
public:

	void ToArchive(ArchiveWriter& writer) const
	{
		Operations::Default::ToArchive(*this, writer);
	}

	void FromArchive(const ArchiveReader& reader)
	{
		Operations::Default::FromArchive(*this, reader);
	}

	/** Returns the transformation matrix for this Transform. */
	Mat4 GetMatrix() const;

	/** Sets the location of this Transform. */
	FORCEINLINE void SetLocation(const Vec3& location)
	{
		_location = location;
	}

	/** Returns the location of this Transform. */
	FORCEINLINE const Vec3& GetLocation() const
	{
		return _location;
	}

	/** Sets the rotation of this Transform. */
	FORCEINLINE void SetRotation(const Quat& rotation)
	{
		_rotation = rotation;
	}

	/** Returns the rotation of this Transform. */
	FORCEINLINE const Quat& GetRotation() const
	{
		return _rotation;
	}

	/** Sets the scale of this Transform. */
	FORCEINLINE void SetScale(const Vec3& scale)
	{
		_scale = scale;
	}

	/** Returns the scale of this Transform. */
	FORCEINLINE const Vec3& GetScale() const
	{
		return _scale;
	}

	////////////////
	///   Data   ///
private:

	Vec3 _location;
	Quat _rotation;
	Vec3 _scale = { 1, 1, 1 };
};
