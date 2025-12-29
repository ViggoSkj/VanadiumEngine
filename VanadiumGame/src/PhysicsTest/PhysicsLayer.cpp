#include "PhysicsLayer.h"
#include "Rigidbody.h"
#include "Core.h"
#include "PixelRenderer/PixelCollisionComponent.h"
#include "PixelRenderer/PixelWorld.h"
#include "core/ShapeRenderer/ShapeRenderer.h"
#include "core/Math.h"

static const u32 iterations = 50;
static const float beta = 0.15f;
static const float penetrationSlop = 0.001f * PixelWorld::PixelSize * 2;
static const float maxBias = 10.0f;

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

struct ContactPoint
{
	Vector2 position;
	float lambdaN = 0;
	float lambdaT = 0; // friction accumulator
	float penetration = 0;
};

struct Manifold
{
	Rigidbody* A = nullptr;
	Rigidbody* B = nullptr;
	Vector2 normal; // A -> B
	std::array<ContactPoint, 2> points;
	u32 pointCount = 0;
};

struct CachedContactPoint
{
	Vector2 position;
	u32 aFace;
	u32 bFace;
	float penetration;
};

struct CachedManifold
{
	u32 aId;
	u32 bId;
	Vector2 normal;
	std::array<CachedContactPoint, 2> points;
	i32 pointCount;
};

static std::vector<CachedManifold> manifoldCache;
static std::vector<u32> deleteCache;

RotatableRect GlobalRect(const Rect& rect, const TransformComponent& transform)
{
	return RotatableRect(rect.Offset(transform.Position).RotateAround(transform.Position, transform.RotationAngle()), transform.RotationAngle());
}

void DebugCollisions(const std::vector<Manifold>& pairs)
{
	return;
	for (i32 i = pairs.size() - 1; i >= 0; i--)
	{
		const Manifold& m = pairs[i];
		for (i32 j = 0; j < m.pointCount; j++)
		{
			const ContactPoint& p = m.points[j];
			ShapeRenderer::Get()->DrawArrow(p.position, p.position + m.normal * p.penetration * 40.0f, { 1.0, 1.0, 1.0, 1.0 });
		}
	}
}

void DebugPixelCollisionComponent(const PixelCollisionComponent& component, const TransformComponent& transform)
{
	return;
	for (const Rect& rect : component.GetCollisionRects())
	{
		RotatableRect rRect = GlobalRect(rect, transform);

		for (Vector2 v : rRect.Vertices())
		{
			ShapeRenderer::Get()->FillCircle(v, 0.05, { 1.0, 0.0,0.0, 1.0, });
		}

		ShapeRenderer::Get()->FillRect(rRect, { 1.0, 1.0, 0.0, 0.5 });
	}
}

std::optional<CachedManifold*> FindChachedPoint(Rigidbody* rA, Rigidbody* rB, std::array<Vector2, 4>& aVerts, std::array<Vector2, 4>& bVerts)
{
	return std::nullopt;
	i32 toDelete = -1;

	for (i32 i = 0; i < manifoldCache.size(); i++)
	{
		CachedManifold& m = manifoldCache[i];

		if (m.aId == rA->GetId() && m.bId == rB->GetId())
		{
			toDelete = i;
			i32 valid = 0;

			for (i32 j = 0; j < m.pointCount; j++)
			{
				CachedContactPoint& contact = m.points[j];

				Vector2 b0 = bVerts[contact.bFace];
				Vector2 b1 = bVerts[(contact.bFace + 1) % 4];

				if (Math::Linear::PointToLineDistance2(contact.position, b0, b1) > Math::Sqr(PixelWorld::PixelSize))
					continue;

				valid++;
			}

			if (valid != m.pointCount)
				break;

			return &m;
		}
	}

	if (toDelete > -1)
		deleteCache.push_back(toDelete);

	return std::nullopt;
}

void SquareCollision(Rigidbody* rA, Rigidbody* rB, std::array<Vector2, 4>& aVerts, std::array<Vector2, 4>& bVerts, RotatableRect& A, RotatableRect& B, std::vector<Manifold>& manifolds, double dt)
{
	std::optional cachedOptional = FindChachedPoint(rA, rB, aVerts, bVerts);

	Manifold man;
	CachedManifold cached;
	cached.aId = rA->GetId();
	cached.bId = rB->GetId();

	man.A = rA;
	man.B = rB;

	std::array<u32, 2> faces;

	u32 c = 0;
	i32 i = 0;
	for (Vector2 v : aVerts)
	{
		if (c > 1)
			break;

		if (B.PointInside(v))
		{
			ContactPoint& point = man.points[c];
			point.position = v;
			point.penetration = FLT_MAX;

			i32 bFace = 0;
			for (i32 i = 0; i < (i32)bVerts.size(); i++)
			{
				Vector2 b1 = bVerts[i];
				Vector2 b2 = bVerts[(i + 1) % 4];
				float p = Math::Linear::PointToLineDistance2(point.position, b1, b2);
				if (p < point.penetration)
				{
					point.penetration = p;
					bFace = i;
				}
			}

			cached.points[c].bFace = bFace;

			// NOTE: this is only used to find a candidate face; true penetration is computed later along the contact normal.
			point.penetration = Math::Sqrt(point.penetration);
			c++;
		}

		i++;
	}

	man.pointCount = c;

	if (c == 1)
		c = 1;

	if (man.pointCount < 1)
		return;

	Vector2 avg = { 0 ,0 };
	for (i32 i = 0; i < (i32)man.pointCount; i++)
	{
		avg += man.points[i].position;
	}
	avg /= (float)man.pointCount;

	Vector2 previousPosition = rA->GetPosition() - rA->LinearVelocity * (float)dt;

	int face = -1;
	Vector2 b1 = Vector2(FLT_MAX, FLT_MAX);
	Vector2 b2 = Vector2(FLT_MAX, FLT_MAX);

	for (i32 i = 0; i < (i32)bVerts.size(); i++)
	{
		if (!Math::Linear::Intersects(previousPosition, avg, bVerts[i], bVerts[(i + 1) % 4]))
			continue;

		b1 = bVerts[i];
		b2 = bVerts[(i + 1) % 4];
		face = i;
		break;
	}

	// Fallback: if we couldn't infer an intersecting face, choose the closest edge to the averaged contact point.
	if (face < 0)
	{
		float best = FLT_MAX;
		for (i32 i = 0; i < (i32)bVerts.size(); i++)
		{
			Vector2 e0 = bVerts[i];
			Vector2 e1 = bVerts[(i + 1) % 4];
			float d2 = Math::Linear::PointToLineDistance2(avg, e0, e1);
			if (d2 < best)
			{
				best = d2;
				b1 = e0;
				b2 = e1;
				face = i;
			}
		}
	}

	Vector2 escape = Math::Linear::ProjectOnto(avg, b1, b2) - avg;
	float escapeLen2 = escape.x * escape.x + escape.y * escape.y;
	if (escapeLen2 <= 1e-12f)
		return;

	man.normal = escape * (1.0f / Math::Sqrt(escapeLen2));

	// Compute penetration depth along the chosen contact normal.
	// For a point inside B, penetration along normal is the distance from the point to the supporting edge (b1->b2).
	for (i32 i = 0; i < (i32)man.pointCount; i++)
	{
		auto& point = man.points[i];
		float depth = glm::dot(man.normal, Math::Linear::ProjectOnto(point.position, b1, b2) - point.position);
		point.penetration = std::max(0.0f, depth);
	}

	if (cachedOptional.has_value())
	{
		CachedManifold& cached = *cachedOptional.value();

		if (cached.pointCount > (i32)man.pointCount)
		{
			man.pointCount = 2;
			int i = 1;
			if (Math::Length2(cached.points[0].position - man.points[0].position) >
				Math::Length2(cached.points[1].position - man.points[0].position)
				)
				i = 0;

			man.points[1].penetration = cached.points[i].penetration;
			man.points[1].position = cached.points[i].position;
		}
	}
	else {
		cached.normal = man.normal;
		cached.pointCount = (i32)man.pointCount;
		for (i32 i = 0; i < (i32)man.pointCount; i++)
		{
			cached.points[i].penetration = man.points[i].penetration;
			cached.points[i].position = man.points[i].position;
		}

		manifoldCache.push_back(cached);
	}

	manifolds.push_back(man);
}

// SAT for squares
void SATCollisionSquares(Rigidbody* rA, Rigidbody* rB, RotatableRect& A, RotatableRect& B, std::vector<Manifold>& pairVec, double dt)
{
	std::array<Vector2, 4> aVerts = A.Vertices();
	std::array<Vector2, 4> bVerts = B.Vertices();

	SquareCollision(rA, rB, aVerts, bVerts, A, B, pairVec, dt);
	SquareCollision(rB, rA, bVerts, aVerts, B, A, pairVec, dt);
}

void PhysicsLayer::OnUpdate(double dt)
{
	EntityComponentSystem& ECS = *Application::Get().GetECS();

	UnorderedVector<Rigidbody>& rbs = ECS.GetComponentStore<Rigidbody>()->GetComponents();

	std::vector<Manifold> manifolds;

	// generate all square collisions
	for (int i = 0; i < rbs.size(); i++)
	{
		Rigidbody* A = &rbs[i];
		PixelCollisionComponent& aCollider = *A->GetComponent<PixelCollisionComponent>();
		TransformComponent& aT = *A->GetTransform();

		for (int j = i + 1; j < rbs.size(); j++)
		{
			Rigidbody* B = &rbs[j];

			PixelCollisionComponent& bCollider = *B->GetComponent<PixelCollisionComponent>();

			Rect bAABB = bCollider.GetAABB();
			Rect aAABB = aCollider.GetAABB();

			ShapeRenderer::Get()->FillCircle(aT.Position, 0.04, { 0.0,1.0,0.0,0.7 });

			if (!aAABB.Overlaps(bAABB))
				continue;

			Rect paddedBAABB = bAABB.Padded({ PixelWorld::PixelSize , PixelWorld::PixelSize });

			TransformComponent& bT = *B->GetTransform();

			for (Rect localARect : aCollider.GetCollisionRects())
			{
				RotatableRect globalARect = GlobalRect(localARect, aT);

				// if (!paddedBAABB.PointInside(aT.Position)) use this for single pixels?
				if (!bAABB.Overlaps(globalARect.GetAABB()))
					continue;

				for (Rect localBRect : bCollider.GetCollisionRects())
				{
					RotatableRect globalBRect = GlobalRect(localBRect, bT);

					if (!globalARect.GetAABB().Overlaps(globalBRect.GetAABB()))
						continue;

					SATCollisionSquares(A, B, globalARect, globalBRect, manifolds, dt);
				}
			}
		}
	}

	DebugCollisions(manifolds);

	Vector2 gravity = Vector2(0, -9.82);

	for (Rigidbody& rb : rbs)
	{
		if (!rb.Gravity)
			continue;

		rb.LinearVelocity += gravity * (float)dt;
	}

	// solver loop

	float safeDt = (dt <= 1e-9) ? 1e-9f : (float)dt;

	for (u32 c = 0; c < iterations; c++)
	{
		for (auto& manifold : manifolds)
		{
			Rigidbody& A = *manifold.A;
			Rigidbody& B = *manifold.B;
			Vector2 normal = manifold.normal;

			float inverseAMass = A.Static ? 0 : A.InverseMass;
			float inverseAInertia = A.Static ? 0 : A.InverseInertia;
			float inverseBMass = B.Static ? 0 : B.InverseMass;
			float inverseBInertia = B.Static ? 0 : B.InverseInertia;

			float muStatic = 0.0f;
			float muDynamic = 0.3f;

			Vector2 linearAChange = { 0, 0 };
			float alngularAChange = 0;
			Vector2 linearBChange = { 0, 0 };
			float alngularBChange = 0;

			for (i32 i = 0; i < manifold.pointCount; i++)
			{
				auto& contact = manifold.points[i];

				glm::vec2 rA = contact.position - A.GetPosition();
				glm::vec2 rB = contact.position - B.GetPosition();

				float rnA = Cross(rA, normal);
				float rnB = Cross(rB, normal);

				glm::vec2 velB = B.LinearVelocity + Cross(B.AngularVelocity, rB);
				glm::vec2 velA = A.LinearVelocity + Cross(A.AngularVelocity, rA);
				float vRel = glm::dot(normal, velA - velB);

				if (vRel > 0)
					continue;

				float bias = (contact.penetration > penetrationSlop) ? beta * (contact.penetration - penetrationSlop) / safeDt : 0.0f;
				bias = glm::clamp(bias, 0.0f, maxBias);

				float kNormal = inverseAMass + inverseBMass
					+ inverseAInertia * rnA * rnA
					+ inverseBInertia * rnB * rnB;

				float effectiveMass = (kNormal == 0.0f) ? 0.0f : 1.0f / kNormal;

				// restitution: only apply bounce for sufficiently fast impacts (avoid jitter on resting contacts)
				const float restitution = 0.3f;
				const float restitutionVelocityThreshold = 1.0f;
				float e = (std::abs(vRel) > restitutionVelocityThreshold) ? restitution : 0.0f;

				// Normal impulse:
				// Solve for vn' = -e * vn with Baumgarte positional bias as a velocity term.
				float deltaLambda = -(vRel - bias) * effectiveMass;
				if (e > 0.0f)
					deltaLambda += -(e * vRel) * effectiveMass;

				float newLambda = std::max(0.0f, contact.lambdaN + deltaLambda);
				float appliedDelta = newLambda - contact.lambdaN;
				contact.lambdaN = newLambda;

				glm::vec2 P = normal * appliedDelta;

				A.LinearVelocity += P * inverseAMass;
				A.AngularVelocity += inverseAInertia * Cross(rA, P);
				B.LinearVelocity -= P * inverseBMass;
				B.AngularVelocity -= inverseBInertia * Cross(rB, P);

				velB = B.LinearVelocity + Cross(B.AngularVelocity, rB);
				velA = A.LinearVelocity + Cross(A.AngularVelocity, rA);
				glm::vec2 dv = velA - velB;

				// tangent = dv minus normal component
				glm::vec2 tangent = dv - normal * glm::dot(dv, normal);
				float tLen2 = glm::dot(tangent, tangent);
				if (tLen2 > 1e-12f)
				{
					tangent *= (1.0f / glm::sqrt(tLen2));

					float rtA = Cross(rA, tangent);
					float rtB = Cross(rB, tangent);

					float kTangent = inverseAMass + inverseBMass
						+ inverseAInertia * rtA * rtA
						+ inverseBInertia * rtB * rtB;

					float massTangent = (kTangent == 0.0f) ? 0.0f : 1.0f / kTangent;

					float vt = glm::dot(dv, tangent);

					// friction impulse (no bias term)
					float dLambdaT = -vt * massTangent;

					// Coulomb friction clamp:
					// - try static friction first (stick)
					// - if exceeded, fall back to dynamic friction (slide)
					float maxStaticFriction = muStatic * contact.lambdaN;
					float newLambdaT = glm::clamp(contact.lambdaT + dLambdaT, -maxStaticFriction, maxStaticFriction);

					// if static friction can't hold, use dynamic friction
					float maxDynamicFriction = muDynamic * contact.lambdaN;
					if (std::abs(newLambdaT) >= maxStaticFriction)
						newLambdaT = glm::clamp(contact.lambdaT + dLambdaT, -maxDynamicFriction, maxDynamicFriction);

					float appliedT = newLambdaT - contact.lambdaT;
					contact.lambdaT = newLambdaT;

					glm::vec2 PT = tangent * appliedT;

					A.LinearVelocity += PT * inverseAMass;
					A.AngularVelocity += inverseAInertia * Cross(rA, PT);
					B.LinearVelocity -= PT * inverseBMass;
					B.AngularVelocity -= inverseBInertia * Cross(rB, PT);
				}
			}

			A.LinearVelocity += linearAChange;
			A.AngularVelocity += alngularAChange;
			B.LinearVelocity += linearBChange;
			B.AngularVelocity += alngularBChange;
		}
	}

	const float percent = 0.02f; // positional correction factor
	const float EPS = 1e-6f;

	for (auto& manifold : manifolds)
	{
		for (i32 i = 0; i < manifold.pointCount; i++)
		{
			auto& contact = manifold.points[i];

			float inverseAMass = manifold.A->Static ? 0 : manifold.A->InverseMass;
			float inverseBMass = manifold.B->Static ? 0 : manifold.B->InverseMass;

			glm::vec2 totalCorrection(0.0f);
			float invMassSum = inverseAMass + inverseBMass;
			if (invMassSum < EPS) continue;

			glm::vec2 rA = contact.position - manifold.A->GetPosition();
			glm::vec2 rB = contact.position - manifold.B->GetPosition();

			float correctionMag = std::max(contact.penetration - penetrationSlop, 0.0f) * percent / invMassSum;
			glm::vec2 correction = manifold.normal * correctionMag;

			auto* transformA = manifold.A->GetComponent<TransformComponent>();
			auto* transformB = manifold.B->GetComponent<TransformComponent>();
			if (transformA) transformA->Position += correction * inverseAMass;
			if (transformB) transformB->Position -= correction * inverseBMass;
		}
	}

	if (!Application::Get().GetWindow()->GetInputManager().Down(Key::Space))
	{
		for (int i = 0; i < rbs.size(); i++)
		{
			auto& rb = rbs[i];

			const float linearEpsilon = 1e-3f;   // units/sec
			const float angularEpsilon = 1e-3f;  // radians/sec

			if (glm::length(rb.LinearVelocity) < linearEpsilon)
				rb.LinearVelocity = Vector2(0.0f);

			if (std::abs(rb.AngularVelocity) < angularEpsilon)
				rb.AngularVelocity = 0.0f;

			rb.GetComponent<TransformComponent>()->Position += rb.LinearVelocity * (float)dt;
			rb.GetComponent<TransformComponent>()->RotateRads(-rb.AngularVelocity * (float)dt);
		}
	}

	std::sort(deleteCache.begin(), deleteCache.end());
	for (i32 i = deleteCache.size() - 1; i >= 0; i--)
	{
		manifoldCache.erase(manifoldCache.begin() + i);
	}
	deleteCache.clear();





	// generate all square collisions
	for (int i = 0; i < rbs.size(); i++)
	{
		Rigidbody* A = &rbs[i];
		PixelCollisionComponent& aCollider = *A->GetComponent<PixelCollisionComponent>();
		TransformComponent& aT = *A->GetTransform();
		DebugPixelCollisionComponent(aCollider, aT);
	}
}