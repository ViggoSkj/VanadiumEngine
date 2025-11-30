#include "pch.h"
#include "RectCollisionComponent.h"
#include "Core.h"
#include <limits>

float Length2(Vector2 vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

float Distance2(Vector2 a, Vector2 b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool RectCollisionComponent::CollidesWith(RectCollisionComponent* other)
{
	for (u32 i = 0; i < Collisions.size(); i++)
	{
		if (Collisions[i] == other)
			return true;
	}

	return false;
}

bool RectCollisionComponent::PointInside_World(Vector2 point)
{
	Vector2 lp = WorldToLocal(point);
	float minx = std::min(Rect.Start.x, Rect.End.x);
	float maxx = std::max(Rect.Start.x, Rect.End.x);
	float miny = std::min(Rect.Start.y, Rect.End.y);
	float maxy = std::max(Rect.Start.y, Rect.End.y);

	return lp.x >= minx && lp.x <= maxx && lp.y >= miny && lp.y <= maxy;
}

Vector2 RectCollisionComponent::LocalToWorld(Vector2 p)
{
	TransformComponent& t = *GetComponent<TransformComponent>().value_or(nullptr);
	Vector2 up = t.Up;
	Vector2 right = { up.y, -up.x };
	return t.Position + right * p.x + up * p.y;
}

Vector2 RectCollisionComponent::WorldToLocal(Vector2 p)
{
	TransformComponent& t = *GetComponent<TransformComponent>().value_or(nullptr);
	Vector2 up = t.Up; // normalized!
	Vector2 right = { up.y, -up.x };
	Vector2 v = p - t.Position;
	return { dot(v, right), dot(v, up) };
}

Vector2 RectCollisionComponent::CenterToWorld()
{
	return LocalToWorld((Rect.Start + Rect.End) / 2.0f);
}

Vector2 RectCollisionComponent::EscapeVector(Vector2 point)
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
	Vector2 escapeVectors[4];

	for (u32 i = 0; i < 4; i++)
	{
		Vector2 A = vertices[i];
		Vector2 B = vertices[(i + 1) % 4];

		Vector2 AB = B - A;
		Vector2 AP = point - A;

		float factor = (glm::dot(AB, AP) / glm::dot(AB, AB));
		Vector2 AD = AB * factor;
		if (factor < 0)
		{
			AD = { 0,0 };
		}
		else if (factor > 1)
		{
			AD = AB;
		}

		Vector2 D = A + AD;


		Vector2 escape = D - point;

		escapeVectors[i] = escape;
	}

	u32 shortest = 0;

	for (u32 i = 0; i < 4; i++)
	{
		if (Length2(escapeVectors[i]) < Length2(escapeVectors[shortest]))
		{
			shortest = i;
		}
	}

	return escapeVectors[shortest];
}

Vector2 RectCollisionComponent::MinimalPenetratingAxis(RectCollisionComponent* other)
{
	float minPenetration = FLT_MAX;
	Vector2 bestAxis;

	Vector2 va1 = LocalToWorld(Rect.Start);
	Vector2 va2 = LocalToWorld({ Rect.Start.x , Rect.End.y });
	Vector2 va3 = LocalToWorld({ Rect.End.x , Rect.End.y });
	Vector2 va4 = LocalToWorld({ Rect.End.x , Rect.Start.y });

	Vector2 vb1 = other->LocalToWorld(other->Rect.Start);
	Vector2 vb2 = other->LocalToWorld({ other->Rect.Start.x , other->Rect.End.y });
	Vector2 vb3 = other->LocalToWorld({ other->Rect.End.x , other->Rect.End.y });
	Vector2 vb4 = other->LocalToWorld({ other->Rect.End.x , other->Rect.Start.y });

	Vector2 normals[] = {
		glm::normalize(va1 - va2),
		glm::normalize(va2 - va3),
		glm::normalize(vb1 - vb2),
		glm::normalize(vb2 - vb3),
	};


	for (u32 i = 0; i < 4; i++)
	{
		Vector2 axis = { -normals[i].y, normals[i].x }; // perpendicular
		// project all vertices of A onto the axis
		float minA = std::numeric_limits<float>::min();
		float maxA = std::numeric_limits<float>::max();

		Vector2 vertsA[] = { va1, va2, va3, va4 };
		Vector2 vertsB[] = { vb1, vb2, vb3, vb4 };

		for (auto v : vertsA)
		{
			float proj = dot(v, axis);
			minA = std::min(minA, proj);
			maxA = std::max(maxA, proj);
		}

		// project all vertices of B onto the axis
		float minB = std::numeric_limits<float>::min();
		float maxB = std::numeric_limits<float>::max();
		for (auto v : vertsB)
		{
			float proj = dot(v, axis);
			minB = std::min(minB, proj);
			maxB = std::max(maxB, proj);
		}

		// compute overlap
		float overlap = std::min(maxA, maxB) - std::max(minA, minB);

		// if there's no overlap, no collision at all
		if (overlap <= 0.0f)
			return {0, 0}; // separating axis found

		// track smallest overlap
		if (overlap < minPenetration)
		{
			minPenetration = overlap;
			bestAxis = axis;
		}
	}

	return bestAxis * minPenetration;
}

Vector2 RectCollisionComponent::CollisionVertex(RectCollisionComponent* other)
{
	Vector2 otherWorldCenter = other->CenterToWorld();

	Vector2 v1 = Rect.Start;
	Vector2 v2 = { Rect.Start.x , Rect.End.y };
	Vector2 v3 = { Rect.End.x , Rect.Start.y };
	Vector2 v4 = Rect.End;

	v1 = LocalToWorld(v1);
	v2 = LocalToWorld(v2);
	v3 = LocalToWorld(v3);
	v4 = LocalToWorld(v4);

	float v1Dist = Distance2(otherWorldCenter, v1);
	float v2Dist = Distance2(otherWorldCenter, v2);
	float v3Dist = Distance2(otherWorldCenter, v3);
	float v4Dist = Distance2(otherWorldCenter, v4);

	float dists[] = { v1Dist, v2Dist,v3Dist, v4Dist };
	Vector2 vertices[] = { v1, v2, v3, v4 };

	int smallestIndex = 0;
	float smallest = dists[0];

	for (u32 i = 0; i < 4; i++)
	{
		if (dists[i] < smallest)
		{
			smallest = dists[i];
			smallestIndex = i;
		}
	}

	return vertices[smallestIndex];
}
