#pragma once
#include "Application.h"

namespace Vanadium
{
	class RectCollisionLayer : public ApplicationLayer
	{
	public:
		void OnUpdate(double dt) override;
	};
}