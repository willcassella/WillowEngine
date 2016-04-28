// LinkedBuffer.h - Copyright 2013-2016 Will Cassella, All Rights Reserved
#pragma once

#include <bitset>
#include <cstdlib>
#include "../../Containers/Array.h"

/** Stores several contigous arrays of untyped elements.
* Pointers to elements are persistent. */
struct LinkedBuffer final
{
	/////////////////////
	///   Constants   ///
private:

	static constexpr std::size_t Node_Size = 64;

	/////////////////
	///   Types   ///
private:

	struct Node final
	{
		std::bitset<Node_Size> mask;
		byte* values;
	};

	////////////////////////
	///   Constructors   ///
public:

	LinkedBuffer(std::size_t elemSize)
		: _elem_size{ elemSize }
	{
		// All done
	}
	LinkedBuffer(const LinkedBuffer& copy) = delete;
	LinkedBuffer(LinkedBuffer&& move)
		: _elem_size{ move._elem_size }, _nodes(std::move(move._nodes))
	{
		// All done
	}
	~LinkedBuffer()
	{
		for (auto node : _nodes)
		{
			std::free(node.values);
		}
	}

	///////////////////
	///   Methods   ///
public:

	/** Returns the size of each element. */
	std::size_t get_elem_size() const
	{
		return this->_elem_size;
	}

	/** Returns a pointer to an empty slot in this LinkedBuffer.
	* NOTE: The returned pointer only meets the size requirements this LinkedBuffer was initialized with. */
	byte* get_empty_slot()
	{
		// Check all existing nodes
		for (auto& node : _nodes)
		{
			// See if there are any free slots in this node
			if (node.mask.all())
			{
				// No free slots, continue
				continue;
			}

			// Find the first free slot in the node
			for (std::size_t i = 0; i < Node_Size; ++i)
			{
				if (!node.mask.test(i))
				{
					// Mark the slot as used
					node.mask.set(i, true);
					return node.values + i * _elem_size;
				}
			}
		}

		// No free slots in existing nodes, create a new one
		Node node;
		node.values = static_cast<byte*>(std::calloc(Node_Size, _elem_size));

		// Mark the slot as used and add the node to this LinkedBuffer
		node.mask.set(0, true);

		// Add the node to the list of nodes
		_nodes.Add(node);

		return node.values;
	}

	/** Sets the given slot as being empty, so it may be reused.
	* NOTE: If the given slot does not belong to this LinkedBuffer, this does nothing.
	* NOTE: You should call the destructor for whatever this slot contained before doing this. */
	void set_slot_empty(byte* slot)
	{
		// Find the node that this value belongs to
		for (auto& node : _nodes)
		{
			// If the given pointer is within the range of owned values
			if (slot >= node.values && slot < node.values + Node_Size * _elem_size)
			{
				// Calculate the index of the pointer within the node
				const auto index = (slot - node.values) / _elem_size;

				// Mark the slot as empty
				node.mask.set(index, false);
				return;
			}
		}
	}

	/** Enumerates all slots that are in use. */
	template <typename F>
	void enumerate_unempty(F func)
	{
		for (auto node : _nodes)
		{
			for (std::size_t i = 0; i < Node_Size; ++i)
			{
				if (node.mask.test(i))
				{
					func(node.values + i * _elem_size);
				}
			}
		}
	}

	/** Enumerates all slots that are in use. */
	template <typename F>
	void enumerate_unempty(F func) const
	{
		for (auto node : _nodes)
		{
			for (std::size_t i = 0; i < Node_Size; ++i)
			{
				if (node.mask.test(i))
				{
					func(static_cast<const byte*>(node.values) + i * _elem_size);
				}
			}
		}
	}

	/////////////////////
	///   Operators   ///
public:

	LinkedBuffer& operator=(const LinkedBuffer& copy) = delete;
	LinkedBuffer& operator=(LinkedBuffer&& move) = delete;

	////////////////
	///   Data   ///
private:

	const std::size_t _elem_size;
	Array<Node> _nodes;
};
