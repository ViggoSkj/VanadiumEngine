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
#include "core/Rendering/Layers/SpriteRendererLayer.h"
#include "Platformer/Components/CameraMovementComponent.h"
#include "Platformer/Components/PlayerMovementComponent.h"
#include "PixelRenderer/PixelRenderer.h"	
#include "PixelRenderer/StaticPixelChunk.h"	
#include "PixelRenderer/PixelWorld.h"

class TestSceneSetupStep : public SceneSetupStep
{
public:
	TestSceneSetupStep(Scene* scene)
		: SceneSetupStep(scene) { }

	void Execute() override
	{
		Application& app = Application::Get();
		EntityComponentSystem* ECS = app.GetECS();

		EntityRef camera = CreateEntity();
		camera.Get().AddComponent<TransformComponent>();
		camera.Get().AddComponent<CameraComponent>()->Zoom = 1.0;
		camera.Get().AddComponent<CameraMovementComponent>();

		/*
		Entity& e1 = CreateEntity();
		e1.AddComponent<PlayerMovementComponent>();
		e1.AddComponent<SpriteRendererComponent>().LoadRGBATexture("res/images/character.png");
		e1.AddComponent<TransformComponent>();
		e1.AddComponent<RectCollisionComponent>();

		Entity& e2 = CreateEntity();
		e2.AddComponent<SpriteRendererComponent>().LoadRGBATexture("res/images/player-running.png");
		e2.AddComponent<TransformComponent>();
		e2.AddComponent<RectCollisionComponent>();
		*/


		EntityRef e = CreateEntity();
		e.Get().AddComponent<PixelWorld>();
		PixelWorld& world = *PixelWorld::GetInstance();

		for (int y = 0; y < 1000; y++)
		{
			for (int x = 0; x < 1000; x++)
			{
				if ((x + y) % 2 == 0)
					world.AddPixel(Vector2I(x, y), rand() % 3);
			}
		}

	}
};

int main()
{
	Application app(1500, 1000);
	app.PushLayer<RectCollisionLayer>();
	app.PushLayer<SpriteRendererLayer>();
	app.PushLayer<LiveComponentLayer<CameraMovementComponent>>();
	app.PushLayer<LiveComponentLayer<PlayerMovementComponent>>();
	app.PushLayer<LiveComponentLayer<PixelWorld>>();
	app.PushLayer<RectCollisionDebugLayer>();

	SceneRef testScene = app.GetSceneManager()->ConstructScene();
	testScene.Get().AddSetupStep<TestSceneSetupStep>();
	app.GetSceneManager()->LoadScene(testScene.GetId());

	app.Run();

	return 0;
}

/*
TODO:
 - fix background grid
*/