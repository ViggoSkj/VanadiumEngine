#include "pch.h"
#include "core/Application.h"
#include "Rendering.h"

#define Get() Application& app = Application::Get(); RenderingManager& renderingManager = *app.GetRenderingManager();

namespace Vanadium::Rendering
{
	constexpr std::vector<GLVertexAttribute> MeshDataAttributes()
	{
		return {
			GLVertexAttribute(GL_FLOAT, 3, GL_FALSE),
			GLVertexAttribute(GL_FLOAT, 2, GL_FALSE),
		};
	}

	MeshHandle CreateMesh(MeshData data)
	{
		Get();

		return renderingManager.meshStore.CreateMesh(data);
	}

	Mesh* GetMesh(MeshHandle handle)
	{
		Get();

		return renderingManager.meshStore.GetMesh(handle);
	}

	VertexArray CreateVertexArray(MeshHandle handle)
	{
		Mesh* mesh = GetMesh(handle);
		VertexArray vao;
		vao.AddVertexBuffer(MeshDataAttributes(), mesh->vertexBuffer, 0);
		vao.BindIndexBuffer(mesh->indexBuffer);
		return vao;
	}
}