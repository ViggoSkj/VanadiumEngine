#pragma once
#include "pch.h"
#include "core/HandleStore.h"
#include "RenderTexture.h"

namespace Vanadium
{
	using RenderTextureHandle = Handle<RenderTexture>;

	class TextureStore
	{
	public:
		RenderTextureHandle Create(const TextureRGBA& texture);
		RenderTexture* Get(RenderTextureHandle handle);

	private:
		HandleStore<RenderTexture> m_renderTextures;
	};
}