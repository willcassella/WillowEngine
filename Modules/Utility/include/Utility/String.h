// String.h
#pragma once

#include "List.h"

namespace Willow
{
	struct UTILITY_API String
	{
		////////////////////////
		///   Constructors   ///
	public:

		String(const char* value = "");
		String(const String& copy);
		String(String&& other);
		~String();

		///////////////////
		///   Methods   ///
	public:

		bool IsNullOrEmpty() const;
		uint32 Length() const;
		const char* Cstr() const;
		String SubString(uint32 start) const;
		String SubString(uint32 start, uint32 end) const;
		String ToUpper() const;
		String ToLower() const;
		List<uint32> OccurencesOf(const String& string) const;
		String GetFileExtension() const;
		String GetFileName() const;
		static uint32 Length(const char* string);

		/////////////////////
		///   Operators   ///
	public:

		String& operator=(const String& rhs);
		String& operator=(String&& other);
		friend UTILITY_API bool operator==(const String& lhs, const String& rhs);
		friend UTILITY_API bool operator!=(const String& lhs, const String& rhs);
		friend UTILITY_API bool operator>(const String& lhs, const String& rhs);
		friend UTILITY_API bool operator>=(const String& lhs, const String& rhs);
		friend UTILITY_API bool operator<(const String& lhs, const String& rhs);
		friend UTILITY_API bool operator<=(const String& lhs, const String& rhs);
		friend UTILITY_API String operator+(const String& lhs, const String& rhs);
		friend UTILITY_API String& operator+=(String& lhs, const String& rhs);

		////////////////
		///   Data   ///
	private:

		char* _value;
	};
}