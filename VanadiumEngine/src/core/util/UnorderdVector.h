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
		std::swap((*this)[index], (*this)[this->size() - 1]); // uses swap, safe for std::thread
	}
	this->pop_back();
}
