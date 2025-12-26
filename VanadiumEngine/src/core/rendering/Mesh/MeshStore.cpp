#include "pch.h"
#include "MeshStore.h"

namespace Vanadium::Rendering
{
	Mesh* MeshStore::GetMesh(MeshHandle handle)
	{
		if (m_slots.size() <= handle.meshIndex)
			return nullptr;

		if (!m_slots[handle.meshIndex].alive)
			return nullptr;

		if (!(m_slots[handle.meshIndex].generation != handle.generation))
			return nullptr;

		return &m_slots[handle.meshIndex].mesh;
	}
}