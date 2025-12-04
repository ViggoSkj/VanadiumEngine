#include "PhysicsLayer.h"
#include "SquareRigidbody.h"
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
	Vector2 contact; 
	Vector2 normal;                // from A -> B
	float penetration;
	float lambda = 0.0f;
};

// Project 4 square vertices onto axis
static void ProjectSquare(const std::vector<Vector2>& verts, const Vector2& axis, float& min, float& max)
{
	min = max = glm::dot(verts[0], axis);
	for (int i = 1; i < 4; i++)
	{
		float p = glm::dot(verts[i], axis);
		if (p < min) min = p;
		if (p > max) max = p;
	}
}

// Overlap along axis
static float OverlapOnAxis(const std::vector<Vector2>& aVerts, const std::vector<Vector2>& bVerts, const Vector2& axis)
{
	float minA, maxA, minB, maxB;
	ProjectSquare(aVerts, axis, minA, maxA);
	ProjectSquare(bVerts, axis, minB, maxB);
	return std::min(maxA, maxB) - std::max(minA, minB);
}

// SAT for squares
bool SATCollisionSquares(CircleRigidbody* A, CircleRigidbody* B, std::vector<CollisionPair>& pairVec)
{
	auto aVerts = A->GetComponent<RectCollisionComponent>().value_or(nullptr)->GetVerticesWorld();
	auto bVerts = B->GetComponent<RectCollisionComponent>().value_or(nullptr)->GetVerticesWorld();

	// Generate contact points (vertex clipping simplified for squares)
	std::vector<Vector2> contacts;
	for (auto& v : aVerts) {
		if (B->GetComponent<RectCollisionComponent>().value_or(nullptr)->PointInside_World(v))
		{
			Vector2 escape = B->GetComponent<RectCollisionComponent>().value_or(nullptr)->EscapeVector(v);
			CollisionPair pair;
			pair.A = A;
			pair.B = B;
			pair.contact = v;
			pair.penetration = glm::length(escape);
			pair.normal = glm::normalize(escape);
			pairVec.push_back(pair);
		}
	}
	for (auto& v : bVerts)
	{
		if (A->GetComponent<RectCollisionComponent>().value_or(nullptr)->PointInside_World(v))
		{
			Vector2 escape = A->GetComponent<RectCollisionComponent>().value_or(nullptr)->EscapeVector(v);
			CollisionPair pair;
			pair.A = B;
			pair.B = A;
			pair.contact = v;
			pair.penetration = glm::length(escape);
			pair.normal = glm::normalize(escape);
			pairVec.push_back(pair);
		}
	}

	return true;
}


void PhysicsLayer::OnUpdate(double dt)
{
	EntityComponentSystem& ECS = *Application::Get().GetECS();

	UnorderedVector<CircleRigidbody>& rbs = ECS.GetComponentStore<CircleRigidbody>().value_or(nullptr)->GetComponents();

	std::vector<CollisionPair> collisionPairs;

	// generate all square collisions
	for (int i = 0; i < rbs.size(); i++)
	{
		CircleRigidbody* A = &rbs[i];
		for (int j = i + 1; j < rbs.size(); j++)
		{
			CircleRigidbody* B = &rbs[j];
			auto aVerts = A->GetComponent<RectCollisionComponent>().value_or(nullptr);
			auto bVerts = B->GetComponent<RectCollisionComponent>().value_or(nullptr);

			if (!aVerts->CollidesWith(bVerts))
				continue;

			SATCollisionSquares(A, B, collisionPairs);
		}
	}

	// solver loop
	const u32 iterations = 100;
	const float beta = 0.2f;
	const float penetrationSlop = 0.001f;
	const float maxBias = 1.0f;

	for (u32 c = 0; c < iterations; c++)
	{
		for (auto& pair : collisionPairs)
		{
			glm::vec2 n = pair.normal;


			glm::vec2 rA = pair.contact - pair.A->GetPosition();
			glm::vec2 rB = pair.contact - pair.B->GetPosition();

			float rnA = Cross(rA, n);
			float rnB = Cross(rB, n);

			glm::vec2 velB = pair.B->LinearVelocity + Cross(pair.B->AngularVelocity, rB);
			glm::vec2 velA = pair.A->LinearVelocity + Cross(pair.A->AngularVelocity, rA);
			float vRel = glm::dot(pair.normal, velA -velB );

			if (vRel > 0)
				continue;

			float safeDt = (dt <= 1e-9) ? 1e-9f : (float)dt;
			float bias = (pair.penetration > penetrationSlop) ? beta * (pair.penetration - penetrationSlop) / safeDt : 0.0f;
			bias = glm::clamp(bias, 0.0f, maxBias);

			float invMassA = (pair.A->Mass == 0.0f) ? 0.0f : 1.0f / pair.A->Mass;
			float invMassB = (pair.B->Mass == 0.0f) ? 0.0f : 1.0f / pair.B->Mass;
			float invInertiaA = (pair.A->GetInertia() == 0.0f) ? 0.0f : 1.0f / pair.A->GetInertia();
			float invInertiaB = (pair.B->GetInertia() == 0.0f) ? 0.0f : 1.0f / pair.B->GetInertia();

			float kNormal = invMassA + invMassB + invInertiaA * rnA * rnA + invInertiaB * rnB * rnB;
			float effectiveMass = (kNormal == 0.0f) ? 0.0f : 1.0f / kNormal;

			float deltaLambda = -(vRel - bias) * effectiveMass;
			float newLambda = std::max(0.0f, pair.lambda + deltaLambda);
			float appliedDelta = newLambda - pair.lambda;
			pair.lambda = newLambda;

			glm::vec2 P = n * appliedDelta;

			pair.A->LinearVelocity += P * invMassA;
			pair.A->AngularVelocity += invInertiaA * Cross(rA, P);
			pair.B->LinearVelocity -= P * invMassB;
			pair.B->AngularVelocity -= invInertiaB * Cross(rB, P);
		}
	}

	const float percent = 0.8f; // positional correction factor
	const float EPS = 1e-6f;

	for (auto& pair : collisionPairs)
	{
		break;
		glm::vec2 totalCorrection(0.0f);
		float invMassA = (pair.A->Mass == 0.0f) ? 0.0f : 1.0f / pair.A->Mass;
		float invMassB = (pair.B->Mass == 0.0f) ? 0.0f : 1.0f / pair.B->Mass;
		float invMassSum = invMassA + invMassB;
		if (invMassSum < EPS) continue;

		float invInertiaA = (pair.A->GetInertia() == 0.0f) ? 0.0f : 1.0f / pair.A->GetInertia();
		float invInertiaB = (pair.B->GetInertia() == 0.0f) ? 0.0f : 1.0f / pair.B->GetInertia();

		glm::vec2 rA = pair.contact - pair.A->GetPosition();
		glm::vec2 rB = pair.contact - pair.B->GetPosition();

		float correctionMag = std::max(pair.penetration - penetrationSlop, 0.0f) * percent / invMassSum;
		glm::vec2 correction = pair.normal * correctionMag;

		auto* transformA = pair.A->GetComponent<TransformComponent>().value_or(nullptr);
		auto* transformB = pair.B->GetComponent<TransformComponent>().value_or(nullptr);
		if (transformA) transformA->Position -= correction * invMassA;
		if (transformB) transformB->Position += correction * invMassB;

		// rotation
		float torqueA = Cross(rA, -correction);
		float torqueB = Cross(rB, correction);
		pair.A->AngularVelocity += torqueA * invInertiaA;
		pair.B->AngularVelocity += torqueB * invInertiaB;
	}

	if (!Application::Get().GetWindow()->GetInputManager().Down(Key::Space))
	{
		for (int i = 0; i < rbs.size(); i++)
		{
			rbs[i].GetComponent<TransformComponent>().value_or(nullptr)->Position += rbs[i].LinearVelocity * (float)dt;
			rbs[i].GetComponent<TransformComponent>().value_or(nullptr)->RotateRads(-rbs[i].AngularVelocity * (float)dt);
		}
	}
}
