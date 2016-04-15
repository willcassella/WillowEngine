// Path.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <Core/Reflection/StructInfo.h>
#include "config.h"

namespace willow
{
	struct RESOURCE_API Path final
	{
		///////////////////////
		///   Information   ///
	public:

		REFLECTABLE_STRUCT

		////////////////////////
		///   Constructors   ///
	public:

		Path() = default;
		Path(CString path)
			: _path{ path }
		{
			this->sanitize();
		}
		Path(String path)
			: _path{ std::move(path) }
		{
			this->sanitize();
		}

		///////////////////
		///   Methods   ///
	public:

		/** Returns this Path as a String. */
		const String& ToString() const
		{
			return _path;
		}

		/** Serializes the state of this Path to an archive. */
		void ToArchive(ArchiveWriter& writer) const;

		/** Sets the state of this Path from the given archive. */
		void FromArchive(const ArchiveReader& reader);

		/** Returns this path as a c-string. */
		CString c_str() const &
		{
			return this->_path.Cstr();
		}

		/** If the given String represents a path to a file, this parses and returns the file extension */
		String get_file_extension() const;

		/** If the given String represents a path to a file, this parses and returns the name of the file */
		String get_file_name() const;

		/** Returns whether this Path is empty. */
		bool is_empty() const;

		/** Returns whether this Path actually points to a file. */
		bool points_to_file() const;

	private:

		/** Makes sure this path has a valid scope. */
		void sanitize();

		/////////////////////
		///   Operators   ///
	public:

		operator const String&() const
		{
			return _path;
		}
		friend FORCEINLINE bool operator==(const Path& lhs, const Path& rhs)
		{
			return lhs._path == rhs._path;
		}
		friend FORCEINLINE bool operator==(const Path& lhs, const String& rhs)
		{
			return lhs._path == rhs;
		}
		friend FORCEINLINE bool operator==(const String& lhs, const Path& rhs)
		{
			return rhs == lhs;
		}
		friend FORCEINLINE bool operator!=(const Path& lhs, const Path& rhs)
		{
			return lhs._path != rhs._path;
		}
		friend FORCEINLINE bool operator!=(const Path& lhs, const String& rhs)
		{
			return !(lhs == rhs);
		}
		friend FORCEINLINE bool operator!=(const String& lhs, const Path& rhs)
		{
			return rhs != lhs;
		}

		////////////////
		///   Data   ///
	private:

		String _path;
	};
}

/////////////////////
///   Functions   ///

/** Custom operator for String literals. */
inline willow::Path operator"" _p(CString string, std::size_t /*size*/)
{
	return{ string };
}
