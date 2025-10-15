#include "pch.h"
#include <iostream>
#include "Components.h"
#include "Platformer/PlatformerLayer.h"
#include "Application.h"
#include "Core.h"
#include "core/BuiltIn/Layers/GridBackgroundLayer.h"
#include "core/Components/RectCollisionLayer.h"
#include "core/Components/RectCollisionComponent.h"
#include "core/Debug/Components/RectCollisionDebugLayer.h"
#include "Platformer/SpriteRendererLayer.h"
#include "Platformer/Components/CameraMovementComponent.h"
#include "Platformer/Components/PlayerMovementComponent.h"
#include "Platformer/SpriteRendererComponent.h"


class TestSceneSetupStep : public SceneSetupStep
{
public:
	void Execute() override
	{
		Application& app = Application::Get();
		EntityComponentSystem* ECS = app.GetECS();

		Entity& camera = CreateEntity();
		camera.AddComponent<TransformComponent>().Position = Vector2(0, -5);
		camera.AddComponent<CameraComponent>().Zoom = 0.1;
		camera.AddComponent<CameraMovementComponent>();

		Entity& e1 = CreateEntity();
		e1.AddComponent<PlayerMovementComponent>();
		e1.AddComponent<SpriteRendererComponent>().LoadRGBATexture("res/images/character.png");
		e1.AddComponent<TransformComponent>();
		e1.AddComponent<RectCollisionComponent>();

		Entity& e2 = CreateEntity();
		e2.AddComponent<SpriteRendererComponent>().LoadRGBATexture("res/images/player-running.png");
		e2.AddComponent<TransformComponent>();
		e2.AddComponent<RectCollisionComponent>();
	}
};

int main()
{

	Application app(1500, 1000);
	app.PushLayer<RectCollisionLayer>();
	app.PushLayer<GridBackgroundLayer>();
	app.PushLayer<SpriteRendererLayer>();
	app.PushLayer<LiveComponentLayer<CameraMovementComponent>>();
	app.PushLayer<LiveComponentLayer<PlayerMovementComponent>>();
	app.PushLayer<RectCollisionDebugLayer>();

	Scene& testScene = app.GetSceneManager()->ConstructScene();
	testScene.AddSetupStep<TestSceneSetupStep>();
	app.GetSceneManager()->LoadScene(testScene.GetId());

	app.Run();

	return 0;
}