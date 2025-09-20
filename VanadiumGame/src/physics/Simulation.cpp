#include "Simulation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Simulation::Simulation()
{
	Init();
}

Simulation::~Simulation()
{
}

void Simulation::Init()
{
	m_transforms = std::shared_ptr<glm::mat4[BallCount]>(new glm::mat4[BallCount]);

	for (int i = 0; i < Simulation::BallCount; i++)
	{
		m_positions[i] = RandomBallPosition();
		m_velocities[i] = glm::vec2(0.0f);
	}

	UpdateTransforms();
}

void Simulation::Reset()
{
	Init();
}

void Simulation::ProccessCollision(int ball1, int ball2)
{
	// Vector from ball1 to ball2
	glm::vec2 normal = glm::normalize(m_positions[ball2] - m_positions[ball1]);
	glm::vec2 tangent(-normal.y, normal.x); // perpendicular vector

	// Project velocities onto normal and tangent
	float v1n = glm::dot(m_velocities[ball1], normal);
	float v1t = glm::dot(m_velocities[ball1], tangent);
	float v2n = glm::dot(m_velocities[ball2], normal);
	float v2t = glm::dot(m_velocities[ball2], tangent);

	// Swap normal components for perfectly elastic collision
	float v1n_after = v2n;
	float v2n_after = v1n;

	// Reconstruct velocities
	m_velocities[ball1] = v1n_after * normal + v1t * tangent;
	m_velocities[ball2] = v2n_after * normal + v2t * tangent;

}

void Simulation::PhysicsUpdate(float dt)
{
	for (int i = 0; i < Simulation::BallCount; i++)
	{
		m_velocities[i] += glm::vec2(0.0f, Gravity) * dt;
		m_positions[i] += m_velocities[i] * dt;
	}

	for (int i = 0; i < Simulation::BallCount; i++)
	{
		if (m_positions[i].x - BallRadius < Bounds.start.x)
		{
			m_positions[i].x = Bounds.start.x + BallRadius;
			m_velocities[i].x = -m_velocities[i].x;
		}
		if (m_positions[i].x + BallRadius > Bounds.end.x)
		{
			m_positions[i].x = Bounds.end.x - BallRadius;
			m_velocities[i].x = -m_velocities[i].x;
		}
		if (m_positions[i].y - BallRadius < Bounds.start.y)
		{
			m_positions[i].y = Bounds.start.y + BallRadius;
			m_velocities[i].y = -m_velocities[i].y;
		}
		if (m_positions[i].y + BallRadius > Bounds.end.y)
		{
			m_positions[i].y = Bounds.end.y - BallRadius;
			m_velocities[i].y = -m_velocities[i].y;
		}
	}

	for (int i = 0; i < Simulation::BallCount - 1; i++)
	{
		for (int j = i + 1; j < Simulation::BallCount; j++)
		{
			float dist = glm::distance(m_positions[i], m_positions[j]);
			if (dist < 2 * BallRadius)
			{
				ProccessCollision(i, j);
			}
		}
	}

	UpdateTransforms();
}

glm::vec2 Simulation::RandomBallPosition()
{
	float r1 = static_cast <float>(rand()) / static_cast <float>(RAND_MAX);
	float r2 = static_cast <float>(rand()) / static_cast <float>(RAND_MAX);

	glm::vec2 size = Bounds.GetSize();

	float x = (size.x - 2 * BallRadius) * r1 + BallRadius + Bounds.start.x;
	float y = (size.y - 2 * BallRadius) * r2 + BallRadius + Bounds.start.y;

	return { x, y };
}

void Simulation::UpdateTransforms()
{
	for (int i = 0; i < Simulation::BallCount; i++)
	{
		glm::mat4& mat = m_transforms.get()[i];
		mat = glm::identity<glm::mat4>();
		mat = glm::translate(mat, glm::vec3(m_positions[i], 0.0f));
		mat = glm::scale(mat, glm::vec3(BallRadius, BallRadius, BallRadius));
	}
}
