#include "pch.h"
#include "RenderingManager.h"
#include "core/Application.h"
#include "core/AssetManager/AssetTypes/Shader/ShaderAsset.h"

namespace Vanadium::Detail::Rendering
{
	RenderingManager::RenderingManager()
	{
		InitializeDefaultUniformObjects();
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

	UniformObject* RenderingManager::FindUniformObject(std::string name)
	{
		for (UniformObject& object : m_uniformObjects)
		{
			if (object.GetName() == name)
			{
				return &object;
			}
		}
		return nullptr;
	}

	void Rendering::RenderingManager::UpdateRenderSurfaceUBO()
	{
		Window& window = *Application::Get().GetWindow();
		glm::mat4 proj = window.GetOrthographicProjection();
		UniformObject& m_matrices = *FindUniformObject("RenderSurface");
		m_matrices.Buffer.SetData(glm::value_ptr(proj), 0, 4 * 4 * 4);
	}

	void RenderingManager::InitializeDefaultUniformObjects()
	{
		std::string definitions[] = {
			"res/shaders/ubos/renderSurface.shader",
			"res/shaders/ubos/camera.shader"
		};

		AssetManager& man = *Application::Get().GetAssetManager();

		for (std::string_view path : definitions)
		{
			std::vector<UniformObjectDescriptor> descs = man.GetFileAsset<ShaderCodeAsset>(path)->GetUniformObjectDescriptors();
			for (auto& desc : descs)
			{
				auto handle = m_uniformObjects.Create(desc);
				UniformBindingVoucher voucher = ClaimBindingSlot();
				UniformObject* o = GetUniformObject(handle);
				o->Bind(std::move(voucher));
			}
		}
	}
}