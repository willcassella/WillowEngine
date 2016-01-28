// XMLArchive.cpp

#include <pugixml.hpp>
#include "../../include/Resource/Archives/XMLArchive.h"

/////////////////
///   Types   ///

/** Archive wrapper for pugi::xml_node. */
struct XMLNode final : ArchiveWriter
{
	////////////////////////
	///   Constructors   ///
public:

	XMLNode(pugi::xml_node node)
		: Node(std::move(node))
	{
		// All done
	}

	//////////////////
	///   Fields   ///
public:

	pugi::xml_node Node;

	///////////////////
	///   Methods   ///
public:

	void SetValue(bool value) override
	{
		Node.append_attribute("value") = value;
	}

	void SetValue(char value) override
	{
		Node.append_attribute("value") = value;
	}

	void SetValue(byte value) override
	{
		Node.append_attribute("value") = value;
	}

	void SetValue(int16 value) override
	{
		Node.append_attribute("value") = value;
	}

	void SetValue(uint16 value) override
	{
		Node.append_attribute("value") = value;
	}

	void SetValue(int32 value) override
	{
		Node.append_attribute("value") = value;
	}

	void SetValue(uint32 value) override
	{
		Node.append_attribute("value") = value;
	}

	void SetValue(int64 value) override
	{
		Node.append_attribute("value") = value;
	}

	void SetValue(uint64 value) override
	{
		Node.append_attribute("value") = value;
	}

	void SetValue(float value) override
	{
		Node.append_attribute("value") = value;
	}

	void SetValue(double value) override
	{
		Node.append_attribute("value") = value;
	}

	void SetValue(long double value) override
	{
		Node.append_attribute("value") = static_cast<double>(value);
	}

	void SetValue(const String& value) override
	{
		Node.append_attribute("value") = value.Cstr();
	}

	void PushHandler(FunctionView<void, ArchiveWriter&> handler, const String& name) override
	{
		XMLNode child = Node.append_child(name.Cstr());
		handler(child);
	}
};

/** Allows XMLArchive to hold a pugi::xml_document without exposing that to the header. */
struct XMLDoc final
{
	pugi::xml_document Doc;
};

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(XMLArchive);

////////////////////////
///   Constructors   ///

XMLArchive::XMLArchive()
{
	_doc = std::make_unique<XMLDoc>();
}

XMLArchive::~XMLArchive()
{
	// Do nothing (prevents incomplete type errors)
}

///////////////////
///   Methods   ///

bool XMLArchive::Load(const Path& path)
{
	auto result = _doc->Doc.load_file(path.ToString().Cstr());
	return result == pugi::xml_parse_status::status_ok;
}

bool XMLArchive::Save(const Path& path) const
{
	return _doc->Doc.save_file(path.ToString().Cstr());
}

void XMLArchive::AddRoot(FunctionView<void, ArchiveWriter&> handler)
{
	XMLNode root = _doc->Doc.append_child("root");
	handler(root);
}

void XMLArchive::GetRoot(FunctionView<void, const ArchiveReader&>) const
{
	// TODO: Implement this
}
