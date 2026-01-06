#pragma once

namespace Vanadium
{
	class ApplicationLayer
	{
	public:
		virtual ~ApplicationLayer() = default;
		
		virtual void OnUpdate(double dt) {};
		virtual void OnRender(double dt) {};
		virtual void OnEvent(Event& event) {};
	};
}