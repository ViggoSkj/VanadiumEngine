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

	void SetResize(int x, int y, T value)
	{
		if (x >= m_width && y >= m_height)
			Resize(x + 1, y + 1);
		else if (x >= m_width)
			Resize(x + 1, m_height);
		else if (y >= m_height)
			Resize(m_width, y);

		Set(x, y, value);
	}

	T* Data()
	{
		return m_data;
	}

	unsigned int GetWidth() { return m_width; }
	unsigned int GetHeight() { return m_height; }

	void Resize(unsigned int width, unsigned int height);

	u32 Count() { return m_width * m_height; }

private:
	T* m_data = nullptr;
	u32 m_width = 0;
	u32 m_height = 0;
};

template<typename T>
inline Array2D<T>::Array2D()
	: m_data(nullptr), m_width(0), m_height(0)
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
	T* newValues = (T*)calloc(width * height, sizeof(width));

	
	if (width * height > 0 && m_height * m_width > 0 && m_data != nullptr)
	{
		// copy rows
		for (int y = 0; y < m_width; y++)
		{
			memcpy(newValues + y * width, m_data + m_width * sizeof(T), m_width * sizeof(T));
		}
	}

	m_data = newValues;

	m_width = width;
	m_height = height;
}
