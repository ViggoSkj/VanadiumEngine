#include "pch.h"
#include "RectCollisionLayer.h"
#include "core/Components/RectCollisionComponent.h"
#include "core/Components/TransformComponent.h"

void RectCollisionLayer::OnUpdate(double dt)
{
	EntityComponentSystem& ECS = *Application::Get().GetECS();

	ComponentStore<RectCollisionComponent>& store = *ECS.GetComponentStore<RectCollisionComponent>().value();

	UnorderedVector<RectCollisionComponent>& colliders = store.GetComponents();

	if (colliders.size() == 0)
		return;

	for (int i = 0; i < colliders.size(); i++)
		colliders[i].Collisions.clear();

	for (int i = 0; i < colliders.size() - 1; i++)
	{
		for (int j = i + 1; j < colliders.size(); j++)
		{
			RectCollisionComponent* a = &colliders[i];
			TransformComponent& at = a->GetComponent<TransformComponent>();
			RectCollisionComponent* b = &colliders[j];
			TransformComponent& bt = b->GetComponent<TransformComponent>();
			if (a->Rect.Overlaps(at.Position, b->Rect, bt.Position))
			{
				a->Collisions.push_back(b);
				b->Collisions.push_back(a);
			}
		}
	}
}