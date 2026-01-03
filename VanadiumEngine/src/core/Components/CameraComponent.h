#pragma
#include "pch.h"
#include "core/EntityComponentSystem/LiveComponent/LiveComponent.h"
#include "core/Rendering/Camera.h"

namespace Vanadium
{
	class CameraComponent : public LiveComponent
	{
	public:
		CameraComponent(Vanadium::ComponentData data);

		static ComponentHandle<CameraComponent> GetMain()
		{
			return s_active;
		};

		void OnUpdate(double dt) override;

		Camera GetCamera();

		float Zoom = 1.0;
	private:
		inline static ComponentHandle<CameraComponent> s_active;
	};
}