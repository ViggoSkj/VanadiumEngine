#include "UiRenderingLayer.h"
#include "ScreenTransform.h"
#include "UiTree.h"
#include "core/Util/StringHash.h"

UiRenderingLayer::UiRenderingLayer()
	: m_quad(Vanadium::Rendering::CreateMesh(Vanadium::Util::SquareMeshData(2.0, false)))
	, m_shader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/box.shader")->CreateShader().value())
{
}

void UiRenderingLayer::OnRender(double dt)
{
	UnorderedVector<ScreenTransform>& elements = Application::Get().GetECS()->GetComponentStore<ScreenTransform>()->GetComponents();

	UiTree tree;
	std::shared_ptr<UiNode> rootNode = std::make_shared<UiNode>();

	for (ScreenTransform& transform : elements)
	{
		if (transform.Parent.IsEmpty())
		{
			rootNode->transform = Vanadium::ECS::CreateHandle(transform);
			rootNode->resolvedProperties.height = 400;
			rootNode->resolvedProperties.width = 400;
			rootNode->resolvedProperties.xPosition = 400;
			rootNode->resolvedProperties.yPosition = 400;
			transform.Surface = Rect(
				Vector2(rootNode->resolvedProperties.xPosition, rootNode->resolvedProperties.yPosition),
				Vector2(
					rootNode->resolvedProperties.xPosition + rootNode->resolvedProperties.width,
					rootNode->resolvedProperties.yPosition + rootNode->resolvedProperties.height
				)
			);

			tree.root = rootNode;
			break;
		}
	}

	m_shader.Use();

	for (ScreenTransform& transform : elements)
	{
		m_shader.SetUniformVec4("u_rect"_id, transform.Surface);
		GL_CHECK(glDepthFunc(GL_ALWAYS));
		m_quad.Render();
		GL_CHECK(glDepthFunc(GL_LESS));
	}
}