#include "pch.h"
#include "RectCollisionLayer.h"
#include "core/Components/RectCollisionComponent.h"
#include "core/Components/TransformComponent.h"

float ProjectionScalar(glm::vec2 axis, glm::vec2 point)
{
	return glm::dot(glm::normalize(axis), point);
}

Vector2 MinMaxProjectionScalars(glm::vec2 axis, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4)
{
	float s1 = ProjectionScalar(axis, p1);
	float s2 = ProjectionScalar(axis, p2);
	float s3 = ProjectionScalar(axis, p3);
	float s4 = ProjectionScalar(axis, p4);

	float min = std::min(std::min(s1, s2), std::min(s3, s4));
	float max = std::max(std::max(s1, s2), std::max(s3, s4));

	return { min, max };
}

Vector2 Orient(Vector2 p, Vector2 up)
{
	Vector2 right = { up.y, -up.x };
	Vector2 rotated = { p.x * right.x + p.y * up.x,
						p.x * right.y + p.y * up.y };
	return rotated;
}

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
			TransformComponent* at = a->GetComponent<TransformComponent>().value();
			RectCollisionComponent* b = &colliders[j];
			TransformComponent* bt = b->GetComponent<TransformComponent>().value();

			Vector2 a1 = a->Rect.Start;
			Vector2 a2 = { a->Rect.Start.x , a->Rect.End.y };
			Vector2 a3 = { a->Rect.End.x , a->Rect.Start.y };
			Vector2 a4 = a->Rect.End;

			a1 = Orient(a1, at->Up) + at->Position;
			a2 = Orient(a2, at->Up) + at->Position;
			a3 = Orient(a3, at->Up) + at->Position;
			a4 = Orient(a4, at->Up) + at->Position;

			Vector2 b1 = b->Rect.Start;
			Vector2 b2 = { b->Rect.Start.x , b->Rect.End.y };
			Vector2 b3 = { b->Rect.End.x , b->Rect.Start.y };
			Vector2 b4 = b->Rect.End;

			b1 = Orient(b1, bt->Up) + bt->Position;
			b2 = Orient(b2, bt->Up) + bt->Position;
			b3 = Orient(b3, bt->Up) + bt->Position;
				b4 = Orient(b4, bt->Up) + bt->Position;

			glm::vec2 axis1 = at->Up;
			glm::vec2 axis2 = at->Right();
			glm::vec2 axis3 = bt->Up;
			glm::vec2 axis4 = bt->Right();

			bool colliding = true;

			Vector2 aMinMax = MinMaxProjectionScalars(axis1, a1, a2, a3, a4);
			Vector2 bMinMax = MinMaxProjectionScalars(axis1, b1, b2, b3, b4);
			if (aMinMax.x > bMinMax.y || aMinMax.y < bMinMax.x)
				colliding = false;

			aMinMax = MinMaxProjectionScalars(axis2, a1, a2, a3, a4);
			bMinMax = MinMaxProjectionScalars(axis2, b1, b2, b3, b4);
			if (aMinMax.x > bMinMax.y || aMinMax.y < bMinMax.x)
				colliding = false;

			aMinMax = MinMaxProjectionScalars(axis3, a1, a2, a3, a4);
			bMinMax = MinMaxProjectionScalars(axis3, b1, b2, b3, b4);
			if (aMinMax.x > bMinMax.y || aMinMax.y < bMinMax.x)
				colliding = false;

			aMinMax = MinMaxProjectionScalars(axis4, a1, a2, a3, a4);
			bMinMax = MinMaxProjectionScalars(axis4, b1, b2, b3, b4);
			if (aMinMax.x > bMinMax.y || aMinMax.y < bMinMax.x)
				colliding = false;

			if (colliding)
			{
				a->Collisions.push_back(b);
				b->Collisions.push_back(a);
			}
		}
	}
}