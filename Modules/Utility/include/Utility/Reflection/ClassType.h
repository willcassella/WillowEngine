// ClassType.h
#pragma once

#include "..\List.h"
#include "Field.h"
#include "Property.h"
#include "InterfaceType.h"
#include "..\Console.h"

namespace Willow
{
	/** Type holding information about class types */
	class UTILITY_API ClassType : public Type
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE
		EXTENDS(Type)

		////////////////////////
		///   Constructors   ///
	protected:

		ClassType(const String& fullName);

	public:

		~ClassType();

		/** Registers a new class */
		template <class UserClass>
		static ClassType Create(const String& fullName)
		{
			ClassType type(fullName);
			type._size = sizeof(UserClass);
			return type;
		}

		///////////////////
		///   Methods   ///
	public:

		/** Returns the namespace this class was declared in */
		String GetNamespace() const;

		/** Returns the full name of this class (including namespace) */
		String GetFullName() const override;

		/** Returns the type info for the base type of this class
		* Returns nullptr if this type is the root of inheritance (such as object) */
		const ClassType* GetBase() const;

		/** Returns a list of all the fields in this class */
		List<const IField&> GetFields() const;

		/** Returns a list of all the fields in this class, including inherited fields */
		List<const IField&> GetAllFields() const;

		/** Returns whether this type is the root of an inheritance tree (such as object) */
		bool IsRoot() const;

		/** Returns whether this type is a subclass of the given type */
		bool IsSubClassOf(const ClassType& base) const;

		/** Returns whether this type implements the given interface */
		bool ImplementsInterface(const InterfaceType& interf) const;

		/** Returns whether this class is factory constructable */
		bool HasFactory() const;

		/** Creates a new instance of this class
		* WARNING: This class must have a factory function, check HasFactory() first 
		* WARNING: The returned instance must be deleted manually */
		object& CreateNew() const;

		/** Returns whether this type is a subclass of the given type */
		template <class BaseType>
		bool IsSubClassOf() const
		{
			const Type& type = TypeInfo<BaseType>();
			if (type.IsA<ClassType>())
			{
				return this->IsSubClassOf(Cast<ClassType>(type));
			}
			else
			{
				return false;
			}
		}

		/** Returns whether this type implements the given interface */
		template <class UserInterface>
		bool ImplementsInterface()
		{
			const Type& type = TypeInfo<UserInterface>();
			if (type.IsA<InterfaceType>())
			{
				return this->ImplementsInterface(Cast<InterfaceType>(type));
			}
			else
			{
				return false;
			}
		}

		/** Sets the base class of this type
		* WARNING: BaseType must be a ClassType */
		template <class BaseType>
		void SetBase()
		{
			const Type& type = TypeInfo<BaseType>();
			if (type.IsA<ClassType>())
			{
				this->_base = &Cast<ClassType>(type);
			}
			else
			{
				throw String("A non-class type cannot be a base type");
			}
		}
		
		/** Specifies the interfaces implemented by this class */
		template <class ... Interfaces>
		void AddInterfaces()
		{
			for (const auto& interf : MultipleTypeInfo<Interfaces...>())
			{
				if (interf.IsA<InterfaceType>())
				{
					_interfaces.Add(&Cast<InterfaceType>(interf));
				}
				else
				{
					Console::Error("Error registering type @, @ is not an interface", this->GetFullName(), interf.GetFullName());
				}
			}
		}

		/** Specifies that this type has a factory
		* If your type is not default constructable, you can specialize __create__<T> for your class */
		template <class UserClass>
		void SetFactory()
		{
			_factory = Factory<UserClass>;
		}

		/** Adds a new field to this class */
		template <class OwnerType, typename FieldType>
		IField& AddField(const String& name, FieldType OwnerType::*field)
		{
			_fields.Add(new Field<OwnerType, FieldType>(name, field));
			return *_fields.Last();
		}

		/** Adds a new property to this class */
		template <class OwnerType, typename PropertyType>
		IField& AddProperty(const String& name, PropertyType&(OwnerType::*getter)(), void(OwnerType::*setter)(const PropertyType&))
		{
			_fields.Add(new Property<OwnerType, PropertyType>(name, getter, setter));
			return *_fields.Last();
		}

		////////////////
		///   Data   ///
	private:

		String _namespace;
		const ClassType* _base;
		List<const InterfaceType*> _interfaces;
		object&(*_factory)();
		List<IField*> _fields;
	};

	/** TypeInfo specialization for Willow::object */
	template <>
	struct __type_info__<object>
	{
		static const Type& __get_type_info__()
		{
			static auto myType = ClassType::Create<object>("Willow::object");
			return myType;
		}
	};

	/** TypeInfo specialization for Willow::Interace */
	template <>
	struct __type_info__<Interface>
	{
		static const Type& __get_type_info__()
		{
			static auto myType = ClassType::Create<Interface>("Willow::Interface");
			return myType;
		}
	};
}