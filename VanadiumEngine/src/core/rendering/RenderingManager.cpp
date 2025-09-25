#include "RenderingManager.h"

RenderingManager::RenderingManager()
	: m_vertexUniformBinder(ShaderType::VertexShader, UniformBinder::BlockCount(GL_MAX_VERTEX_UNIFORM_BLOCKS))
{
}

UniformBindingSlot RenderingManager::LoanUniformBindingSlot(ShaderType shaderType)
{
	switch (shaderType)
	{
	case None:
		break;
	case VertexShader:
		return m_vertexUniformBinder.LoneBindingSlot();
	case FragmentShader:
		break;
	default:
		break;
	}
}

void RenderingManager::ReturnuniformBindingSlot(UniformBindingSlot bindingSlot)
{
	switch (bindingSlot.ShaderType)
	{
	case VertexShader:
		m_vertexUniformBinder.ReturnBindingSlot(bindingSlot);
	}
}
