#include "pch.h"
#include "RenderObject.h"
#include "Application.h"

namespace Vanadium
{
	RenderObject::RenderObject(MeshHandle handle)
		: meshHandle(handle)
	{
		Mesh* mesh = Application::Get().GetRenderingManager()->meshStore.GetMesh(handle);
		if (mesh == nullptr)
			return;

		vertexArray.AddVertexBuffer(
			{
				GLVertexAttribute(GL_FLOAT, 3, GL_FALSE),
				GLVertexAttribute(GL_FLOAT, 2, GL_FALSE),
			}
		, mesh->vertexBuffer, 0);

		vertexArray.BindIndexBuffer(mesh->indexBuffer);

		m_valid = true;
	}

	void RenderObject::Render()
	{
		Mesh* mesh = Application::Get().GetRenderingManager()->meshStore.GetMesh(meshHandle);
		if (mesh == nullptr)
		{
			m_valid = false;
			return;
		}

		vertexArray.Bind();
		GL_CHECK(glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0))
	}
}