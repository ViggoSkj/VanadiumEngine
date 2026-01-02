#pragma once
#include <memory>
#include "Shaders/ShaderUniform.h"
#include "Shaders/ShaderType.h"
#include "Shaders/UniformBinder.h"
#include "Shaders/Shader.h"
#include "Mesh/MeshStore.h"
#include "core/Util/UnorderdVector.h"
#include "core/HandleStore.h"

namespace Vanadium::Detail::Rendering
{
	class RenderingManager
	{
	public:
		RenderingManager();
		RenderingManager(const RenderingManager&) = delete;

		UniformBindingVoucher ClaimBindingSlot();

		Handle<UniformObject> CreateUniformObject(UniformObjectDescriptor& descriptor);
		UniformObject* GetUniformObject(Handle<UniformObject> handle);
		UniformObject* FindUniformObject(std::string name);

		void UpdateRenderSurfaceUBO();

		MeshStore meshStore;
	private:
		void InitializeDefaultUniformObjects();

		UniformBinder m_uniformBinder;
		HandleStore<UniformObject> m_uniformObjects;
	};
}