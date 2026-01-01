#pragma once
#include "pch.h"
#include "Mesh.h"

namespace Vanadium::Detail::Rendering
{
	using Vanadium::Rendering::Mesh;
	using Vanadium::Rendering::MeshData;
	using Vanadium::Rendering::MeshHandle;

	struct MeshSlot
	{
		std::optional<Mesh> mesh;
		u32 generation = 0;
		bool alive = false;
	};

	class MeshStore
	{
	public:
		MeshHandle CreateMesh(MeshData data);
		MeshHandle CreateMesh(Mesh mesh);

		Mesh* GetMesh(MeshHandle handle);
		void RemoveMesh(MeshHandle handle);

		bool IsValid(MeshHandle handle);
	private:

		std::vector<MeshSlot> m_slots;
		std::vector<size_t> m_freeSlots;
	};
}