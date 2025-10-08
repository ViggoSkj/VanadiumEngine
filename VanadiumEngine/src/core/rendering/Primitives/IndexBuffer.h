#pragma once

class IndexBuffer
{
public:
	IndexBuffer();
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	void SetData(const unsigned int* data, unsigned int count);
	inline unsigned int GetCount() const { return m_count; }
private:
	unsigned int m_id;
	unsigned int m_count;	
};