#include "UiRenderingLayer.h"
#include "ScreenElement.h"
#include "UiTree.h"
#include "core/Util/StringHash.h"

UiRenderingLayer::UiRenderingLayer()
	: m_quad(Vanadium::Rendering::CreateMesh(Vanadium::Util::SquareMeshData(2.0, false)))
	, m_shader(Application::Get().GetAssetManager()->GetFileAsset<ShaderCodeAsset>("res/shaders/box.shader")->CreateShader().value())
{
}

void UiRenderingLayer::OnRender(double dt)
{
	UnorderedVector<ScreenElement>& elements = Application::Get().GetECS()->GetComponentStore<ScreenElement>()->GetComponents();

	if (elements.size() == 0)
		return;

	UiTree tree;
	for (ScreenElement& transform : elements)
	{
		if (transform.Parent.IsEmpty())
		{
			UiNode root;
			root.transform = Vanadium::ECS::CreateHandle(transform);
			root.style = transform.style;
			tree.root = root;
			break;
		}
	}

	ResolveChildren(tree.root);
	CalculateLayout(tree);

	m_shader.Use();
	GL_CHECK(glDepthFunc(GL_ALWAYS));
	for (UiNode* node : tree.GetNodes())
	{
		ScreenElement& t = node->transform.Get();
		m_shader.SetUniformVec2("u_position"_id, t.box.position);
		m_shader.SetUniformVec2("u_content"_id, t.box.content);
		
		m_shader.SetUniformVec4("u_border"_id, t.box.border);
		m_shader.SetUniformVec4("u_padding"_id, t.box.padding);

		m_shader.SetUniformVec4("u_color"_id, node->style.backgroundColor);
		m_quad.Render();
	}
	GL_CHECK(glDepthFunc(GL_LESS));
}