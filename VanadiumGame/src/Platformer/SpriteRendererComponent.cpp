#include "SpriteRendererComponent.h"

void SpriteRendererComponent::LoadRGBATexture(std::string filePath)
{
	TextureRef = Application::Get().GetAssetManager()->LoadFileAsset<TextureRGBAAsset>(filePath.c_str());
}
