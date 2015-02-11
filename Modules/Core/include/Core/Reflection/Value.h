// Value.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../String.h"
#include "Reflection.h"

/** Smart pointer that holds an instance of a reflected type */
struct CORE_API Value final
{
	///////////////////////
	///   Information   ///
public:

	template <typename TargetType> friend struct Implementation::Unpack;

	///////////////////////
	///   Inner Types   ///
private:

	/** Non-templated handle for TValue */
	class IValue
	{
		////////////////////////
		///   Constructors   ///
	public:

		virtual ~IValue() = default;

		///////////////////
		///   Methods   ///
	public:

		/** Returns the String representation for the value */
		virtual String ToString() const = 0;

		/** Gets the type that this Value holds */
		virtual const TypeInfo& GetType() const = 0;

		/** Returns a pointer to the value */
		virtual void* GetValue() const = 0;

		/** Copies this IValue and a returns a pointer to the copy */
		virtual IValue* Copy() const = 0;
	};

	/** Container for the held value */
	template <typename AnyType>
	class TValue final : public IValue
	{
		////////////////////////
		///   Constructors   ///
	public:

		TValue(const AnyType& value)
		{
			// @TODO: Clone value
			_value = new AnyType(value);
		}
		~TValue() override
		{
			delete _value;
		}

		///////////////////
		///   Methods   ///
	public:

		void* GetValue() const override
		{
			return _value;
		}

		const TypeInfo& GetType() const override
		{
			return TypeOf(*_value);
		}

		virtual String ToString() const override
		{
			return ::ToString(*_value);
		}

		IValue* Copy() const override
		{
			return new TValue<AnyType>(*_value);
		}

		////////////////
		///   Data   ///
	private:

		AnyType* _value;
	};

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs a null Value */
	Value();

	/** Copies the value pointed to by a Reference (Values of References are not allowed) */
	Value(const Reference& reference) = delete;

	/** Copies the value of a another Value (Values of Values are not allowed) */
	Value(const Value& copy);

	Value(Value&& move);

	~Value();

	/** Create Value from instance of AnyType */
	template <typename AnyType>
	Value(const AnyType& value)
		: _value(new TValue<AnyType>(value))
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the state of this Value as a String */
	struct String ToString() const;

	/** Returns the Type of the value this Value holds */
	const TypeInfo& GetType() const;

	/** Returns whether this Value actually holds a value */
	bool IsNull() const;

	/** Nullifies this Value */
	void Nullify();

	/////////////////////
	///   Operators   ///
public:

	/** Copies the value held by a Reference (Values of References are not allowed) */
	Value& operator=(const Reference& reference) = delete;

	/** Copies the value held by another Value (Values of Values are not allowed) */
	Value& operator=(const Value& copy);

	Value& operator=(Value&& move);

	/** Assign Value from instance of AnyType */
	template <typename AnyType>
	Value& operator=(const AnyType& value)
	{
		delete _value;
		this->_value = new TValue<AnyType>(value);
		return This;
	}

	////////////////
	///   Data   ///
private:

	IValue* _value;
};

// @TODO: Update documentation to give warnings for relevant exceptions