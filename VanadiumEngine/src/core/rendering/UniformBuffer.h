#pragma once

class UniformBuffer
{
public:
	UniformBuffer();
	~UniformBuffer();

	void Bind();
	void UnBind();

	void SetData(void* data, unsigned int offset, unsigned int size);

	void SetBindingPoint(unsigned int bindingPoint);
private:
	unsigned int m_id;
};