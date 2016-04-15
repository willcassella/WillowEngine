// XMLArchive.cpp

#include <pugixml.hpp>
#include <Core/Reflection/ClassInfo.h>
#include "../../include/Resource/Archives/XMLArchive.h"

namespace willow
{
	/////////////////
	///   Types   ///

	/** Archive wrapper for pugi::xml_node. */
	struct XMLNode final : ArchiveWriter, ArchiveReader
	{
		////////////////////////
		///   Constructors   ///
	public:

		XMLNode(const Archive& archive, pugi::xml_node node)
			: archive(&archive), node(std::move(node))
		{
			// All done
		}

		//////////////////
		///   Fields   ///
	public:

		const Archive* archive;
		pugi::xml_node node;

		///////////////////
		///   Methods   ///
	public:

		void MapRefID(ArchiveRefID refID, void* pointer) const override
		{
			this->archive->RefTable[refID] = pointer;
		}

		ArchiveRefID GetRefID() const override
		{
			auto idAttr = this->node.attribute("ref_id");
			ArchiveRefID value = 0;

			if (idAttr)
			{
				FromString(value, idAttr.value());
			}

			return value;
		}

		String GetName() const override
		{
			return this->node.name();
		}

		void GetValue(bool& value) const override
		{
			value = this->node.attribute("value").as_bool(value);
		}

		void GetValue(char& value) const override
		{
			value = static_cast<char>(this->node.attribute("value").as_int(value));
		}

		void GetValue(byte& value) const override
		{
			value = static_cast<byte>(this->node.attribute("value").as_uint(value));
		}

		void GetValue(int16& value) const override
		{
			value = static_cast<int16>(this->node.attribute("value").as_int(value));
		}

		void GetValue(uint16& value) const override
		{
			value = static_cast<uint16>(this->node.attribute("value").as_uint(value));
		}

		void GetValue(int32& value) const override
		{
			value = static_cast<int32>(this->node.attribute("value").as_int(value));
		}

		void GetValue(uint32& value) const override
		{
			value = static_cast<uint32>(this->node.attribute("value").as_uint(value));
		}

		void GetValue(int64& value) const override
		{
			FromString(value, this->node.attribute("value").value());
		}

		void GetValue(uint64& value) const override
		{
			FromString(value, this->node.attribute("value").value());
		}

		void GetValue(float& value) const override
		{
			value = this->node.attribute("value").as_float(value);
		}

		void GetValue(double& value) const override
		{
			value = this->node.attribute("value").as_double(value);
		}

		void GetValue(long double& value) const override
		{
			FromString(value, this->node.attribute("value").value());
		}

		void GetValue(String& value) const override
		{
			value = this->node.attribute("value").value();
		}

		void GetValue(void*& value) const override
		{
			if (this->IsNull())
			{
				value = nullptr;
				return;
			}

			// Find the ref in the table
			ArchiveRefID ref = 0;
			FromString(ref, this->node.attribute("ref").value());
			auto result = this->archive->RefTable.Find(ref);
			
			// If the key does not exist in the reftable, this ref cannot be resolved
			if (!result)
			{
				throw UnresolvedArchiveReferenceException{ ref };
			}

			value = *result;
		}

		bool IsNull() const override
		{
			return this->node.attribute("ref").value() == "null"_s;
		}

		bool GetFirstChild(FunctionView<void, const ArchiveReader&> function) const override
		{
			auto child = this->node.first_child();

			if (child != nullptr)
			{
				XMLNode node(*this->archive, child);
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
			for (auto child : this->node.children())
			{
				if (i == index)
				{
					XMLNode node(*this->archive, child);
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
			auto child = this->node.child(name.Cstr());

			if (!child.empty())
			{
				XMLNode node(*this->archive, child);
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
			for (auto child : this->node.children())
			{
				XMLNode node(*this->archive, child);
				enumerator.Invoke(node);
			}
		}

		void EnumerateChildren(const String& name, const EnumeratorView<const ArchiveReader&>& enumerator) const override
		{
			for (auto child : this->node.children(name.Cstr()))
			{
				XMLNode node(*this->archive, child);
				enumerator(node);
			}
		}

		void SetRefID(const void* refID) override
		{
			auto value = reinterpret_cast<ArchiveRefID>(refID);
			this->node.append_attribute("ref_id") = ToString(value).Cstr();
		}

		void SetValue(bool value) override
		{
			this->node.append_attribute("value") = value;
		}

		void SetValue(char value) override
		{
			this->node.append_attribute("value") = static_cast<int>(value);
		}

		void SetValue(byte value) override
		{
			this->node.append_attribute("value") = static_cast<unsigned int>(value);
		}

		void SetValue(int16 value) override
		{
			this->node.append_attribute("value") = static_cast<int>(value);
		}

		void SetValue(uint16 value) override
		{
			this->node.append_attribute("value") = static_cast<unsigned int>(value);
		}

		void SetValue(int32 value) override
		{
			this->node.append_attribute("value") = value;
		}

		void SetValue(uint32 value) override
		{
			this->node.append_attribute("value") = value;
		}

		void SetValue(int64 value) override
		{
			this->node.append_attribute("value") = ToString(value).Cstr();
		}

		void SetValue(uint64 value) override
		{
			this->node.append_attribute("value") = ToString(value).Cstr();
		}

		void SetValue(float value) override
		{
			this->node.append_attribute("value") = value;
		}

		void SetValue(double value) override
		{
			this->node.append_attribute("value") = value;
		}

		void SetValue(long double value) override
		{
			this->node.append_attribute("value") = ToString(value).Cstr();
		}

		void SetValue(const char* value) override
		{
			this->node.append_attribute("value") = value;
		}

		void SetValue(const void* value) override
		{
			this->node.append_attribute("ref") = ToString(reinterpret_cast<ArchiveRefID>(value)).Cstr();
		}

		void SetValue(std::nullptr_t) override
		{
			this->node.append_attribute("ref") = "null";
		}

		void AddChild(const String& name, FunctionView<void, ArchiveWriter&> function) override
		{
			XMLNode child(*this->archive, this->node.append_child(name.Cstr()));
			function(child);
		}
	};

	/** Allows XMLArchive to hold a pugi::xml_document without exposing that to the header. */
	struct XMLDoc final
	{
		pugi::xml_document Doc;
	};
}

//////////////////////
///   Reflection   ///

BUILD_REFLECTION(willow::XMLArchive);

namespace willow
{
	////////////////////////
	///   Constructors   ///

	XMLArchive::XMLArchive()
		: _doc{ std::make_unique<XMLDoc>() }
	{
		// All done
	}

	XMLArchive::~XMLArchive()
	{
		// Do nothing (prevents incomplete type errors)
	}

	///////////////////
	///   Methods   ///

	bool XMLArchive::load(const Path& path)
	{
		auto result = this->_doc->Doc.load_file(path.c_str());
		return result == pugi::xml_parse_status::status_ok;
	}

	bool XMLArchive::save(const Path& path) const
	{
		return this->_doc->Doc.save_file(path.c_str());
	}

	void XMLArchive::add_root(FunctionView<void, ArchiveWriter&> handler)
	{
		XMLNode root(*this, this->_doc->Doc.append_child("root"));
		handler(root);
	}

	void XMLArchive::get_root(FunctionView<void, const ArchiveReader&> handler) const
	{
		XMLNode root(*this, this->_doc->Doc.first_child());
		handler(root);
	}
}
