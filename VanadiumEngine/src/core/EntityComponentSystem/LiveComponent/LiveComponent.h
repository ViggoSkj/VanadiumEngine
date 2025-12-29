#pragma once
#include "pch.h"
#include "core/EntityComponentSystem/Component.h"
#include "core/EntityComponentSystem/EntityRef.h"

namespace Vanadium
{
	class LiveComponent : public Component
	{
	public:
		LiveComponent(LiveComponent&&) noexcept = default;
		LiveComponent& operator=(LiveComponent&&) noexcept = default;

		LiveComponent(const LiveComponent&) = delete;
		LiveComponent(EntityRef ref)
			: Component(ref) {
		};

		virtual void OnUpdate(double dt) {};
		virtual void OnRender(double dt) {};
	};
}