#pragma once
#include "Component.h"

class LiveComponent : public Component
{
public:
	LiveComponent(unsigned int owner)
		: Component(owner) {
	};

	virtual void OnUpdate(double dt) {};
	virtual void OnRender(double dt) {};

private:
};