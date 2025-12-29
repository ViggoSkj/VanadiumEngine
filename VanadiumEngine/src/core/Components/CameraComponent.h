#pragma
#include "pch.h"
#include "core/EntityComponentSystem/LiveComponent/LiveComponent.h"
#include "core/Rendering/Camera.h"

namespace Vanadium
{
	class CameraComponent : public LiveComponent
	{
	public:
		static std::optional<CameraComponent*> GetMain()
		{
			if (s_main == nullptr)
				return std::nullopt;

			return s_main;
		};

		CameraComponent(EntityRef ref);

		void OnUpdate(double dt) override;

		Camera GetCamera();

		float Zoom = 1.0;
	private:
		inline static CameraComponent* s_main = nullptr;
	};
}