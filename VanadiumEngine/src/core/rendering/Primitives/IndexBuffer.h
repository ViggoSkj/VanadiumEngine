#pragma once

class IndexBuffer
{
public:
	IndexBuffer();
	IndexBuffer(IndexBuffer&) = delete;
	IndexBuffer(IndexBuffer&& other) noexcept
		: m_id(other.m_id), m_count(other.m_count)
	{
		other.m_id = 0;
		other.m_count = 0;
	}
	~IndexBuffer();

	IndexBuffer& operator=(IndexBuffer&& other) noexcept
	{
		if (this != &other)
		{
			this->m_id = other.m_id;
			this->m_count = other.m_count;
			other.m_id = 0;
			other.m_count = 0;
		}
		return *this;
	}

	void Bind() const;
	void UnBind() const;

	u32 Id() const { return m_id; }

	void SetData(const unsigned int* data, unsigned int count);
	inline unsigned int GetCount() const { return m_count; }
private:
	unsigned int m_id;
	unsigned int m_count;
};