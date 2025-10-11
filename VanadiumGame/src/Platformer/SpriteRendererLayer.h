#pragma once
#include "Application.h"
#include "Rendering.h"
#include <unordered_map>

class SpriteRendererLayer : public ApplicationLayer
{
public:
	SpriteRendererLayer();

	void OnUpdate(double dt) override;
	void OnRender(double dt) override;


private:
	GLTexture& GetTexture(std::shared_ptr<TextureRGBAAsset> texture);

	VertexArray m_VAO;
	UniformObject m_matrices;
	Shader m_textureShader;
	std::unordered_map<std::shared_ptr<TextureRGBAAsset>, GLTexture> m_readyTexture;
};