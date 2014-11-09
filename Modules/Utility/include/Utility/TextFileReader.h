// TextFileReader.h
#pragma once

#include "String.h"

namespace Willow
{
	/** Class representing a File reader object
	WARNING: A lot of this is subject to change */
	class UTILITY_API TextFileReader
	{
		////////////////////////
		///   Constructors   ///
	public:

		TextFileReader(const String& path = "");
		TextFileReader(const TextFileReader& copy);
		TextFileReader(TextFileReader&& other);
		~TextFileReader();

		///////////////////
		///   Methods   ///
	public:

		/** Returns whether this file reader has a file open was successfully loaded */
		bool FileOpen() const;

		/** Opens a file */
		void Open(const String& path);

		/** Closes the currently active file */
		void Close();

		/** Sends the reader back to the top of the file */
		void Reset();

		/** Returns the path this reader is reading from */
		String GetPath() const;

		/** Dumps the whole file into a string
		lineEndings: Whether to include line engines in the dump */
		String Dump(bool lineEndings = true);

		/** Reads the next line in the file into outLine
		* If the file has nothing left, returns false */
		bool GetNextLine(String& outLine);

		/////////////////////
		///   Operators   ///
	public:

		TextFileReader& operator=(const TextFileReader& copy);
		TextFileReader& operator=(TextFileReader&& other);
		friend UTILITY_API bool operator==(const TextFileReader& lhs, const TextFileReader& rhs);
		friend UTILITY_API inline bool operator!=(const TextFileReader& lhs, const TextFileReader& rhs)
		{
			return !(lhs == rhs);
		}

		////////////////
		///   Data   ///
	private:

		String _path;
		struct __Utility_TextFileReader_Impl__* _impl;
	};
}