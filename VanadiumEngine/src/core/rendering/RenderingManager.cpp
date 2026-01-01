#include "pch.h"
#include "RenderingManager.h"

namespace Vanadium::Detail::Rendering
{
	RenderingManager::RenderingManager()
	{
	}

	UniformBindingVoucher RenderingManager::ClaimBindingSlot()
	{
		return m_uniformBinder.ClaimBindingSlot();
	}

	UniformObject* RenderingManager::CreateUniformObject(UniformObjectDescriptor descriptor)
	{
		m_uniformObjects.emplace_back(descriptor);
		return &m_uniformObjects.back();
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
}