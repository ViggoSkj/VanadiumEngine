#include "pch.h"
#include <iostream>
#include <cmath>
#include "Components.h"
#include "Application.h"
#include "Core.h"
#include "core/BuiltIn/Layers/GridBackgroundLayer.h"
#include "core/Components/RectCollisionLayer.h"
#include "core/Components/RectCollisionComponent.h"
#include "core/Debug/Components/RectCollisionDebugLayer.h"
#include "core/Rendering/Layers/SpriteRendererLayer.h"
#include "Platformer/Components/CameraMovementComponent.h"
#include "PhysicsTest/PhysicsLayer.h"
#include "PhysicsTest/CircleRigidbody.h"

class PhysicsSceneSetup : public SceneSetupStep
{
public:
	PhysicsSceneSetup(Scene* scene)
		: SceneSetupStep(scene) {
	}

	void CreateBall(Vector2 position, Vector2 velocity, bool gravity = true)
	{
		EntityRef Ball = CreateEntity();
		Ball.Get().AddComponent<TransformComponent>()->Position = position;
		Ball.Get().AddComponent<CircleRigidbody>()->SetLinearVelocity(velocity);
		Ball.Get().GetComponent<CircleRigidbody>().value()->Gravity = gravity;
		Ball.Get().AddComponent<SpriteRendererComponent>()->LoadRGBATexture("res/images/character.png");
	}

	void Execute() override
	{
		Application& app = Application::Get();
		EntityComponentSystem* ECS = app.GetECS();
		AssetManager* assetMan = app.GetAssetManager();

		EntityRef CameraRef = CreateEntity();
		CameraRef.Get().AddComponent<TransformComponent>();
		CameraRef.Get().AddComponent<CameraComponent>()->Zoom = 10.0;
		CameraRef.Get().AddComponent<CameraMovementComponent>();

		for (i32 i = 1; i < 8; i++)
		{
			CreateBall({ 0, i * 2.0 + 1 }, { 0, 0 });
		}
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