#include "pch.h"
#include "core/Application.h"
#include "core/AssetManager/AssetTypes/Texture/TextureAsset.h"
#include "Rendering.h"

#define LoadDefaultServiceVariables() \
Vanadium::Application& app = Application::Get(); \
Vanadium::Detail::Rendering::RenderingManager& renderingManager = *app.GetRenderingManager(); \
Vanadium::AssetManager& assetManager = *app.GetAssetManager();

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
		LoadDefaultServiceVariables();

		return renderingManager.meshStore.CreateMesh(data);
	}

	Mesh* GetMesh(MeshHandle handle)
	{
		LoadDefaultServiceVariables();

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

	RenderTextureHandle LoadTexture(std::filesystem::path path)
	{
		LoadDefaultServiceVariables();
		auto tex = assetManager.GetFileAsset<TextureRGBAAsset>(path);
		return renderingManager.textureStore.Create(tex->Texture);
	}
	RenderTexture* GetRenderTexture(RenderTextureHandle handle)
	{
		LoadDefaultServiceVariables();

		return renderingManager.textureStore.Get(handle);
	}
}