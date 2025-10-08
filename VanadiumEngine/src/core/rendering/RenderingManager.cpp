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

UniformObject& RenderingManager::CreateUniformObject(UniformObjectDescriptor descriptor)
{
	m_uniformObjects.emplace_back(descriptor);
	return m_uniformObjects.back();
}

std::optional<UniformObject*> RenderingManager::FindUniformObject(std::string name)
{
	for (int i = 0; i < m_uniformObjects.size(); i++)
	{
		if (m_uniformObjects[i].GetName() == name)
		{
			return &m_uniformObjects[i];
		}
	}

	return std::nullopt;
}
