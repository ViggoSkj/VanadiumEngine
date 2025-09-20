#pragma once
#include "core/ApplicationLayer.h"
#include "core/Application.h"
#include "physics/Simulation.h"
#include "core/rendering/Camera.h"
#include "core/rendering/VertexBuffer.h"


class PhysicsApplicationLayer : public ApplicationLayer
{
public:
	PhysicsApplicationLayer();
	~PhysicsApplicationLayer();

	void OnUpdate(double dt) override;
	void OnRender(double dt) override;
private:
	Simulation m_simulation;
	Camera m_camera;
	VertexBuffer m_instanceVertexBuffer;
	RenderQueueItem* m_renderQueueItem;
	int m_projectionMatrixUniformId;
};