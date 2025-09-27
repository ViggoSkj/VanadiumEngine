#pragma once
#include <vector>

template <typename T>
class UnorderedVector
{
public:
	UnorderedVector() = default;
	UnorderedVector(size_t initalSize);

	size_t Size() {
		return m_vector.size();
	}

	void PushBack(T entry);
	void Set(size_t index, T entry);
	void Remove(size_t index);

	T Last()
	{
		return m_vector.back();
	};

	T Get(size_t index);

	void Swap(size_t a, size_t b);

private:
	std::vector<T> m_vector;
};

template<typename T>
inline UnorderedVector<T>::UnorderedVector(size_t initalSize)
	: m_vector(initalSize)
{

}

template<typename T>
inline void UnorderedVector<T>::PushBack(T entry)
{
	m_vector.push_back(entry);
}

template<typename T>
inline void UnorderedVector<T>::Remove(size_t index)
{
	m_vector[index] = std::move(m_vector.back());
	m_vector.pop_back();
}

template<typename T>
inline T UnorderedVector<T>::Get(size_t index)
{
	return m_vector[index];
}

template<typename T>
inline void UnorderedVector<T>::Set(size_t index, T entry)
{
	m_vector[index] = entry;
}


template<typename T>
inline void UnorderedVector<T>::Swap(size_t a, size_t b)
{
	std::swap(m_vector[a], m_vector[b]);
}
