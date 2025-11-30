#pragma once
#include "Components.h"
#include "core/Util/Rect.h"

class RectCollisionComponent : public Component
{
public:
	void SetSize(Vector2 size)
	{
		SetSize(size.x, size.y);
	}

	void SetSize(float width, float height)
	{
		Rect = { Vector2(-width / 2.0, -height / 2.0), Vector2(width / 2.0, height / 2.0) };
	}

	bool CollidesWith(RectCollisionComponent* other);

	bool PointInside_World(Vector2 point);

	Vector2 LocalToWorld(Vector2 vertex);

	Vector2 WorldToLocal(Vector2 point);

	Vector2 CollisionVertex(RectCollisionComponent* other);

	Vector2 CenterToWorld();

	Vector2 EscapeVector(Vector2 point);

	Vector2 MinimalPenetratingAxis(RectCollisionComponent* other);

	Vector2 GetVertexWorld(u32 index)
	{
		Vector2 v1 = Rect.Start;
		Vector2 v2 = { Rect.Start.x , Rect.End.y };
		Vector2 v3 = { Rect.End.x , Rect.End.y };
		Vector2 v4 = { Rect.End.x , Rect.Start.y };
		v1 = LocalToWorld(v1);
		v2 = LocalToWorld(v2);
		v3 = LocalToWorld(v3);
		v4 = LocalToWorld(v4);
		Vector2 vertices[] = { v1, v2, v3, v4 };
		return vertices[index % 4];
	}

	std::vector<Vector2> GetVerticesWorld()
	{
		return {
			GetVertexWorld(0),
			GetVertexWorld(1),
			GetVertexWorld(2),
			GetVertexWorld(3)
		};
	}

	Rect Rect;

	UnorderedVector<RectCollisionComponent*> Collisions;
};