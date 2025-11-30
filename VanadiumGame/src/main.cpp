#include "pch.h"
#include <iostream>
#include <cmath>
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
		camera.Get().AddComponent<CameraComponent>()->Zoom = 30.0;
		camera.Get().AddComponent<CameraMovementComponent>()->EnableMove = true;

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

	// utility: random float in [min, max)
	float GetRandomFloat(float min, float max)
	{
		return min + (float)(rand()) / (float)(RAND_MAX) * (max - min);
	}

	float GetRandomRotation()
	{
		return GetRandomFloat(0.0f, 360.0f);
	}

	float GetRandomMass()
	{
		return GetRandomFloat(1.0f, 10.0f);
	}

	Vector2 GetRandomSize()
	{
		return { GetRandomFloat(0.1f, 1.0f), GetRandomFloat(0.1f, 1.0f) };
	}

	// Create a single body at a specific position with a given initial velocity and rotation
	void CreateBodyAt(const Vector2& position, const Vector2& initialVelocity)
	{
		static u32 i = 0;

		EntityRef squareA = CreateEntity();
		Vector2 size = GetRandomSize();
		squareA.Get().AddComponent<TransformComponent>()->Position = position;
		squareA.Get().GetComponent<TransformComponent>().value_or(nullptr)->SetAngleDeg(GetRandomRotation());
		squareA.Get().AddComponent<CircleRigidbody>()->LinearVelocity = initialVelocity;
		squareA.Get().AddComponent<CircleRigidbody>()->AngularVelocity = 3.14;
		squareA.Get().GetComponent<CircleRigidbody>().value_or(nullptr)->Mass = size.y * size.x;
		squareA.Get().AddComponent<RectCollisionComponent>()->SetSize(size);
		if (i == 0)
			i = 45;
		else 
			i = 0;
	}

	// Place `count` bodies roughly evenly around a circle of `radius`. Each body is given an inward-biased velocity
	// so they "launch towards each other". A small tangential component is added for variety.
	void CreateBodiesOnCircle(int count, float radius, float baseSpeed = 5.0f)
	{
		if (count <= 0) return;

		const float twoPi = 3.14159265358979323846f * 2.0f;

		for (int i = 0; i < count; ++i)
		{
			// distribute angles evenly but add a bit of jitter
			float angle = ((float)i / (float)count) * twoPi + GetRandomFloat(-0.05f, 0.05f);

			float px = std::cos(angle) * radius;
			float py = std::sin(angle) * radius;
			Vector2 position = { px, py };

			// inward direction (towards center)
			float invLen = std::sqrt(px * px + py * py);
			Vector2 inward = { 0.0f, 0.0f };
			if (invLen > 1e-6f)
			{
				inward = { -px / invLen, -py / invLen };
			}

			// small tangential component to cause glancing collisions
			Vector2 tangential = { -inward.y, inward.x };

			// vary speed a bit
			float speed = baseSpeed * GetRandomFloat(0.7f, 1.3f);

			// combine inward + tangential (weighted)
			float tangentialWeight = GetRandomFloat(-0.5f, 0.5f);
			Vector2 velocity = { inward.x * speed + tangential.x * speed * tangentialWeight,
								 inward.y * speed + tangential.y * speed * tangentialWeight };

			CreateBodyAt(position, velocity);
		}
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

		// A larger circular perimeter — increase the radius to spread bodies out.
		// Tweak `count` and `radius` to control density and spread.
		const int bodyCount = 100;
		const float circleRadius = 8.0f;

		CreateBodiesOnCircle(bodyCount, circleRadius, /* baseSpeed= */ 2.0f);

		//CreateBodyAt({ -1.0f, 0.0f }, { 1.0f, 0.0f });
		//CreateBodyAt({ 1.0f, 0.0f }, { -1.0f, 0.0f });
	}
};

int main()
{
	Application app(2300, 1200);
	app.PushLayer<GridBackgroundLayer>();
	app.PushLayer<RectCollisionLayer>();
	app.PushLayer<PhysicsLayer>();
	app.PushLayer<SpriteRendererLayer>();
	app.PushLayer<LiveComponentLayer<CameraMovementComponent>>();
	app.PushLayer<LiveComponentLayer<PlayerMovementComponent>>();
	app.PushLayer<LiveComponentLayer<PixelWorld>>();
	app.PushLayer<RectCollisionDebugLayer>();

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