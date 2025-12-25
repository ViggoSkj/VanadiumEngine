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

	PixelBody& pixelBody = *GetComponent<PixelBody>().value();
	PixelSoa pixelSoa = pixelBody.GetSoa();

	i32 minX = INT_MAX;
	i32 minY = INT_MAX;
	i32 maxX = INT_MIN;
	i32 maxY = INT_MIN;

	for (i32 x : pixelSoa.XPositions)
	{
		minX = glm::min(minX, x);
		maxX = glm::max(maxX, x);
	}
	for (i32 y : pixelSoa.YPositions)
	{
		minY = glm::min(minY, y);
		maxY = glm::max(maxY, y);
	}

	Array2D<bool> pixelGrid(maxX - minX + 1, maxY - minY + 1);

	for (int i = 0; i < pixelSoa.Count(); i++)
	{
		i32 x = pixelSoa.XPositions[i] - minX;
		i32 y = pixelSoa.YPositions[i] - minY;
		pixelGrid.Set(x, y, true);
	}

	Vector2 StartPos = Vector2(0, 0);
	Vector2 EndPos = Vector2(0, 0);

	while (StartPos.y < pixelGrid.GetHeight())
	{
		while (StartPos.x < pixelGrid.GetWidth())
		{
			while (EndPos.x < pixelGrid.GetWidth() && pixelGrid.Get(EndPos.x + 1, EndPos.y) == true)
				EndPos.x++;

			while (EndPos.y < pixelGrid.GetHeight())
			{
				for (i32 x = StartPos.x; x <= EndPos.x; x++)
					if (pixelGrid.Get(x, EndPos.y) == false)
						continue;
				EndPos.y++;
			}

			Vector2 pixelStartPost = (StartPos - m_centerOfMass) * PixelWorld::PixelSize;
			Vector2 pixelEndPos = (EndPos - m_centerOfMass) * PixelWorld::PixelSize;
			Rect rect(pixelStartPost, pixelEndPos);
			m_collisionRects.push_back(rect);

			StartPos.x = EndPos.x + 1;
			StartPos.y = EndPos.y;
		}

		StartPos.x = 0;
		StartPos.y = EndPos.y + 1;
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

Rect PixelCollisionComponent::GetAABB()
{
	PixelBody& pixelBody = *GetComponent<PixelBody>().value_or(nullptr);
	PixelSoa pixelSoa = pixelBody.GetSoa();

	i32 minX = INT_MAX;
	i32 minY = INT_MAX;
	i32 maxX = INT_MIN;
	i32 maxY = INT_MIN;

	for (i32 x : pixelSoa.XPositions)
	{
		minX = glm::min(minX, x);
		maxX = glm::max(maxX, x);
	}
	for (i32 y : pixelSoa.YPositions)
	{
		minY = glm::min(minY, y);
		maxY = glm::max(maxY, y);
	}

	TransformComponent& transform = *GetComponent<TransformComponent>().value_or(nullptr);

	Rect localAABB(
		(Vector2(minX, minY) - m_centerOfMass) * PixelWorld::PixelSize,
		(Vector2(maxX + 1, maxY + 1) - m_centerOfMass) * PixelWorld::PixelSize
	);

	// Get rotation from transform
	float cosR = glm::cos(transform.Angle);
	float sinR = glm::sin(transform.Angle);

	// Get all four corners of the local AABB
	Vector2 corners[4] = {
		localAABB.Start,
		Vector2(localAABB.End.x, localAABB.Start.y),
		localAABB.End,
		Vector2(localAABB.Start.x, localAABB.End.y)
	};

	// Rotate each corner and find the new AABB
	float rotatedMinX = FLT_MAX;
	float rotatedMinY = FLT_MAX;
	float rotatedMaxX = -FLT_MAX;
	float rotatedMaxY = -FLT_MAX;

	for (int i = 0; i < 4; i++)
	{
		Vector2 rotatedCorner(
			corners[i].x * cosR - corners[i].y * sinR,
			corners[i].x * sinR + corners[i].y * cosR
		);

		rotatedMinX = glm::min(rotatedMinX, rotatedCorner.x);
		rotatedMinY = glm::min(rotatedMinY, rotatedCorner.y);
		rotatedMaxX = glm::max(rotatedMaxX, rotatedCorner.x);
		rotatedMaxY = glm::max(rotatedMaxY, rotatedCorner.y);
	}

	return Rect(Vector2(rotatedMinX, rotatedMinY), Vector2(rotatedMaxX, rotatedMaxY)).Offset(transform.Position);
}

// Potential overflow
void PixelCollisionComponent::UpdateCenterOfMass()
{
	PixelBody& pixelBody = *GetComponent<PixelBody>().value();
	PixelSoa pixelSoa = pixelBody.GetSoa();

	Vector2 totalPosition = { 0, 0 };

	for (i32 x : pixelSoa.XPositions)
		totalPosition.x += x + 0.5;
	for (i32 y : pixelSoa.YPositions)
		totalPosition.y += y + 0.5;

	m_centerOfMass = totalPosition / (float)pixelSoa.Count();
}

void PixelCollisionComponent::UpdateInverseMass()
{
	Rigidbody& rb = *GetComponent<Rigidbody>().value();
	PixelBody& pixelBody = *GetComponent<PixelBody>().value();
	PixelSoa pixelSoa = pixelBody.GetSoa();
	float pixelMass = PixelWorld::PixelSize * PixelWorld::PixelSize * PixelBody::PixelDensity;
	rb.InverseMass = 1.0 / (pixelSoa.Count() * pixelMass);
}

void PixelCollisionComponent::UpdateInverseInertia()
{
	Rigidbody& rb = *GetComponent<Rigidbody>().value_or(nullptr);
	PixelBody& pixelBody = *GetComponent<PixelBody>().value_or(nullptr);
	PixelSoa pixelSoa = pixelBody.GetSoa();

	float momentOfInertia = 0;
	float pixelMass = PixelWorld::PixelSize * PixelWorld::PixelSize * PixelBody::PixelDensity;

	for (i32 x : pixelSoa.XPositions)
		momentOfInertia += pixelMass * (m_centerOfMass.x - x - 0.5) * (m_centerOfMass.x - x - 0.5) * (PixelWorld::PixelSize * PixelWorld::PixelSize);

	for (i32 y : pixelSoa.YPositions)
		momentOfInertia += pixelMass * (m_centerOfMass.y - y - 0.5) * (m_centerOfMass.y - y - 0.5) * (PixelWorld::PixelSize * PixelWorld::PixelSize);

	rb.InverseInertia = 1 / momentOfInertia;
}
