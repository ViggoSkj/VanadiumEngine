#pragma once
#include <memory>
#include "Shaders/ShaderUniform.h"
#include "Shaders/ShaderType.h"
#include "Shaders/UniformBinder.h"
#include "Shaders/Shader.h"
#include "Mesh/MeshStore.h"
#include "core/Util/UnorderdVector.h"

namespace Vanadium::Detail::Rendering
{
	class RenderingManager
	{
	public:
		RenderingManager();
		RenderingManager(const RenderingManager&) = delete;

		UniformBindingVoucher ClaimBindingSlot();

		UniformObject* CreateUniformObject(UniformObjectDescriptor descriptor);
		std::optional<UniformObject*> FindUniformObject(std::string name);

		MeshStore meshStore;
	private:
		UniformBinder m_uniformBinder;
		std::vector<UniformObject> m_uniformObjects;
	};
}