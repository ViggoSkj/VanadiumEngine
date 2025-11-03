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
#include "MapAsset.h"
#include "PhysicsTest/PhysicsLayer.h"
#include "PhysicsTest/SquareRigidbody.h"

class TestSceneSetupStep : public SceneSetupStep
{
public:
	TestSceneSetupStep(Scene* scene)
		: SceneSetupStep(scene) {
	}

	void Execute() override
	{
		Application& app = Application::Get();
		EntityComponentSystem* ECS = app.GetECS();
		AssetManager* assetMan = app.GetAssetManager();

		EntityRef camera = CreateEntity();
		camera.Get().AddComponent<TransformComponent>();
		camera.Get().AddComponent<CameraComponent>()->Zoom = 10.0;
		camera.Get().AddComponent<CameraMovementComponent>()->EnableMove = false;

		EntityRef e1 = CreateEntity();
		e1.Get().AddComponent<PlayerMovementComponent>();
		e1.Get().AddComponent<SpriteRendererComponent>()->LoadRGBATexture("res/images/character.png");
		e1.Get().AddComponent<TransformComponent>();
		e1.Get().AddComponent<RectCollisionComponent>();

		camera.Get().GetComponent<CameraMovementComponent>().value_or(nullptr)->Target = e1;

		/*
		Entity& e2 = CreateEntity();
		e2.AddComponent<SpriteRendererComponent>().LoadRGBATexture("res/images/player-running.png");
		e2.AddComponent<TransformComponent>();
		e2.AddComponent<RectCollisionComponent>();
		*/


		EntityRef e = CreateEntity();
		e.Get().AddComponent<PixelWorld>();
		PixelWorld& world = *PixelWorld::GetInstance();

		for (int y = 0; y < 0 * 256 * 5; y++)
		{
			for (int x = 0; x < 256 * 5; x++)
			{
				if ((x + y) % 2 == 0)
					world.AddPixel(Vector2I(x, y), rand() % 3);
			}
		}

		std::shared_ptr<MapAsset> map = assetMan->GetFileAsset<MapAsset>("res/maps/testing.map");

		u32 brushSize = 32;

		for (u32 y = 0; y < map->Map.GetHeight(); y++)
		{
			for (u32 x = 0; x < map->Map.GetWidth(); x++)
			{
				u8 t = map->Map.Get(x, y);
				if (t != 0)
				{
					for (u32 xa = 0; xa < brushSize; xa++)
					{
						for (u32 ya = 0; ya < brushSize; ya++)
						{
							world.AddPixel({ x * brushSize + xa, y * brushSize + ya }, t);
						}
					}
				}

			}
		}
	}
};

class PhysicsSceneSetup : public SceneSetupStep
{
public:
	PhysicsSceneSetup(Scene* scene)
		: SceneSetupStep(scene) {
	}

	void Execute() override
	{
		Application& app = Application::Get();
		EntityComponentSystem* ECS = app.GetECS();
		AssetManager* assetMan = app.GetAssetManager();

		EntityRef camera = CreateEntity();
		camera.Get().AddComponent<TransformComponent>();
		camera.Get().AddComponent<CameraComponent>()->Zoom = 5.0;
		camera.Get().AddComponent<CameraMovementComponent>()->EnableMove = false;

		EntityRef squareA = CreateEntity();
		squareA.Get().AddComponent<TransformComponent>()->Position = Vector2(-2, 0);
		squareA.Get().GetComponent<TransformComponent>().value_or(nullptr)->SetAngleDeg(rand()%360);
		squareA.Get().AddComponent<SquareRigidbody>()->LinearVelocity = Vector2(1, 0);
		squareA.Get().AddComponent<RectCollisionComponent>()->SetSize(rand()%2 + 1, rand() % 2 + 1);


		EntityRef squareB = CreateEntity();
		squareB.Get().AddComponent<TransformComponent>()->Position = Vector2(2, 0);
		squareB.Get().GetComponent<TransformComponent>().value_or(nullptr)->SetAngleDeg(rand() % 360);
		squareB.Get().AddComponent<SquareRigidbody>()->LinearVelocity = Vector2(-1, 0);
		squareB.Get().AddComponent<RectCollisionComponent>()->SetSize(rand() % 2 + 1, rand() % 2 + 1);
	}
};

int main()
{
	Application app(2300, 1200);
	app.PushLayer<GridBackgroundLayer>();
	app.PushLayer<RectCollisionLayer>();
	app.PushLayer<SpriteRendererLayer>();
	app.PushLayer<LiveComponentLayer<CameraMovementComponent>>();
	app.PushLayer<LiveComponentLayer<PlayerMovementComponent>>();
	app.PushLayer<LiveComponentLayer<PixelWorld>>();
	app.PushLayer<RectCollisionDebugLayer>();
	app.PushLayer<PhysicsLayer>();

	SceneRef testScene = app.GetSceneManager()->ConstructScene();
	testScene.Get().AddSetupStep<PhysicsSceneSetup>();
	app.GetSceneManager()->LoadScene(testScene.GetId());

	app.Run();

	return 0;
}

/*
TODO:
 - fix background grid
*/