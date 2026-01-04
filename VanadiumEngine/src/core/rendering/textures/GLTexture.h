#pragma once
#include "core/AssetManager/AssetTypes/Texture/Texture.h"
#include "core/Rendering/textures/TextureConfiguration.h"

namespace Vanadium
{
	class GLTexture
	{
	public:
		GLTexture();
		GLTexture(const GLTexture&) = delete;
		~GLTexture();

		GLTexture(GLTexture&& other) noexcept
			: m_id(other.m_id), Config(other.Config)
		{
			other.m_id = 0;
		}

		GLTexture& operator=(GLTexture&& other) noexcept
		{
			if (&other == this)
				return *this;

			m_id = other.m_id;
			Config = other.Config;

			other.m_id = 0;

			return *this;
		}

		void AssignTexture(const Texture& texture);

		void Bind();
		void UnBind();

		void Use();

		TextureConfiguration Config;
	private:
		unsigned int m_id = 0;
	};
}