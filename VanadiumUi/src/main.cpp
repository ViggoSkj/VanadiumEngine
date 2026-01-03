#include "Core.h"
#include "ScreenTransform.h"
#include "ScreenBox.h"
#include "UiRenderingLayer.h"

class UiSetup : public SceneSetupStep
{
public:
	UiSetup(Scene* scene)
		: SceneSetupStep(scene) {
	}

	void Execute() override
	{
		EntityRef ref = CreateEntity();
		ref.Get().AddComponent<ScreenTransform>();
		ref.Get().AddComponent<ScreenBox>();
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