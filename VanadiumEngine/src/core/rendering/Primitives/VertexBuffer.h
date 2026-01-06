#pragma once
#include "core/Rendering/GLCommon.h"

namespace Vanadium
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(VertexBuffer&) = delete;
		VertexBuffer(VertexBuffer&& other) noexcept
			: m_bufferSize(other.m_bufferSize), m_vertexBufferId(other.m_vertexBufferId) {
			other.m_vertexBufferId = 0;
			other.m_bufferSize = 0;
		};
		~VertexBuffer();

		VertexBuffer& operator=(VertexBuffer&& other) noexcept
		{
			if (this != &other)
			{
				this->m_vertexBufferId = other.m_vertexBufferId;
				this->m_bufferSize = other.m_bufferSize;
				other.m_vertexBufferId = 0;
				other.m_bufferSize = 0;
			}
			return *this;
		}

		u32 Id() const { return m_vertexBufferId; }

		void Bind();
		void UnBind();

		void SetVertecies(const void* data, int size, GLenum usage = GL_STATIC_DRAW);
		template<typename T>
		void SetVertecies(const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW);
		
		void UpdateVertecies(const void* data, int size, int offset = 0);
		template<typename T>
		void UpdateVertecies(const std::vector<T>& data, i32 offset, GLenum usage = GL_STATIC_DRAW);

	private:
		unsigned int m_vertexBufferId = 0;
		u32 m_bufferSize = 0;
	};

	template<typename T>
	inline void VertexBuffer::SetVertecies(const std::vector<T>& data, GLenum usage)
	{
		SetVertecies(data.data(), data.size() * sizeof(T), usage);
	}

	template<typename T>
	inline void VertexBuffer::UpdateVertecies(const std::vector<T>& data, i32 offset, GLenum usage)
	{
		UpdateVertecies(data.data(), data.size() * sizeof(T), offset, usage);
	}
}