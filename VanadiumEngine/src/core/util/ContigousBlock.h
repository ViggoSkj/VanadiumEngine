#pragma once
#include "UnorderdVector.h"

template <typename T>
struct BlockEntry
{
	unsigned int Id;
	T Data;
};

template <typename T>
class ContigousBlock
{
public:
	ContigousBlock() = default;
	ContigousBlock(size_t initialSize);

	unsigned int Add(T entry);

private:
	UnorderedVector<BlockEntry<T>> m_entries;
	UnorderedVector<std::pair<unsigned int, unsigned int>> m_IdToIndex;
};

template<typename T>
inline ContigousBlock<T>::ContigousBlock(size_t initialSize)
	: m_entries(initialSize)
{

}

template<typename T>
inline unsigned int ContigousBlock<T>::Add(T entry)
{
	m_entries.PushBack(m_entries);
}