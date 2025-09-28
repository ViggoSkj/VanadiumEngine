#pragma once
#include "Application.h"
#include "Rendering.h"
#include <unordered_map>

class SpriteRendererLayer : public ApplicationLayer
{
public:
	SpriteRendererLayer();

	void OnRender(double dt) override;


private:
	GLTexture& GetTexture(AssetRef textureRef);

	VertexArray m_VAO;
	UniformObject m_matrices;
	Shader m_textureShader;
	std::unordered_map<AssetRef, GLTexture, AssetRefHash> m_readyTexture;
};