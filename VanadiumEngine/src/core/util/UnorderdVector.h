#pragma once


template <typename T>
class UnorderedVector : public std::vector<T>
{
public:
	void remove(size_t index);
};

template<typename T>
inline void UnorderedVector<T>::remove(size_t index)
{
	if (this->size() > 1)
	{
		(*this)[index] = std::move(this->back());
	}
	this->pop_back();
}
