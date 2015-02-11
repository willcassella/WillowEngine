// Reference.h - Copyright 2013-2015 Will Cassella, All Rights Reserved
#pragma once

#include "../String.h"
#include "Reflection.h"

/** Smart pointer that holds a pointer to an instance of a reflected type */
struct CORE_API Reference final
{
	///////////////////////
	///   Information   ///
public:

	template <typename AnyType> friend struct Implementation::Unpack; // @TODO: Implement unpacking as "Unboxing" and casting

	///////////////////////
	///   Inner Types   ///
private:

	/** Non-templated handle for TReference */
	class IReference
	{
		////////////////////////
		///   Constructors   ///
	public:

		virtual ~IReference() = default;

		///////////////////
		///   Methods   ///
	public:

		/** Returns a String representation of the held value */
		virtual String ToString() const = 0;

		/** Returns the type information for the held value */
		virtual const TypeInfo& GetType() const = 0;

		/** Returns a pointer to the held value */
		virtual void* GetValue() const = 0;

		/** Returns whether the held value is immutable (const or non-const) */
		virtual bool IsImmutable() const = 0;

		/** Copies the implementation of this interface (does not copy value) */
		virtual IReference* Copy() const = 0;
	};

	/** Internal class for handling references */
	template <typename AnyType>
	class TReference final : public IReference
	{
		////////////////////////
		///   Constructors   ///
	public:

		/** Construct TReference from a non-const value */
		TReference(AnyType& value)
			: _isImmutable(false), _value(&value)
		{
			// All done
		}

		/** Construct TReference from a const value */
		TReference(const AnyType& value)
			: _isImmutable(true), _value(const_cast<AnyType*>(&value))
		{
			// All done
		}

		///////////////////
		///   Methods   ///
	public:
	
		String ToString() const override
		{
			return ::ToString(*_value);
		}

		const TypeInfo& GetType() const override
		{
			return TypeOf(*_value);
		}

		void* GetValue() const override
		{
			return _value;
		}

		bool IsImmutable() const override
		{
			return _isImmutable;
		}

		IReference* Copy() const override
		{
			return new TReference<AnyType>(This);
		}

		////////////////
		///   Data   ///
	private:

		bool _isImmutable;
		AnyType* _value;
	};

	////////////////////////
	///   Constructors   ///
public:

	/** Constructs a null Reference */
	Reference();

	/** Constructs a reference, referencing the value of a Value (References to Values are not allowed) // @TODO: Update this */
	Reference(const Value& value) = delete;

	/** Copy Reference (References to References are not allowed) */
	Reference(const Reference& copy);

	/** Moves the reference held by another Reference */
	Reference(Reference&& move);

	/** Destroy a Reference
	* NOTE: Does not destroy the held value ('Value' however, does do that) */
	~Reference();

	/** Create a mutable Reference to value */
	template <typename AnyType>
	Reference(AnyType& value)
		: _value(new TReference<AnyType>(value))
	{
		// All done
	}

	/** Create an immutable Reference to value */
	template <typename AnyType>
	Reference(const AnyType& value)
		: _value(new TReference<AnyType>(value))
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	/** Formats the state of the referenced value as a String */
	String ToString() const;

	/** Returns the type of the referenced value */
	const TypeInfo& GetType() const;

	/** Returns whether this reference points to a value */
	bool IsNull() const;

	/** Returns whether this reference points to an immutable value */
	bool IsImmutable() const;

	/** Nullifies this Reference */
	void Nullify();

	/////////////////////
	///   Operators   ///
public:

	/** Nullifies this Reference */
	Reference& operator=(std::nullptr_t);

	/** Assigns this Reference to the value held by a Value (References to Values are not allowed) // @TODO: Update documentation */
	Reference& operator=(const Value& value) = delete;

	/** Assigns this Reference to the value held by a Value */
	Reference& operator=(const Reference& copy);

	/** Moves the reference held by another Reference */
	Reference& operator=(Reference&& move);

	/** Assign Reference to a mutable value */
	template <typename AnyType>
	Reference& operator=(AnyType& value)
	{
		delete _value;
		_value = new TReference<AnyType>(value);

		return This;
	}

	/** Assign Reference to an immutable value */
	template <typename AnyType>
	Reference& operator=(const AnyType& value)
	{
		delete _value;
		_value = new TReference<AnyType>(value);

		return This;
	}

	////////////////
	///   Data   ///
private:

	IReference* _value;
};

// @TODO: Give NullReferenceException warnings on relevant methods