#pragma once


// Main
#include "core/API/Rendering.h"
#include "core/Rendering/Util.h"

// Higher Level
#include "core/Rendering/RenderObject.h"

// Shaders
#include "core/Rendering/Shaders/Descriptors/ShaderDescriptorBase.h"
#include "core/Rendering/Shaders/Descriptors/VertexShaderDescriptor.h"
#include "core/Rendering/Shaders/Descriptors/FragmentShaderDescriptor.h"
#include "core/Rendering/Shaders/Descriptors/ShaderDescriptor.h"
#include "core/Rendering/Shaders/ShaderUniform.h"
#include "core/Rendering/Shaders/GLShader.h"
#include "core/Rendering/Shaders/GLUniformBuffer.h"

#include "core/AssetManager/AssetTypes/Shader/ShaderAsset.h"

// Vertex, Index
#include "core/Rendering/Primitives/VertexBuffer.h"
#include "core/Rendering/Primitives/IndexBuffer.h"
#include "core/Rendering/Primitives/VertexArray.h"

// Camera
#include "core/Rendering/Camera.h"

// Texture
#include "core/Rendering/Textures/GLTexture.h"
#include "core/Rendering/Textures/TextureConfiguration.h"
#include "core/AssetManager/AssetTypes/Texture/Texture.h"
#include "core/AssetManager/AssetTypes/Texture/TextureAsset.h"

// Mesh
#include "core/Rendering/Mesh/Mesh.h"

using Vanadium::VertexArray;
using Vanadium::IndexBuffer;
using Vanadium::VertexBuffer;

using Vanadium::RenderObject;
using Vanadium::Shader;