#include "pch.h"
#include "MeshStore.h"

namespace Vanadium::Detail::Rendering
{
	MeshHandle MeshStore::CreateMesh(MeshData data)
	{
		return CreateMesh(Mesh(data));
	}

	MeshHandle MeshStore::CreateMesh(Mesh mesh)
	{
		size_t index = -1;
		if (m_freeSlots.size() < 1)
		{
			m_slots.emplace_back();
			index = m_slots.size() - 1;
		}
		else
			index = m_freeSlots.back();

		m_slots[index].alive = true;
		m_slots[index].mesh = std::move(mesh);
		m_slots[index].generation++;

		return MeshHandle(index, m_slots[index].generation);
	}

	Mesh* MeshStore::GetMesh(MeshHandle handle)
	{
		if (!IsValid(handle))
			return nullptr;

		return &m_slots[handle.meshIndex].mesh.value();
	}

	void MeshStore::RemoveMesh(MeshHandle handle)
	{
		if (!IsValid(handle))
			return;

		m_slots[handle.meshIndex].alive = false;
		m_slots[handle.meshIndex].mesh = std::nullopt;
		m_slots[handle.meshIndex].generation++;
	}

	bool MeshStore::IsValid(MeshHandle handle)
	{
		if (m_slots.size() <= handle.meshIndex)
			return false;

		if (!m_slots[handle.meshIndex].alive)
			return false;

		if (m_slots[handle.meshIndex].generation != handle.generation)
			return false;

		if (!(m_slots[handle.meshIndex].mesh.has_value()))
			return false;

		return true;
	}
}