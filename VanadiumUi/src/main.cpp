#include "Core.h"
#include "ScreenElement.h"
#include "UiRenderingLayer.h"
#include "TextElement.h"
#include "ButtonElement.h"
#include "StyleSheetParser.h"

using namespace StyleLiterals;

class SymbolTesting : public SceneSetupStep
{
public:
	using SceneSetupStep::SceneSetupStep;

	ScreenElement& CreateBox(Style style)
	{
		EntityRef ref = CreateEntity();
		ScreenElement* t = ref.Get().AddComponent<ScreenElement>();
		t->style = style;
		return *t;
	}

	ScreenElement& CreateTextElement(Style style, std::string text)
	{
		std::shared_ptr<SymbolSheet> symbolSheet = Application::Get().GetAssetManager()->GetFileAsset<SymbolSheet>("res/textures/font.png");
		ScreenElement& e = CreateBox(style);
		e.GetEntity().AddComponent<TextElement>()->text = text;
		e.GetEntity().AddComponent<ButtonElement>();
		e.GetEntity().GetComponent<TextElement>()->symbolRenderer = std::make_unique<SymbolRenderer>(symbolSheet);
		return e;
	}

	void Execute() override
	{
		std::shared_ptr<StyleSheet> styleSheet = Application::Get().GetAssetManager()->GetFileAsset<StyleSheet>("res/styles/style.vss");

		Style style = styleSheet->GetClassDefinition("panel").value();
		/*
				style.backgroundColor = Vanadium::Colors::white;
				style.positioning = Style::Absolute;
				style.yPosition = 100_px;
				style.widthAuto = true;
				style.height = 400_px;
				style.margin = 100_px;
				style.heightAuto = true;
				style.border = { 10_px, 10_px, 10_px, 10_px };
				style.padding = { 100_px, 100_px, 100_px, 100_px };
				style.borderRadius = 10_px;
		*/

		auto panel = Vanadium::ECS::CreateHandle(CreateBox(style));

		Style style2;
		style2.padding = 10_px;
		style2.margin = 10_px;
		style2.marginAuto = { true, true, true ,true };
		style2.backgroundColor = Vanadium::Colors::red;
		style2.backgroundColor.value.w = 0.5;
		style2.positioning = Style::Flow;
		style2.width = 350_px;
		style2.height = 200_px;
		//CreateTextElement(style2, "T").Parent = panel;
		CreateTextElement(style2, "This is a test").Parent = panel;
	}
};

int main()
{
	Application app(Vanadium::WindowOptions(1600, 1000, 2));

	app.PushLayer<UiRenderingLayer>();

	SceneManager& man = *app.GetSceneManager();

	SceneRef ref = man.ConstructScene();
	ref.Get().AddSetupStep<SymbolTesting>();

	man.LoadScene(ref.GetId());

	app.Run();

	return 0;
}