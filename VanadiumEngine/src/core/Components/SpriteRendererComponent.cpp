
#include "pch.h"
#include "SpriteRendererComponent.h"

namespace Vanadium
{
	void SpriteRendererComponent::LoadRGBATexture(std::string filePath)
	{
		Texture = Application::Get().GetAssetManager()->GetFileAsset<TextureRGBAAsset>(filePath);
	}
}