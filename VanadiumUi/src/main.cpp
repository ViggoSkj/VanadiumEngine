#include "Core.h"
#include "ScreenElement.h"
#include "UiRenderingLayer.h"

class UiSetup : public SceneSetupStep
{
public:
	UiSetup(Scene* scene)
		: SceneSetupStep(scene) {
	}

	ScreenElement& CreateBox(Style style)
	{
		EntityRef ref = CreateEntity();
		ScreenElement* t = ref.Get().AddComponent<ScreenElement>();
		t->style = style;
		return *t;
	}

	void Execute() override
	{
		Style style;
		style.backgroundColor = Vanadium::Colors::white;
		style.position = Style::Absolute;
		style.xPosition = 400;
		style.yPosition = 100;
		style.width = 700;
		style.height = 400;
		style.heightAuto = true;
		style.padding = { 100, 100, 100, 100 };

		Style style2;
		style2.margin.marginAuto = { true, true, true ,true };
		style2.backgroundColor = Vanadium::Colors::red;
		style2.backgroundColor.w = 0.5;
		style2.position = Style::Flow;
		style2.width = 200;
		style2.height = 200;

		auto panel = Vanadium::ECS::CreateHandle(CreateBox(style));
		CreateBox(style2).Parent = panel;
		style2.width = 300;
		style2.height = 300;
		style2.widthAuto = true;
		CreateBox(style2).Parent = panel;
	}
};

int main()
{
	Application app(Vanadium::WindowOptions(1600, 1000, 2));

	app.PushLayer<UiRenderingLayer>();

	SceneManager& man = *app.GetSceneManager();

	SceneRef ref = man.ConstructScene();
	ref.Get().AddSetupStep<UiSetup>();

	man.LoadScene(ref.GetId());

	app.Run();

	return 0;
}