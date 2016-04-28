// SubClassOf.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include "../Application.h"
#include "../IO/ArchiveReader.h"
#include "../IO/ArchiveWriter.h"
#include "ClassInfo.h"
#include "StructInfo.h"

/////////////////
///   Types   ///

/** Points to a type that extends 'T' (may be null). */
template <class T>
struct SubClassOf final
{
	////////////////////////
	///   Constructors   ///
public:

	SubClassOf()
		: _class{ nullptr }
	{
		
	}
	SubClassOf(const ClassInfo& type)
		: _class{ &type }
	{
		assert(type.is_castable_to(TypeOf<T>()));
	}

	template <class F>
	SubClassOf(SubClassOf<F> type)
		: _class{ type.get_class() }
	{
		static_assert(std::is_base_of<T, F>::value, "");
	}

	///////////////////
	///   Methods   ///
public:

	void ToArchive(ArchiveWriter& writer) const
	{
		if (this->_class)
		{
			writer.SetValue(_class->get_name());
		}
		else
		{
			writer.SetValue(nullptr);
		}
	}

	void FromArchive(const ArchiveReader& reader)
	{
		if (reader.IsNull())
		{
			this->_class = nullptr;
		}
		else
		{
			// Get the type
			String name;
			reader.GetValue(name);
			auto type = Application::FindType(name);

			// If the type exists
			if (type)
			{
				// And it's a class
				if (auto cType = Cast<ClassInfo>(*type))
				{
					// AND it extends 'T'
					if (cType->Extends(TypeOf<T>()))
					{
						// Use it
						this->_class = cType;
					}
				}
			}
		}
	}

	/** Returns whether this points to a class. */
	bool is_null() const
	{
		return this->_class == nullptr;
	}

	/** Returns the class this points to. */
	const ClassInfo* get_class() const
	{
		return this->_class;
	}

	////////////////
	///   Data   ///
private:

	const ClassInfo* _class;
};

//////////////////////
///   Operations   ///

namespace Implementation
{
	template <class T>
	struct TypeOf< SubClassOf<T> > final
	{
		/** Defined below */
		static const StructInfo StaticTypeInfo;

		static const StructInfo& Function()
		{
			return StaticTypeInfo;
		}

		static const StructInfo& Function(SubClassOf<T> /*value*/)
		{
			return StaticTypeInfo;
		}
	};

	/** Register TypeInfo for SubClassOf */
	template <class T>
	const StructInfo TypeOf<SubClassOf<T>>::StaticTypeInfo = TypeInfoBuilder<SubClassOf<T>>("SubClasOf");
}
