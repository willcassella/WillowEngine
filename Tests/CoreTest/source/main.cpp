// main.cpp - Copyright 2013-2015 Will Cassella, All Rights Reserved

#include <Core/Core.h>
#include <Core/Math/Vec4.h>

class TestArchNode : public ArchNode
{
	///////////////////////
	///   Information   ///
public:

	EXTENDS(ArchNode)

	////////////////////////
	///   Constructors   ///
public:

	TestArchNode(String name)
		: Base(std::move(name))
	{
		// All done
	}

	///////////////////
	///   Methods   ///
public:

	TestArchNode& AddNode(String name) override
	{
		assert(_value.IsEmpty()); // Tree nodes may not have values
		auto child = New<TestArchNode>(std::move(name));
		auto& rChild = *child; // Save this reference to return
		_children.Add(child.Transfer());

		return rChild;
	}

	Array<const ArchNode*> GetSubNodes() const override
	{
		Array<const ArchNode*> result(_children.Size());

		for (const auto& node : _children)
		{
			result.Add(node.Get());
		}

		return result;
	}

	void SetValue(String value) override
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

	String _value;
	Array<UniquePtr<TestArchNode>> _children;
};

int main()
{
	Vec3 vec{ 1, 2, 3 };

	TestArchNode test("Test");

	ToArchive(vec, test);

	Console::Prompt();
}
