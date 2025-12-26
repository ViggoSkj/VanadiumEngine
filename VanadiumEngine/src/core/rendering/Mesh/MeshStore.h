#pragma once
#include "pch.h"
#include "Mesh.h"

namespace Vanadium::Rendering
{
	struct MeshSlot
	{
		Mesh mesh;
		u32 generation;
		bool alive;
	};

	class MeshStore
	{
	public:
		Mesh* GetMesh(MeshHandle handle);

	private:
		std::vector<MeshSlot> m_slots;
	};
}