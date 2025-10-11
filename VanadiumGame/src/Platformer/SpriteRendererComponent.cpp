#include "SpriteRendererComponent.h"

void SpriteRendererComponent::LoadRGBATexture(std::string filePath)
{
	Texture = Application::Get().GetAssetManager()->GetFileAsset<TextureRGBAAsset>(filePath);
}
