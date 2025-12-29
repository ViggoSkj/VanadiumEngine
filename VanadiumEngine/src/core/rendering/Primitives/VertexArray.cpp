#include "pch.h"
#include "VertexArray.h"
#include "core/Rendering/GLCommon.h"
#include "core/Debug/Log.h"

namespace Vanadium
{
	GLVertexAttribute::GLVertexAttribute(GLenum type, u32 count, GLenum normalized)
		: type(type), count(count), normalized(normalized)
	{

	}

	u32 GLVertexAttribute::Size()
	{
		switch (type)
		{
		case GL_BYTE:
		case GL_UNSIGNED_BYTE:
			return sizeof(GLubyte) * count;
		case GL_SHORT:
		case GL_UNSIGNED_SHORT:
			return sizeof(GLushort) * count;
		case GL_INT:
		case GL_UNSIGNED_INT:
			return sizeof(GLuint) * count;
		case GL_FLOAT:
			return sizeof(GLfloat) * count;
		default:
			throw std::runtime_error("GLVertexAttribute type not implemented");
		}
	}

	VertexArray::VertexArray()
	{
		GL_CHECK(glCreateVertexArrays(1, &m_vertexArrayId));
		m_vertexAttributeCount = 0;
	}

	VertexArray::~VertexArray()
	{
		//LogDebug("Deleted vertex array with id " + std::to_string(m_vertexArrayId));
		GL_CHECK(glDeleteVertexArrays(1, &m_vertexArrayId));
	}

	void VertexArray::Bind()
	{
		GL_CHECK(glBindVertexArray(m_vertexArrayId));
	}

	void VertexArray::UnBind()
	{
		GL_CHECK(glBindVertexArray(0));
	}

	void VertexArray::BindIndexBuffer(IndexBuffer& indexBuffer)
	{
		GL_CHECK(glVertexArrayElementBuffer(m_vertexArrayId, indexBuffer.Id()));
	}

	u32 VertexArray::AddVertexAttributes(std::vector<GLVertexAttribute> attributes, u32 bindingIndex, u32 divisor)
	{
		u32 offset = 0;
		for (u32 i = 0; i < attributes.size(); i++)
		{
			GLVertexAttribute attribute = attributes[i];
			GL_CHECK(glVertexArrayAttribFormat(m_vertexArrayId, m_vertexAttributeCount, attribute.count, attribute.type, attribute.normalized, offset));
			GL_CHECK(glVertexArrayAttribBinding(m_vertexArrayId, m_vertexAttributeCount, bindingIndex));
			GL_CHECK(glEnableVertexArrayAttrib(m_vertexArrayId, m_vertexAttributeCount));
			m_vertexAttributeCount++;
			offset += attribute.Size();
		}

		if (divisor != 0)
			GL_CHECK(glVertexArrayBindingDivisor(m_vertexArrayId, bindingIndex, divisor));

		return offset; // stride
	}

	void VertexArray::BindVertexBuffer(u32 bindingIndex, VertexBuffer& vertexBuffer, u32 offset, u32 stride)
	{
		GL_CHECK(glVertexArrayVertexBuffer(m_vertexArrayId, bindingIndex, vertexBuffer.Id(), offset, stride));
	}

	void VertexArray::AddVertexBuffer(std::vector<GLVertexAttribute> attributes, VertexBuffer& vertexBuffer, u32 bindingIndex, u32 divisor)
	{
		u32 stride = AddVertexAttributes(attributes, bindingIndex, divisor);
		BindVertexBuffer(bindingIndex, vertexBuffer, 0, stride);
	}
}