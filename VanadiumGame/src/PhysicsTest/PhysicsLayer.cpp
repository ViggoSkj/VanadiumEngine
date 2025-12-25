
#include "PhysicsLayer.h"
#include "Rigidbody.h"
#include "Core.h"
#include "PixelRenderer/PixelCollisionComponent.h"
#include "PixelRenderer/PixelWorld.h"
#include "core/ShapeRenderer/ShapeRenderer.h"
#include "core/Math.h"

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
	Rigidbody* A;
	Rigidbody* B;
	Vector2 contact;
	Vector2 normal;                // from A -> B
	float penetration;
	float lambda = 0.0f;
};

// SAT for squares
bool SATCollisionSquares(Rigidbody* rA, Rigidbody* rB, RotatableRect& A, RotatableRect& B, std::vector<CollisionPair>& pairVec, double dt)
{
	std::array<Vector2, 4> aVerts = A.Vertices();
	std::array<Vector2, 4> bVerts = B.Vertices();

	// Generate contact points (vertex clipping simplified for squares)
	std::vector<Vector2> contacts;
	for (Vector2 v : aVerts)
	{
		if (B.PointInside(v))
		{
			Vector2 previousPosition = rA->GetPosition() - rA->LinearVelocity * (float)dt;

			Vector2 other1 = Vector2(FLT_MAX, FLT_MAX);
			Vector2 other2 = Vector2(FLT_MAX, FLT_MAX);

			for (i32 i = 0; i < bVerts.size(); i++)
			{
				if (!Math::Linear::Intersects(previousPosition, v, bVerts[i], bVerts[(i + 1) % 4]))
					continue;

				other1 = bVerts[i];
				other2 = bVerts[(i + 1) % 4];
				break;
			}

			Vector2 escape = Math::Linear::ProjectOnto(v, other1, other2) - v;
			CollisionPair pair;
			pair.A = rA;
			pair.B = rB;
			pair.contact = v;
			pair.penetration = glm::length(escape);
			pair.normal = glm::normalize(escape);
			pairVec.push_back(pair);
			ShapeRenderer::Get()->DrawArrow(pair.contact, pair.contact + escape * 10.0f, { 0.0,0.0,0.0,0.0 });
		}
	}
	for (Vector2 v : bVerts)
	{
		if (A.PointInside(v))
		{
			Vector2 previousPosition = rB->GetPosition() - rB->LinearVelocity * (float)dt;

			Vector2 other1 = Vector2(FLT_MAX, FLT_MAX);
			Vector2 other2 = Vector2(FLT_MAX, FLT_MAX);

			for (i32 i = 0; i < aVerts.size(); i++)
			{
				if (!Math::Linear::Intersects(previousPosition, v, aVerts[i], aVerts[(i + 1) % 4]))
					continue;

				other1 = aVerts[i];
				other2 = aVerts[(i + 1) % 4];
				break;
			}

			ShapeRenderer::Get()->FillCircle(other1, 0.02, { 1.0,1.0,0.0,1.0 });
			ShapeRenderer::Get()->FillCircle(other2, 0.02, { 1.0,1.0,0.0,1.0 });

			Vector2 escape = Math::Linear::ProjectOnto(v, other1, other2) - v;
			CollisionPair pair;
			pair.A = rA;
			pair.B = rB;
			pair.contact = v;
			pair.penetration = glm::length(escape);
			pair.normal = -glm::normalize(escape);
			pairVec.push_back(pair);
			ShapeRenderer::Get()->DrawArrow(pair.contact, pair.contact + escape * 10.0f, { 0.0,0.0,0.0,0.0 });
		}
	}

	return true;
}

void PhysicsLayer::OnUpdate(double dt)
{
	EntityComponentSystem& ECS = *Application::Get().GetECS();

	UnorderedVector<Rigidbody>& rbs = ECS.GetComponentStore<Rigidbody>()->GetComponents();

	if (!Application::Get().GetWindow()->GetInputManager().Down(Key::Space))
	{
		for (int i = 0; i < rbs.size(); i++)
		{
			rbs[i].GetComponent<TransformComponent>()->Position += rbs[i].LinearVelocity * (float)dt;
			rbs[i].GetComponent<TransformComponent>()->RotateRads(-rbs[i].AngularVelocity * (float)dt);
		}
	}

	std::vector<CollisionPair> collisionPairs;
	std::vector<CollisionPair> collisionPairsStaticA;


	// generate all square collisions
	for (int i = 0; i < rbs.size(); i++)
	{
		Rigidbody* A = &rbs[i];
		for (int j = i + 1; j < rbs.size(); j++)
		{
			Rigidbody* B = &rbs[j];

			PixelCollisionComponent& aCollider = *A->GetComponent<PixelCollisionComponent>();
			PixelCollisionComponent& bCollider = *B->GetComponent<PixelCollisionComponent>();

			Rect bAABB = bCollider.GetAABB();
			Rect aAABB = aCollider.GetAABB();

			TransformComponent& aT = *A->GetTransform();
			ShapeRenderer::Get()->FillCircle(aT.Position, 0.04, { 0.0,1.0,0.0,0.7 });

			if (!aAABB.Overlaps(bAABB))
				continue;

			Rect paddedBAABB = bAABB.Padded({ PixelWorld::PixelSize , PixelWorld::PixelSize });

			TransformComponent& bT = *B->GetTransform();

			for (Rect localARect : aCollider.GetCollisionRects())
			{
				RotatableRect globalARect(localARect.Offset(aT.Position).RotateAround(aT.Position, aT.RotationAngle()), aT.RotationAngle());

				// if (!paddedBAABB.PointInside(aT.Position)) use this for single pixels?

				for (Rect localBRect : bCollider.GetCollisionRects())
				{
					RotatableRect globalBRect(localBRect.Offset(bT.Position).RotateAround(bT.Position, bT.RotationAngle()), bT.RotationAngle());

					if (A->Static)
						SATCollisionSquares(A, B, globalARect, globalBRect, collisionPairsStaticA, dt);
					else if (B->Static)
						SATCollisionSquares(B, A, globalBRect, globalARect, collisionPairsStaticA, dt);
					else
						SATCollisionSquares(A, B, globalARect, globalBRect, collisionPairs, dt);
				}
			}
		}
	}

	Vector2 gravity = Vector2(0, -9.82);

	for (Rigidbody& rb : rbs)
	{
		if (!rb.Gravity)
			continue;

		rb.LinearVelocity += gravity * (float)dt;
	}

	// solver loop
	const u32 iterations = 100;
	const float beta = 0.2f;
	const float penetrationSlop = 0.001f;
	const float maxBias = 1.0f;

	for (u32 c = 0; c < iterations; c++)
	{
		for (auto& pair : collisionPairsStaticA)
		{
			glm::vec2 n = pair.normal;

			glm::vec2 rA = pair.contact - pair.A->GetPosition();
			glm::vec2 rB = pair.contact - pair.B->GetPosition();

			float rnB = Cross(rB, n);

			glm::vec2 velB = pair.B->LinearVelocity + Cross(pair.B->AngularVelocity, rB);
			glm::vec2 velA = pair.A->LinearVelocity + Cross(pair.A->AngularVelocity, rA);
			float vRel = glm::dot(pair.normal, velA - velB);

			if (vRel > 0)
				continue;

			float safeDt = (dt <= 1e-9) ? 1e-9f : (float)dt;
			float bias = (pair.penetration > penetrationSlop) ? beta * (pair.penetration - penetrationSlop) / safeDt : 0.0f;
			bias = glm::clamp(bias, 0.0f, maxBias);

			float kNormal = pair.B->InverseMass + pair.B->InverseInertia * rnB * rnB;

			float effectiveMass = (kNormal == 0.0f) ? 0.0f : 1.0f / kNormal;

			float deltaLambda = -(vRel - bias) * effectiveMass;
			float newLambda = std::max(0.0f, pair.lambda + deltaLambda);
			float appliedDelta = newLambda - pair.lambda;
			pair.lambda = newLambda;

			glm::vec2 P = n * appliedDelta;

			//ShapeRenderer::Get()->DrawArrow(pair.contact, pair.contact + P, { 0.0,0.0,0.0,0.0 });

			pair.B->LinearVelocity -= P * pair.B->InverseMass;
			pair.B->AngularVelocity -= pair.B->InverseInertia * Cross(rB, P);
		}

		for (auto& pair : collisionPairs)
		{
			glm::vec2 n = pair.normal;

			glm::vec2 rA = pair.contact - pair.A->GetPosition();
			glm::vec2 rB = pair.contact - pair.B->GetPosition();

			float rnA = Cross(rA, n);
			float rnB = Cross(rB, n);

			glm::vec2 velB = pair.B->LinearVelocity + Cross(pair.B->AngularVelocity, rB);
			glm::vec2 velA = pair.A->LinearVelocity + Cross(pair.A->AngularVelocity, rA);
			float vRel = glm::dot(pair.normal, velA - velB);

			if (vRel > 0)
				continue;

			float safeDt = (dt <= 1e-9) ? 1e-9f : (float)dt;
			float bias = (pair.penetration > penetrationSlop) ? beta * (pair.penetration - penetrationSlop) / safeDt : 0.0f;
			bias = glm::clamp(bias, 0.0f, maxBias);

			float kNormal = pair.A->InverseMass + pair.B->InverseMass
				+ pair.A->InverseInertia * rnA * rnA
				+ pair.B->InverseInertia * rnB * rnB;

			float effectiveMass = (kNormal == 0.0f) ? 0.0f : 1.0f / kNormal;

			float deltaLambda = -(vRel - bias) * effectiveMass;
			float newLambda = std::max(0.0f, pair.lambda + deltaLambda);
			float appliedDelta = newLambda - pair.lambda;
			pair.lambda = newLambda;

			glm::vec2 P = n * appliedDelta;

			//ShapeRenderer::Get()->DrawArrow(pair.contact, pair.contact + P, { 0.0,0.0,0.0,0.0 });

			pair.A->LinearVelocity += P * pair.A->InverseMass;
			pair.A->AngularVelocity += pair.A->InverseInertia * Cross(rA, P);
			pair.B->LinearVelocity -= P * pair.B->InverseMass;
			pair.B->AngularVelocity -= pair.B->InverseInertia * Cross(rB, P);
		}
	}

	const float percent = 0.8f; // positional correction factor
	const float EPS = 1e-6f;

	for (auto& pair : collisionPairs)
	{
		break;
		glm::vec2 totalCorrection(0.0f);
		float invMassSum = pair.A->InverseMass + pair.B->InverseMass;
		if (invMassSum < EPS) continue;

		glm::vec2 rA = pair.contact - pair.A->GetPosition();
		glm::vec2 rB = pair.contact - pair.B->GetPosition();

		float correctionMag = std::max(pair.penetration - penetrationSlop, 0.0f) * percent / invMassSum;
		glm::vec2 correction = pair.normal * correctionMag;

		auto* transformA = pair.A->GetComponent<TransformComponent>();
		auto* transformB = pair.B->GetComponent<TransformComponent>();
		if (transformA) transformA->Position -= correction * pair.A->InverseMass;
		if (transformB) transformB->Position += correction * pair.B->InverseMass;
	}
}
