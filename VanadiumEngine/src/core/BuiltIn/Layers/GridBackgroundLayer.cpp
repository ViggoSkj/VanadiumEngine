#include "GridBackgroundLayer.h"
#include "GLCommon.h"

GridBackgroundLayer::GridBackgroundLayer()
	: m_shader(Application::Get().GetAssetManager()->LoadAndGetFileAsset<ShaderAsset>("res/background.shader").ShaderProgram),
	m_vao(Util::Square())
{

}

void GridBackgroundLayer::OnRender(double dt)
{
	m_vao.Bind();
	m_shader.GlShader().Use();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
