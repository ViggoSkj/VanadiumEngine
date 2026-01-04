#include "pch.h"
#include "TextureStore.h"

namespace Vanadium
{
	RenderTextureHandle TextureStore::Create(const TextureRGBA& texture)
	{
		RenderTextureHandle h = m_renderTextures.Create();
		RenderTexture& tex = *m_renderTextures.Get(h);

		texture.Copy(tex.textureData);
		tex.glTexture.AssignTexture(tex.textureData);

		return h;
	}

	RenderTexture* Vanadium::TextureStore::Get(RenderTextureHandle handle)
	{
		return m_renderTextures.Get(handle);
	}
}