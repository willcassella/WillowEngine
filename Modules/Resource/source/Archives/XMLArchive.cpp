// XMLArchive.cpp

#include <pugixml.hpp>
#include "../../include/Resource/Archives/XMLArchive.h"

namespace Willow
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
			: Archive(&archive), Node(std::move(node))
		{
			// All done
		}

		//////////////////
		///   Fields   ///
	public:

		const Willow::Archive* Archive;
		pugi::xml_node Node;

		///////////////////
		///   Methods   ///
	public:

		void MapRefID(ArchiveRefID refID, void* pointer) const override
		{
			this->Archive->RefTable[refID] = pointer;
		}

		ArchiveRefID GetRefID() const override
		{
			auto idAttr = this->Node.attribute("refID");
			ArchiveRefID value = 0;

			if (idAttr)
			{
				FromString(value, idAttr.value());
			}

			return value;
		}

		String GetName() const override
		{
			return this->Node.name();
		}

		void GetValue(bool& value) const override
		{
			value = this->Node.attribute("value").as_bool(value);
		}

		void GetValue(char& value) const override
		{
			value = static_cast<char>(this->Node.attribute("value").as_int(value));
		}

		void GetValue(byte& value) const override
		{
			value = static_cast<byte>(this->Node.attribute("value").as_uint(value));
		}

		void GetValue(int16& value) const override
		{
			value = static_cast<int16>(this->Node.attribute("value").as_int(value));
		}

		void GetValue(uint16& value) const override
		{
			value = static_cast<uint16>(this->Node.attribute("value").as_uint(value));
		}

		void GetValue(int32& value) const override
		{
			value = static_cast<int32>(this->Node.attribute("value").as_int(value));
		}

		void GetValue(uint32& value) const override
		{
			value = static_cast<uint32>(this->Node.attribute("value").as_uint(value));
		}

		void GetValue(int64& value) const override
		{
			FromString(value, this->Node.attribute("value").value());
		}

		void GetValue(uint64& value) const override
		{
			FromString(value, this->Node.attribute("value").value());
		}

		void GetValue(float& value) const override
		{
			value = this->Node.attribute("value").as_float(value);
		}

		void GetValue(double& value) const override
		{
			value = this->Node.attribute("value").as_double(value);
		}

		void GetValue(long double& value) const override
		{
			FromString(value, this->Node.attribute("value").value());
		}

		void GetValue(String& value) const override
		{
			value = this->Node.attribute("value").value();
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
			FromString(ref, this->Node.attribute("ref").value());
			auto result = this->Archive->RefTable.Find(ref);
			
			// If the key does not exist in the reftable, this ref cannot be resolved
			if (!result)
			{
				throw UnresolvedArchiveReferenceException{ ref };
			}

			value = *result;
		}

		bool IsNull() const override
		{
			return this->Node.attribute("ref").value() == "null"_s;
		}

		bool GetFirstChild(FunctionView<void, const ArchiveReader&> function) const override
		{
			auto child = this->Node.first_child();

			if (child != nullptr)
			{
				XMLNode node(*this->Archive, child);
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
			for (auto child : this->Node.children())
			{
				if (i == index)
				{
					XMLNode node(*this->Archive, child);
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
			auto child = this->Node.child(name.Cstr());

			if (!child.empty())
			{
				XMLNode node(*this->Archive, child);
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
			for (auto child : this->Node.children())
			{
				XMLNode node(*this->Archive, child);
				enumerator.Invoke(node);
			}
		}

		void EnumerateChildren(const String& name, const EnumeratorView<const ArchiveReader&>& enumerator) const override
		{
			for (auto child : this->Node.children(name.Cstr()))
			{
				XMLNode node(*this->Archive, child);
				enumerator(node);
			}
		}

		void SetRefID(const void* refID) override
		{
			auto value = reinterpret_cast<ArchiveRefID>(refID);
			this->Node.append_attribute("refID") = ToString(value).Cstr();
		}

		void SetValue(bool value) override
		{
			this->Node.append_attribute("value") = value;
		}

		void SetValue(char value) override
		{
			this->Node.append_attribute("value") = static_cast<int>(value);
		}

		void SetValue(byte value) override
		{
			this->Node.append_attribute("value") = static_cast<unsigned int>(value);
		}

		void SetValue(int16 value) override
		{
			this->Node.append_attribute("value") = static_cast<int>(value);
		}

		void SetValue(uint16 value) override
		{
			this->Node.append_attribute("value") = static_cast<unsigned int>(value);
		}

		void SetValue(int32 value) override
		{
			this->Node.append_attribute("value") = value;
		}

		void SetValue(uint32 value) override
		{
			this->Node.append_attribute("value") = value;
		}

		void SetValue(int64 value) override
		{
			this->Node.append_attribute("value") = ToString(value).Cstr();
		}

		void SetValue(uint64 value) override
		{
			this->Node.append_attribute("value") = ToString(value).Cstr();
		}

		void SetValue(float value) override
		{
			this->Node.append_attribute("value") = value;
		}

		void SetValue(double value) override
		{
			this->Node.append_attribute("value") = value;
		}

		void SetValue(long double value) override
		{
			this->Node.append_attribute("value") = ToString(value).Cstr();
		}

		void SetValue(const char* value) override
		{
			this->Node.append_attribute("value") = value;
		}

		void SetValue(const void* value) override
		{
			this->Node.append_attribute("ref") = ToString(reinterpret_cast<ArchiveRefID>(value)).Cstr();
		}

		void SetValue(std::nullptr_t) override
		{
			this->Node.append_attribute("ref") = "null";
		}

		void AddChild(const String& name, FunctionView<void, ArchiveWriter&> function) override
		{
			XMLNode child(*this->Archive, this->Node.append_child(name.Cstr()));
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

BUILD_REFLECTION(Willow::XMLArchive);

namespace Willow
{
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
		XMLNode root(*this, _doc->Doc.append_child("root"));
		handler(root);
	}

	void XMLArchive::GetRoot(FunctionView<void, const ArchiveReader&> handler) const
	{
		XMLNode root(*this, _doc->Doc.first_child());
		handler(root);
	}
}
