#include "pch.h"
#include "Util.h"
#include "core/API/Rendering.h"

namespace Util
{
	Vanadium::Rendering::MeshData SquareMeshData(float width)
	{
		using namespace Vanadium::Rendering;

		MeshData data;

		data.AddVertex({ -width / 2.0,  width / 2.0, 0.0 }, { 0.0, 0.0 }); // top-left
		data.AddVertex({ width / 2.0,  width / 2.0, 0.0 }, { 1.0, 0.0 }); // top-right
		data.AddVertex({ width / 2.0, -width / 2.0, 0.0 }, { 1.0, 1.0 }); // bottom-right
		data.AddVertex({ -width / 2.0, -width / 2.0, 0.0 }, { 0.0, 1.0 }); // bottom-left

		data.AddIndex(0);
		data.AddIndex(1);
		data.AddIndex(3);

		data.AddIndex(1);
		data.AddIndex(2);
		data.AddIndex(3);

		return data;
	}

	VertexArray SquareVertexArray()
	{
		return Vanadium::Rendering::CreateVertexArray(Vanadium::Rendering::CreateMesh(SquareMeshData(1.0)));
	}
}