#pragma once
#include "core/CoreTypes.h"
#include <vector>
#include <cassert>
#include <algorithm>

template<typename T>
class Array2D
{
public:
    Array2D() = default;
    Array2D(unsigned int width, unsigned int height);
    Array2D(const T* data, unsigned int width, unsigned int height);

    void Copy(Array2D<T>& destination) const;

    T Get(int x, int y) const
    {
        assert(x >= 0 && y >= 0);
        assert(x < (int)m_width && y < (int)m_height);
        return m_data[x + y * m_width];
    }

    void Set(int x, int y, const T& value)
    {
        assert(x >= 0 && y >= 0);
        assert(x < (int)m_width && y < (int)m_height);
        m_data[x + y * m_width] = value;
    }

    void SetResize(int x, int y, const T& value)
    {
        if (x >= (int)m_width || y >= (int)m_height)
        {
            Resize(
                std::max(m_width, (u32)(x + 1)),
                std::max(m_height, (u32)(y + 1))
            );
        }
        Set(x, y, value);
    }

    T* Data() { return m_data.data(); }
    const T* Data() const { return m_data.data(); }

    u32 GetWidth() const { return m_width; }
    u32 GetHeight() const { return m_height; }
    u32 Count() const { return m_width * m_height; }

    void Resize(unsigned int width, unsigned int height);

private:
    std::vector<T> m_data;
    u32 m_width = 0;
    u32 m_height = 0;
};

template<typename T>
Array2D<T>::Array2D(unsigned int width, unsigned int height)
{
    Resize(width, height);
}

template<typename T>
Array2D<T>::Array2D(const T* data, unsigned int width, unsigned int height)
    : m_width(width), m_height(height), m_data(width* height)
{
    std::copy(data, data + m_data.size(), m_data.begin());
}

template<typename T>
void Array2D<T>::Copy(Array2D<T>& destination) const
{
    destination.m_width = m_width;
    destination.m_height = m_height;
    destination.m_data = m_data;
}

template<typename T>
void Array2D<T>::Resize(unsigned int width, unsigned int height)
{
    if (width == m_width && height == m_height)
        return;

    std::vector<T> newData(width * height);

    unsigned int copyWidth = std::min(m_width, width);
    unsigned int copyHeight = std::min(m_height, height);

    for (unsigned int y = 0; y < copyHeight; ++y)
    {
        std::copy(
            m_data.begin() + y * m_width,
            m_data.begin() + y * m_width + copyWidth,
            newData.begin() + y * width
        );
    }

    m_data = std::move(newData);
    m_width = width;
    m_height = height;
}
