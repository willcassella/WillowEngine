// TLinkedBuffer.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <bitset>
#include "../../Containers/Array.h"

template <typename T, std::size_t NodeSize = 64>
struct TLinkedBuffer final
{
	/////////////////////
	///   Constants   ///
private:

	/** Function used to allocate memory for each node. */
	static constexpr auto AllocFunc = std::malloc;

	/** Function used to deallocated memory for each node. */
	static constexpr auto FreeFunc = std::free;

	/////////////////
	///   Types   ///
private:

	struct Node final
	{
		std::bitset<NodeSize> Mask;
		T* Values;
	};

	////////////////////////
	///   Constructors   ///
public:

	TLinkedBuffer() = default;
	TLinkedBuffer(const TLinkedBuffer& copy) = delete; // TODO
	TLinkedBuffer(TLinkedBuffer&& move) = default;
	~TLinkedBuffer()
	{
		// For each node in this buffer
		for (const auto node : _nodes)
		{
			// Destroy the value in each node
			for (std::size_t i = 0; i < NodeSize; ++i)
			{
				if (node.Mask.test(i))
				{
					(node.Values + i)->~T();
				}
			}

			// Free the node's buffer
			FreeFunc(node.Values);
		}
	}

	///////////////////
	///   Methods   ///
public:

	/** Creates a new instante of 'F' with the given arguments.
	* NOTE: This buffer will destroy the returned value automatically when it itself is destroyed.
	* If you want to destroy a value before the buffer is destroyed, use the 'Destroy' member function. 
	* NOTE: You may use this to construct derived classes of 'T', but they must have the same size and alignment. */
	template <typename F = T, typename ... Args>
	F* New(Args&& ... args)
	{
		static_assert(std::is_base_of<T, F>::value, "The given type to construct does not extend the buffer 'T' type.");
		static_assert(sizeof(F) == sizeof(T) && alignof(F&) == alignof(T&), "The given type to construct does not fit in this TLinkedBuffer.");

		// Check all existing nodes
		for (auto& node : _nodes)
		{
			const auto mask = node.Mask;

			// See if there are any free slots in this node
			if (mask.all())
			{
				// No free slots, continue
				continue;
			}

			// Find the first free slot in the node
			for (std::size_t i = 0; i < NodeSize; ++i)
			{
				if (!mask.test(i))
				{
					// Emplace the object
					node.Mask.set(i, true);
					return new (node.Values + i) F{ std::forward<Args>(args)... };
				}
			}
		}

		// No free slots in existing nodes, create a new one
		Node node;
		node.Values = static_cast<T*>(AllocFunc(sizeof(T) * NodeSize));

		// Emplace the object
		node.Mask.set(0, true);
		auto value = new (node.Values) F{ std::forward<Args>(args)... };

		// Add the node to the list of nodes
		_nodes.Add(std::move(node));

		return value;
	}

	/** Destroys the given value.
	* NOTE: If the value does not exist in this buffer, this does nothing. */
	void Destroy(T* value)
	{
		// Find the node that this value belongs to
		for (auto& node : _nodes)
		{
			// If the given pointer is within the range of owned values
			if (value >= node.Values && value < node.Values + NodeSize)
			{
				// Calculate the index of the pointer within the node, and set the mask bit
				const auto index = (value - node.Values) / sizeof(T);
				node.Mask.set(index, false);

				// Destroy the value
				value->~T();
				return;
			}
		}
	}

	/** Enumerates over all the values in this Buffer. */
	template <typename F>
	void enumerate(F& func)
	{
		for (const auto node : _nodes)
		{
			for (std::size_t i = 0; i < NodeSize; ++i)
			{
				if (node.Mask.test(i))
				{
					func(node.Values[i]);
				}
			}
		}
	}

	/** Enumerates over all the values in this Buffer. */
	template <typename F>
	void enumerate(F& func) const
	{
		for (const auto node : _nodes)
		{
			for (std::size_t i = 0; i < NodeSize; ++i)
			{
				if (node.Mask.test(i))
				{
					func(node.Values[i]);
				}
			}
		}
	}

	/////////////////////
	///   Operators   ///
public:

	TLinkedBuffer& operator=(const TLinkedBuffer& copy) = delete; // TODO
	TLinkedBuffer& operator=(TLinkedBuffer&& move) = delete; // TODO

	////////////////
	///   Data   ///
private:

	Array<Node> _nodes;
};
