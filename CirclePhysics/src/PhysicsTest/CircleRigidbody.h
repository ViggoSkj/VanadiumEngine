#pragma once
#include "Core.h"

class CircleRigidbody : public Component
{
public:
	CircleRigidbody(CircleRigidbody&& other) noexcept = default;
	CircleRigidbody& operator=(CircleRigidbody&& other) noexcept = default;
	CircleRigidbody(EntityRef entityRef)
		: Component(entityRef) {
	};

	Vector2 GetPosition();
	float GetInverseMass() const { return m_inverseMass; }
	float GetMass() const { return m_inverseMass == 0 ? 0 : 1.0f / m_inverseMass; }
	float GetInverseInertia() const { return m_inverseInertia; }
	float GetInertia() const { return m_inverseInertia == 0 ? 0 : 1.0f / m_inverseInertia; }
	Vector2 GetLinearVelocity() const { return m_linearVelocity; }
	float GetRadius() const { return m_radius; }

	void SetLinearVelocity(const Vector2& velocity) { m_linearVelocity = velocity; }
	void SetRadius(float radius)
	{
		m_radius = radius;
		UpdateMass(1.0f);
	}

	Vector2 Center() {
		return GetPosition();
	}

	bool Gravity = true;
private:
	void UpdateInertia()
	{
		float mass = GetMass();
		if (mass == 0)
		{
			m_inverseInertia = 0;
			return;
		}
		float inertia = 0.5f * mass * m_radius * m_radius;
		m_inverseInertia = 1.0f / inertia;
	}

	void UpdateMass(float density)
	{
		float area = 3.14159265f * m_radius * m_radius;
		float mass = area * density;
		if (mass == 0)
		{
			m_inverseMass = 0;
			return;
		}
		m_inverseMass = 1.0f / mass;
		UpdateInertia();
	}

	float m_radius = 0.5f;
	float m_inverseMass = 1.0;
	float m_inverseInertia = 0;
	Vector2 m_linearVelocity = Vector2(0.0f);
};