#include "PhysicsLayer.h"
#include "CircleRigidbody.h"
#include "Core.h"

static float Length2(Vector2 vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

static Vector2 Cross(float a, Vector2 v)
{
	return Vector2(-a * v.y, a * v.x);
}

static float Cross(Vector2 a, Vector2 b)
{
	return a.x * b.y - a.y * b.x;
}

struct CollisionPair
{
	CircleRigidbody* A;
	CircleRigidbody* B;
	Vector2 normal;
	Vector2 contactPoint;
	float penetration;
	float lambda = 0.0f;
};

void PhysicsLayer::OnUpdate(double dt)
{
	EntityComponentSystem& ECS = *Application::Get().GetECS();

	UnorderedVector<CircleRigidbody>& rbs = ECS.GetComponentStore<CircleRigidbody>().value_or(nullptr)->GetComponents();

	std::vector<CollisionPair> pairs;

	for (u32 i = 0; i < rbs.size(); i++)
	{
		CircleRigidbody* body = &rbs[i];

		if (body->GetPosition().y - body->GetRadius() <= 0)
		{
			CollisionPair c;
		}

		if (body->Gravity)
			body->SetLinearVelocity(body->GetLinearVelocity() + Vector2(0, -Gravity) * (float)dt);
	}

	// find all collision pairs
	for (int i = 0; i < rbs.size(); i++)
	{
		CircleRigidbody* A = &rbs[i];
		for (int j = i + 1; j < rbs.size(); j++)
		{
			CircleRigidbody* B = &rbs[j];

			float minDist = A->GetRadius() + B->GetRadius();
			Vector2 diff = B->GetPosition() - A->GetPosition();

			if (Length2(diff) < minDist * minDist)
			{
				CollisionPair pair;
				pair.A = A;
				pair.B = B;
				pair.normal = glm::normalize(diff);
				pair.penetration = minDist - glm::length(diff);
				pair.contactPoint = (A->Center() + pair.normal * A->GetRadius() + B->Center() - pair.normal * B->GetRadius()) / 2.0f,
					pairs.push_back(pair);
			}
		}
	}

	// solver loop
	const u32 iterations = 150;
	const float beta = 0.1f;
	const float penetrationSlop = 0.001f;
	const float maxBias = 0.1f;

	for (u32 c = 0; c < iterations; c++)
	{
		for (auto& pair : pairs)
		{
			glm::vec2 velA = pair.A->GetLinearVelocity();
			glm::vec2 velB = pair.B->GetLinearVelocity();
			float vRel = glm::dot(pair.normal, velB - velA);

			if (vRel > 0)
				continue;

			float safeDt = (dt <= 1e-9) ? 1e-9f : (float)dt;
			float bias = (pair.penetration > penetrationSlop) ? beta * (pair.penetration - penetrationSlop) / safeDt : 0.0f;
			bias = glm::clamp(bias, 0.0f, maxBias);

			// normal of A -> collision
			glm::vec2 ra = pair.contactPoint - pair.A->Center();

			// normal of B -> collision
			glm::vec2 rb = pair.contactPoint - pair.B->Center();

			float rnA = Cross(ra, pair.normal);
			float rnB = Cross(rb, pair.normal);

			float kNormal = pair.A->GetInverseMass() + pair.B->GetInverseMass() + pair.A->GetInverseInertia() * rnA * rnA + pair.B->GetInverseInertia() * rnB * rnB;;
			float effectiveMass = (kNormal == 0.0f) ? 0.0f : 1.0f / kNormal;

			float deltaLambda = -(vRel)*effectiveMass * 2;
			float newLambda = std::max(0.0f, pair.lambda + deltaLambda);
			float appliedDelta = newLambda - pair.lambda;
			pair.lambda = newLambda;

			glm::vec2 P = pair.normal * appliedDelta;

			pair.A->SetLinearVelocity(pair.A->GetLinearVelocity() - P * pair.A->GetInverseMass());
			pair.B->SetLinearVelocity(pair.B->GetLinearVelocity() + P * pair.B->GetInverseMass());
		}
	}

	if (!Application::Get().GetWindow()->GetInputManager().Down(Key::Space))
	{
		for (int i = 0; i < rbs.size(); i++)
		{
			rbs[i].GetComponent<TransformComponent>().value_or(nullptr)->Position += rbs[i].GetLinearVelocity() * (float)dt;
		}
	}
}
