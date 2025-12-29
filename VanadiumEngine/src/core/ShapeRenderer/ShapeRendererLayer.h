#pragma once
#include "core/ApplicationLayer.h"
#include "core/Rendering/Shaders/Shader.h"

namespace Vanadium
{
	class ShapeRendererLayer : public ApplicationLayer
	{
	public:
		ShapeRendererLayer();

		void OnRender(double dt) override;

	private:

		Shader m_squareShader;
		Shader m_arrowShader;
		Shader m_cirlceShader;
	};
}