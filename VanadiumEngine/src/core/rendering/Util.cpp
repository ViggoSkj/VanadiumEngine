#include "pch.h"
#include "Util.h"
#include "core/API/Rendering.h"

namespace Vanadium::Util
{
	MeshData Util::SquareMeshData(float width, bool centered)
	{
		MeshData data;

		if (centered)
		{
			data.AddVertex({ -width / 2.0,  width / 2.0, 0.0 }, { 0.0, 0.0 }); // top-left
			data.AddVertex({ width / 2.0,  width / 2.0, 0.0 }, { 1.0, 0.0 }); // top-right
			data.AddVertex({ width / 2.0, -width / 2.0, 0.0 }, { 1.0, 1.0 }); // bottom-right
			data.AddVertex({ -width / 2.0, -width / 2.0, 0.0 }, { 0.0, 1.0 }); // bottom-left
		}
		else {
			data.AddVertex({ 0,  width , 0.0 }, { 0.0, 0.0 }); // top-left
			data.AddVertex({ width,  width , 0.0 }, { 1.0, 0.0 }); // top-right
			data.AddVertex({ width,0, 0.0 }, { 1.0, 1.0 }); // bottom-right
			data.AddVertex({ 0, 0, 0.0 }, { 0.0, 1.0 }); // bottom-left
		}

		data.AddIndex(0);
		data.AddIndex(1);
		data.AddIndex(3);

		data.AddIndex(1);
		data.AddIndex(2);
		data.AddIndex(3);

		return data;
	}
	MeshData SquareMeshData(float width)
	{
		return SquareMeshData(width, true);
	}

	VertexArray SquareVertexArray()
	{
		return Vanadium::Rendering::CreateVertexArray(Vanadium::Rendering::CreateMesh(SquareMeshData(1.0)));
	}
}