#pragma once
#include <memory>

template<typename T>
class Array2D
{
public:
	Array2D();
	Array2D(T* data, unsigned int width, unsigned int height);
	Array2D(unsigned int width, unsigned int height);

	T Get(int x, int y)
	{
		return m_data[x + y * m_width];
	}

	void Set(int x, int y, T value)
	{
		m_data[x + y * m_width] = value;
	}

	T* Data()
	{
		return m_data;
	}

	unsigned int GetWidth() { return m_width; }
	unsigned int GetHeight() { return m_height; }

	void Resize(unsigned int width, unsigned int height);

private:
	T* m_data;
	unsigned int m_width;
	unsigned int m_height;
};

template<typename T>
inline Array2D<T>::Array2D()
{
}

template<typename T>
inline Array2D<T>::Array2D(T* data, unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;
	m_data = data;
}

template<typename T>
inline Array2D<T>::Array2D(unsigned int width, unsigned int height)
{
	Resize(width, height);
}

template<typename T>
inline void Array2D<T>::Resize(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;
	m_data = (T*) calloc(width * height, sizeof(width));
}
