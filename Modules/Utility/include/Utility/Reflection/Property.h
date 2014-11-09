// Property.h
#pragma once

#include "Field.h"

namespace Willow
{
	template <class OwnerType, typename PropertyType>
	class Property : public object, public IField
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(object)

		////////////////////////
		///   Constructors   ///
	public:

		Property(const String& name, PropertyType&(OwnerType::*getter)(), void(OwnerType::*setter)(const PropertyType&))
		{
			_name = name;
			_getter = getter;
			_setter = setter;
		}

		///////////////////
		///   Methods   ///
	public:

		String GetName() const override
		{
			return _name;
		}

		const Type& GetFieldType() const override
		{
			return TypeInfo<PropertyType>();
		}

		const ClassType& GetOwnerType() const override
		{
			return Cast<ClassType>(TypeInfo<OwnerType>());
		}

		const object& GetValue(const object& owner) const override
		{
			if (owner.IsA<OwnerType>())
			{
				return Cast<OwnerType>(owner).*_getter();
			}
			else
			{
				throw String("Given object does not have this property");
			}
		}

		String GetValueString(const object& owner) const override
		{
			return "FUCK";
		}

		////////////////
		///   Data   ///
	private:

		String _name;
		PropertyType&(OwnerType::*_getter)();
		void(OwnerType::*_setter)(const PropertyType&);
	};
}