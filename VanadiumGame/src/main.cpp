#include <iostream>
#include "Platformer/PlatformerLayer.h"
#include "Application.h"
#include "Platformer/SpriteRendererLayer.h"
#include "Platformer/Components/CameraMovementComponent.h"
#include "Platformer/Components/PlayerMovementComponent.h"
#include "Platformer/TransformComponent.h"
#include "Platformer/SpriteRendererComponent.h"
#include "SimdTest/SimdTest.h"
#include "core/Scene/Scene.h"
#include "core/Scene/SceneSetupStep.h"
#include "core/BuiltIn/Layers/GridBackgroundLayer.h"
#include "ECS.h"


class TestSceneSetupStep : public SceneSetupStep
{
public:
	void Execute() override
	{
		Application& app = Application::Get();
		EntityComponentSystem* ECS = app.GetECS();

		Entity& camera = CreateEntity();
		camera.AddComponent<CameraComponent>();
		camera.AddComponent<CameraMovementComponent>();

		Entity& e1 = CreateEntity();
		e1.AddComponent<SpriteRendererComponent>().LoadRGBATexture("res/images/character.png");
		e1.AddComponent<TransformComponent>();
		e1.AddComponent<PlayerMovementComponent>();

		Entity& e2 = CreateEntity();
		e2.AddComponent<SpriteRendererComponent>().LoadRGBATexture("res/images/player-running.png");
		e2.AddComponent<TransformComponent>();
	}
};

int main()
{

	Application app(1500, 1000);
	app.PushLayer<GridBackgroundLayer>();
	app.PushLayer<SpriteRendererLayer>();
	app.PushLayer<LiveComponentLayer<CameraMovementComponent>>();
	app.PushLayer<LiveComponentLayer<PlayerMovementComponent>>();

	Scene& testScene = app.GetSceneManager()->ConstructScene();
	testScene.AddSetupStep<TestSceneSetupStep>();
	app.GetSceneManager()->LoadScene(testScene.GetId());

	app.Run();

	return 0;
}