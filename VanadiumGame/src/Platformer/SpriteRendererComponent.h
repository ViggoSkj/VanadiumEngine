#pragma once
#include "Component.h"
#include "Rendering.h"

class SpriteRendererComponent : public Component
{
public:
	AssetRef TextureRef;
};