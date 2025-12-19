#include "PixelCollisionComponent.h"
#include "PixelBody.h"
#include "PixelWorld.h"

PixelCollisionComponent::PixelCollisionComponent(EntityRef ref)
	: Component(ref)
{
}

void PixelCollisionComponent::RecalculateCollisionRects()
{
	m_collisionRects.clear();

	PixelBody& pixelBody = *GetComponent<PixelBody>().value_or(nullptr);
	PixelSoa pixelSoa = pixelBody.GetSoa();

	for (int i = 0; i < pixelSoa.Count(); i++)
	{
		Vector2 pixelPos = (pixelSoa.Position(i) - m_centerOfMass - Vector2(0.5f, 0.5f))* PixelWorld::PixelSize;

		Rect rect(pixelPos, pixelPos + Vector2(PixelWorld::PixelSize, PixelWorld::PixelSize));
		m_collisionRects.push_back(rect);
	}
}

Vector2 PixelCollisionComponent::GetCenterOfMass() const
{
	return m_centerOfMass;
}

void PixelCollisionComponent::PixelsChanged()
{
	UpdateCenterOfMass();
	UpdateInverseMass();
	UpdateInverseInertia();
}

// Potential overflow
void PixelCollisionComponent::UpdateCenterOfMass()
{
	PixelBody& pixelBody = *GetComponent<PixelBody>().value_or(nullptr);
	PixelSoa pixelSoa = pixelBody.GetSoa();

	Vector2 totalPosition = { 0, 0 };

	for (i32 x : pixelSoa.XPositions)
		totalPosition.x += x;
	for (i32 y : pixelSoa.YPositions)
		totalPosition.y += y;

	m_centerOfMass = totalPosition / (float)pixelSoa.Count();
}

void PixelCollisionComponent::UpdateInverseMass()
{
	Rigidbody& rb = *GetComponent<Rigidbody>().value_or(nullptr);
	PixelBody& pixelBody = *GetComponent<PixelBody>().value_or(nullptr);
	PixelSoa pixelSoa = pixelBody.GetSoa();
	rb.InverseMass = pixelSoa.Count();
}

void PixelCollisionComponent::UpdateInverseInertia()
{
	Rigidbody& rb = *GetComponent<Rigidbody>().value_or(nullptr);
	PixelBody& pixelBody = *GetComponent<PixelBody>().value_or(nullptr);
	PixelSoa pixelSoa = pixelBody.GetSoa();

	float momentOfInertia = 0;
	float pixelMass = PixelWorld::PixelSize * PixelWorld::PixelSize * PixelBody::PixelDensity;

	for (i32 x : pixelSoa.XPositions)
	{
		for (i32 y : pixelSoa.YPositions)
		{
			momentOfInertia += pixelMass * glm::length(m_centerOfMass.x - Vector2(x, y));
		}
	}

	rb.InverseInertia = 1 / momentOfInertia;
}
