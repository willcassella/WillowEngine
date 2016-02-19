// XMLArchive.cpp

#include <pugixml.hpp>
#include "../../include/Resource/Archives/XMLArchive.h"

/////////////////
///   Types   ///

/** Archive wrapper for pugi::xml_node. */
struct XMLNode final : ArchiveWriter, ArchiveReader
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

	String GetName() const override
	{
		return Node.name();
	}

	void GetValue(bool& value) const override
	{
		value = Node.first_attribute().as_bool(value);
	}

	void GetValue(char& value) const override
	{
		value = static_cast<char>(Node.first_attribute().as_int(value));
	}

	void GetValue(byte& value) const override
	{
		value = static_cast<byte>(Node.first_attribute().as_uint(value));
	}

	void GetValue(int16& value) const override
	{
		value = static_cast<int16>(Node.first_attribute().as_int(value));
	}

	void GetValue(uint16& value) const override
	{
		value = static_cast<uint16>(Node.first_attribute().as_uint(value));
	}

	void GetValue(int32& value) const override
	{
		value = static_cast<int32>(Node.first_attribute().as_int(value));
	}

	void GetValue(uint32& value) const override
	{
		value = static_cast<uint32>(Node.first_attribute().as_uint(value));
	}

	void GetValue(int64& value) const override
	{
		FromString(value, Node.first_attribute().value());
	}

	void GetValue(uint64& value) const override
	{
		FromString(value, Node.first_attribute().value());
	}

	void GetValue(float& value) const override
	{
		value = Node.first_attribute().as_float(value);
	}

	void GetValue(double& value) const override
	{
		value = Node.first_attribute().as_double(value);
	}

	void GetValue(long double& value) const override
	{
		FromString(value, Node.first_attribute().value());
	}

	void GetValue(String& value) const override
	{
		value = Node.first_attribute().value();
	}

	bool IsNull() const override
	{
		return Node.attribute("null") != nullptr;
	}

	bool GetFirstChild(FunctionView<void, const ArchiveReader&> function) const override
	{
		auto child = Node.first_child();

		if (child != nullptr)
		{
			XMLNode node(child);
			function(node);
			return true;
		}
		else
		{
			return false;
		}
	}

	bool GetChild(uint32 index, FunctionView<void, const ArchiveReader&> function) const override
	{
		uint32 i = 0;
		for (auto child : Node.children())
		{
			if (i == index)
			{
				XMLNode node(child);
				function(node);
				return true;
			}
			else
			{
				++i;
			}
		}

		return false;
	}

	bool GetChild(const String& name, FunctionView<void, const ArchiveReader&> function) const override
	{
		auto child = Node.child(name.Cstr());

		if (!child.empty())
		{
			XMLNode node(child);
			function(node);
			return true;
		}
		else
		{
			return false;
		}
	}

	void EnumerateChildren(const EnumeratorView<const ArchiveReader&>& enumerator) const override
	{
		for (auto child : Node.children())
		{
			XMLNode node(child);
			enumerator.Invoke(node);
		}
	}

	void EnumerateChildren(const String& name, const EnumeratorView<const ArchiveReader&>& enumerator) const override
	{
		for (auto child : Node.children(name.Cstr()))
		{
			XMLNode node(child);
			enumerator(node);
		}
	}

	void SetValue(bool value) override
	{
		Node.append_attribute("value") = value;
	}

	void SetValue(char value) override
	{
		Node.append_attribute("value") = static_cast<int>(value);
	}

	void SetValue(byte value) override
	{
		Node.append_attribute("value") = static_cast<unsigned int>(value);
	}

	void SetValue(int16 value) override
	{
		Node.append_attribute("value") = static_cast<int>(value);
	}

	void SetValue(uint16 value) override
	{
		Node.append_attribute("value") = static_cast<unsigned int>(value);
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
		Node.append_attribute("value") = ToString(value).Cstr();
	}

	void SetValue(uint64 value) override
	{
		Node.append_attribute("value") = ToString(value).Cstr();
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
		Node.append_attribute("value") = ToString(value).Cstr();
	}

	void SetValue(const String& value) override
	{
		Node.append_attribute("value") = value.Cstr();
	}

	void SetValue(std::nullptr_t) override
	{
		Node.append_attribute("null");
	}

	void AddChild(const String& name, FunctionView<void, ArchiveWriter&> function) override
	{
		XMLNode child(Node.append_child(name.Cstr()));
		function(child);
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
	XMLNode root(_doc->Doc.append_child("root"));
	handler(root);
}

void XMLArchive::GetRoot(FunctionView<void, const ArchiveReader&> handler) const
{
	XMLNode root(_doc->Doc.first_child());
	handler(root);
}
