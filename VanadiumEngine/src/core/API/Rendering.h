#pragma once
#include "core/Rendering/Mesh/MeshStore.h"	
#include "core/Rendering/Primitives/VertexArray.h"
#include "core/Rendering/textures/TextureStore.h"

namespace Vanadium::Rendering
{
	constexpr std::vector<GLVertexAttribute> MeshDataAttributes();

#pragma region Mesh

	MeshHandle CreateMesh(MeshData mesh);
	Mesh* GetMesh(MeshHandle handle);

#pragma endregion

#pragma region Vertex Array

	VertexArray CreateVertexArray(MeshHandle handle);

#pragma endregion

#pragma region Textures

	RenderTextureHandle LoadTexture(std::filesystem::path path);
	RenderTexture* GetRenderTexture(RenderTextureHandle handle);

#pragma endregion
}