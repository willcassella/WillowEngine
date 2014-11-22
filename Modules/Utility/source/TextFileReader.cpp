// TextFileReader.cpp

#include <fstream>
#include <string>
#include "../include/Utility/TextFileReader.h"
#include "../include/Utility/Console.h"
using namespace Willow;

//////////////////////////
///   Implementation   ///

namespace Willow
{
	struct __Utility_TextFileReader_Impl__
	{
		//////////////////
		///   Fields   ///
	public:

		std::ifstream file;
	};
}

////////////////////////
///   Constructors   ///

TextFileReader::TextFileReader(const String& path)
{
	this->_impl = new __Utility_TextFileReader_Impl__();

	if (path.IsNullOrEmpty())
	{
		return;
	}
	else
	{
		this->Open(path);
	}
}

TextFileReader::TextFileReader(const TextFileReader& copy)
{
	_impl = new __Utility_TextFileReader_Impl__();
	This = copy;
}

TextFileReader::TextFileReader(TextFileReader&& copy)
{
	this->_impl = copy._impl;
	copy._impl = nullptr;
}

TextFileReader::~TextFileReader()
{
	if (_impl)
	{
		this->Close();
		delete _impl;
	}
}

///////////////////
///   Methods   ///

bool TextFileReader::FileOpen() const
{
	return _impl->file.is_open();
}

void TextFileReader::Open(const String& path)
{
	this->Close();
	this->_path = path;
	_impl->file.open(_path.Cstr());

	if (!this->FileOpen())
	{
		Console::Error("Could not open '@'", path);
	}
}

void TextFileReader::Close()
{
	if (this->FileOpen())
	{
		_impl->file.close();
		_path = "";
	}
}

void TextFileReader::Reset()
{
	if (this->FileOpen())
	{
		_impl->file.seekg(0, _impl->file.beg);
	}
}

String TextFileReader::GetPath() const
{
	return _path;
}

String TextFileReader::Dump(bool lineEndings)
{
	std::string line, source;
	if (this->FileOpen())
	{
		while (std::getline(_impl->file, line))
		{
			source += line;

			if (lineEndings)
			{
				source += '\n';
			}
		}
	}

	return source.c_str();
}

bool TextFileReader::GetNextLine(String& outLine)
{
	std::string line;
	bool end = true;
	if (this->FileOpen())
	{
		std::getline(_impl->file, line);
		end = !(!_impl->file);
	}
	outLine = line.c_str();
	return end;
}

TextFileReader& TextFileReader::operator=(const TextFileReader& copy)
{
	if (this != &copy)
	{
		this->Close();
		this->_path = copy._path;

		if (copy.FileOpen())
		{
			_impl->file.open(_path.Cstr());
			_impl->file.seekg(copy._impl->file.tellg());
		}
	}
	return This;
}

TextFileReader& TextFileReader::operator=(TextFileReader&& other)
{
	if (this != &other)
	{
		this->Close();
		delete _impl;

		this->_path = other._path;
		_impl = other._impl;
		other._impl = nullptr;
	}

	return This;
}

bool Willow::operator==(const TextFileReader& lhs, const TextFileReader& rhs)
{
	bool sameFile = lhs._path == rhs._path;
	bool sameSpot = lhs._impl->file.tellg() == rhs._impl->file.tellg();
	return sameFile && sameSpot;
}