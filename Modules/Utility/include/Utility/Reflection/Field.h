// Field.h
#pragma once

#include "Interface.h"
#include "InterfaceType.h"
#include "Type.h"

namespace Willow
{
	/** Generic field type */
	interface UTILITY_API IField : public Interface
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_INTERFACE

		///////////////////
		///   Methods   ///
	public:

		/** Returns the name of this field */
		virtual String GetName() const = 0;

		/** Returns the type of this field */
		virtual const Type& GetFieldType() const = 0;

		/** Returns the type that owns this field */
		virtual const class ClassType& GetOwnerType() const = 0;

		/** Returns the value of this field within the given owner 
		WARNING: FieldType must not be a PrimitiveType (check GetFieldType().IsA<PrimitiveType>() first)*/
		virtual const object& GetValue(const object& owner) const = 0;

		/** Gets the value of this field as a string, used for primitives (or if you just want the value as a string) */
		virtual String GetValueString(const object& owner) const = 0;

		///** Sets the value of this field within the given owner to the given value */
		//void SetValue(object& owner, const object& value) const;
	};

	BEGIN_INTERFACE_INFO(Willow::IField)
	END_REFLECTION_INFO

	/** Concrete field type, holding information about a field */
	template <class OwnerType, typename FieldType>
	class Field : public object, public IField
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(object)

		////////////////////////
		///   Constructors   ///
	public:

		Field(String name, FieldType OwnerType::* field)
		{
			_name = name;
			_field = field;
		}

		///////////////////
		///   Methods   ///
	public:

		/** Returns the state of this field as a string */
		String ToString() const override
		{
			return String::Format("Field: @.@", TypeInfo<OwnerType>().GetFullName(), TypeInfo<FieldType>().GetFullName());
		}

		/** Returns the name of this field */
		String GetName() const override
		{
			return _name;
		}

		/** Returns the type of this field */
		const Type& GetFieldType() const override
		{
			return TypeInfo<FieldType>();
		}

		/** Returns the type that owns this field */
		const ClassType& GetOwnerType() const override
		{
			return Cast<ClassType>(TypeInfo<OwnerType>());
		}

		/** Returns the value of this field within the given owner */
		const object& GetValue(const object& owner) const override
		{
			if (owner.IsA<OwnerType>())
			{
				if (!owner.GetType().IsA<PrimitiveType>())
				{
					// I need to do all this fuckery because C++ doesn't have static_if
					return *(const object*)(&(Cast<OwnerType>(owner).*_field));
				}
				else
				{
					// You can't GetValue() on a primitive field! (Hey, go blame the people who designed C++, not me. Seriously, C++ references suck ass)
					throw String("Attempt to call 'GetValue()' on a primitive field");
				}
			}
			else
			{
				// @TODO: Make this more than a string
				throw String("Given object does not have this field!");
			}
		}

		/** Returns the value of this field within the given owner as a string */
		String GetValueString(const object& owner) const override
		{
			if (owner.IsA<OwnerType>())
			{
				using Willow::ValueToString;
				return ValueToString(Cast<OwnerType>(owner).*_field);
			}
			else
			{
				throw String("Given object does not have this field!");
			}
		}

		////////////////
		///   Data   ///
	private:

		String _name;
		FieldType OwnerType::* _field;
	};

	BEGIN_TEMPLATE_INFO(Willow::Field, typename OwnerType, typename FieldType)
	IMPLEMENTS(IField)
	END_REFLECTION_INFO
}