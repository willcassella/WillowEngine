// String.h
#pragma once

#include <ostream>
#include "Array.h"

namespace Willow
{
	template class UTILITY_API Array<uint32>;
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
		size_t Length() const;
		const char* Cstr() const;
		String SubString(uint32 start) const;
		String SubString(uint32 start, uint32 end) const;
		Array<uint32> OccurencesOf(const String& string) const;
		String GetFileExtension() const;
		static size_t Length(const char* string);

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
		friend UTILITY_API std::ostream& operator<<(std::ostream& lhs, const String& rhs);

		////////////////
		///   Data   ///
	private:

		char* _value;
	};
}