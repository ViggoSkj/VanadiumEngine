#pragma once
#include "ECS.h"
#include "Rendering.h"

class SpriteRendererComponent : public Component
{
public:
	AssetRef TextureRef;
};