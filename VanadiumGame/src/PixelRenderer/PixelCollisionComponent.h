#pragma once
#include "pch.h"
#include "core/Util/Rect.h"
#include "core/EntityComponentSystem/Component.h"

class PixelCollisionComponent : public Component
{
public:
	PixelCollisionComponent(EntityRef ref);

	void RecalculateCollisionRects();

	Vector2 GetCenterOfMass() const;

	void PixelsChanged();

	Rect GetAABB();

	std::vector<Rect> GetCollisionRects() const { return m_collisionRects; }
private:
	void UpdateCenterOfMass();
	void UpdateInverseMass();
	void UpdateInverseInertia();

	std::vector<Rect> m_collisionRects;
	Vector2 m_centerOfMass = { 0, 0 };
};