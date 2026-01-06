#include "UiRenderingLayer.h"
#include "ScreenElement.h"
#include "TextElement.h"
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
			std::shared_ptr<UiNode> root = std::make_shared<UiNode>();
			root->transform = Vanadium::ECS::CreateHandle(transform);
			root->style = transform.style;
			tree.root = root;
			break;
		}
	}

	ResolveChildren(tree.root);
	CalculateLayout(tree);

	m_shader.Use();
	GL_CHECK(glDepthFunc(GL_ALWAYS));
	for (std::shared_ptr<UiNode> node : tree.GetNodes())
	{
		if (node->transform.IsEmpty())
			continue;

		ScreenElement& t = node->transform.Get();
		m_shader.SetUniformVec2("u_position"_id, t.box.position);
		m_shader.SetUniformVec2("u_content"_id, t.box.content);

		m_shader.SetUniformVec4("u_border"_id, t.box.border);
		m_shader.SetUniformVec4("u_padding"_id, t.box.padding);

		m_shader.SetUniformVec4("u_color"_id, node->style.backgroundColor);
		m_quad.Render();

		if (auto* props = std::get_if<TextProperties>(&node->special.variant)) {
			if (!props->renderer)
				continue;

			std::vector<Vector2> v(props->text.size());
			for (i32 i = 0; i < v.size(); i++)
			{
				v[i] = node->children[i]->resolvedProperties.box.position;
			}
			props->renderer->SetSymbols(props->text, v);
			props->renderer->Render();
		}
	}
	GL_CHECK(glDepthFunc(GL_LESS));
}

void UiRenderingLayer::OnEvent(Vanadium::Event& event)
{
	Vanadium::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Vanadium::MouseButtonDownEvent>([this](Vanadium::MouseButtonDownEvent& event) { return OnClick(event); });
}

bool UiRenderingLayer::OnClick(Vanadium::MouseButtonDownEvent& event)
{

	return false;
}