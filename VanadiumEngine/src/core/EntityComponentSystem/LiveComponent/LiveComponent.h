#pragma once
#include "pch.h"
#include "core/EntityComponentSystem/Component.h"
#include "core/EntityComponentSystem/EntityRef.h"

namespace Vanadium
{
	class LiveComponent : public Component
	{
	public:
		using Component::Component;

		virtual void OnUpdate(double dt) {};
		virtual void OnRender(double dt) {};
	};
}