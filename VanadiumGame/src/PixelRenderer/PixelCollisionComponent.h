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

	std::vector<Rect> GetCollisionRects() const { return m_collisionRects; }
private:
	std::vector<Rect> m_collisionRects;
	void UpdateCenterOfMass();
	void UpdateInverseMass();
	void UpdateInverseInertia();


	Vector2 m_centerOfMass;
};