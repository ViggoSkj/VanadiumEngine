#pragma once
#include "ECS.h"
#include "Rendering.h"

namespace Vanadium
{
	class SpriteRendererComponent : public Component
	{
	public:
		void LoadRGBATexture(std::string filePath);

		std::shared_ptr<TextureRGBAAsset> Texture;
	};
}