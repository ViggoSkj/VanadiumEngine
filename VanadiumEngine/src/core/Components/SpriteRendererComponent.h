#pragma once
#include "ECS.h"
#include "Rendering.h"

namespace Vanadium
{
	class SpriteRendererComponent : public Component
	{
	public:
		using Component::Component;
		
		void LoadRGBATexture(std::string filePath);

		std::shared_ptr<TextureRGBAAsset> Texture;
	};
}