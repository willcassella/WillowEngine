// Serialization.h
#pragma once

#include "..\TextFileReader.h"

namespace Willow
{
	class UTILITY_API ObjectFile
	{
		
	};

	class UTILITY_API Serializer
	{
		///////////////////////
		///   Information   ///
	public:

		friend ObjectFile;

		////////////////////////
		///   Constructors   ///
	private:

		Serializer(ObjectFile* file);
		~Serializer();

		///////////////////
		///   Methods   ///
	public:

		/** Adds a new node to this node, returning a serializer to that node */
		Serializer AddNode(const String& identifier);

		/** Sets the value of this node as a literal */
		void SetValue(const String& value);

		////////////////
		///   Data   ///
	private:

		ObjectFile* _file;
	};
}