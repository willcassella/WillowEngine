// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>
#include <Core/Math/Vec4.h>

class TestArchNode : public ArchiveNode
{
	///////////////////////
	///   Information   ///
public:

	EXTENDS(ArchiveNode)

	////////////////////////
	///   Constructors   ///
public:

	TestArchNode(String name)
		: _name(std::move(name))
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	String GetName() const override
	{
		return _name;
	}

	bool IsValueNode() const override
	{
		return _value.IsEmpty();
	}

	TestArchNode* AddChild(const String& name) override
	{
		assert(_value.IsEmpty()); // Tree nodes may not have values
		auto child = New<TestArchNode>(std::move(name));
		auto pChild = child.Get(); // Save this reference to return
		_children.Add(child.Transfer());

		return pChild;
	}

	Array<const ArchiveNode*> GetChildren() const override
	{
		Array<const ArchiveNode*> result(_children.Size());

		for (const auto& node : _children)
		{
			result.Add(node.Get());
		}

		return result;
	}

	void SetValue(const String& value) override
	{
		assert(_children.IsEmpty()); // Value nodes may not have children
		_value = std::move(value);
	}

	String GetValue() const override
	{
		return _value;
	}

	////////////////
	///   Data   ///
private:

	String _name;
	String _value;
	Array<UniquePtr<TestArchNode>> _children;
};

int main()
{
	Vec3 test(1, 2, 3);

	auto y = test.GetType().FindData("Y")->Get(Variant{ test }).ToString();
	Console::Prompt(y);
}
