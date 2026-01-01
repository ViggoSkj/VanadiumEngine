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

	Handle<UniformObject>RenderingManager::CreateUniformObject(UniformObjectDescriptor& descriptor)
	{
		return m_uniformObjects.Create(descriptor);
	}

	UniformObject* RenderingManager::GetUniformObject(Handle<UniformObject> handle)
	{
		return m_uniformObjects.Get(handle);
	}

	std::optional<UniformObject*> RenderingManager::FindUniformObject(std::string name)
	{
		for (UniformObject& object : m_uniformObjects)
		{
			if (object.GetName() == name)
			{
				return &object;
			}
		}
		return std::nullopt;
	}
}