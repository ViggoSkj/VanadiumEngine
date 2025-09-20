#pragma once
#include <memory>
#include "glm/glm.hpp"	
#include "Rect.h"

class Simulation
{
public:
	const static unsigned int BallCount = 300;
	const static unsigned int BallRadius = 1;
	float Gravity = -90.0f;

	const Rect Bounds = { {-100.0f, -100.0f}, {100.0f, 100.0f} };

	Simulation();
	~Simulation();

	void Reset();

	void PhysicsUpdate(float dt);
	std::shared_ptr<glm::mat4[BallCount]> GetTransforms() const { return m_transforms; };
private:
	glm::vec2 m_positions[BallCount];
	glm::vec2 m_velocities[BallCount];


	std::shared_ptr<glm::mat4[BallCount]> m_transforms;

	void Init();
	glm::vec2 RandomBallPosition();
	void UpdateTransforms();
	void ProccessCollision(int ball1, int ball2);
};