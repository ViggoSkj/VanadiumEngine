#include "PhysicsLayer.h"
#include "SquareRigidbody.h"

void PhysicsLayer::OnUpdate(double dt)
{
	EntityComponentSystem& ECS = *Application::Get().GetECS();

	UnorderedVector<SquareRigidbody>& rbs = ECS.GetComponentStore<SquareRigidbody>().value_or(nullptr)->GetComponents();

	if (!Application::Get().GetWindow()->GetInputManager().Down(Key::Space))
		for (int i = 0; i < rbs.size(); i++)
		{
			rbs[i].GetComponent<TransformComponent>().value_or(nullptr)->Position += rbs[i].LinearVelocity * (float)dt;
		}

	for (int i = 0; i < rbs.size(); i++)
	{
		SquareRigidbody& A = rbs[i];
		for (int j = i + 1; j < rbs.size(); j++)
		{
			SquareRigidbody& B = rbs[i];

		}
	}
}
