#include "pch.h"
#include "Math.h"

namespace Math
{
	float Angle(Vector2 point)
	{
		return std::atan2(point.y, point.x);
	}

	Vector2 RotatePoint(Vector2 point, Vector2 center, float rads)
	{
		float s = glm::sin(rads);
		float c = glm::cos(rads);
		// Translate point back to origin
		point -= center;
		// Rotate point
		float xnew = point.x * c - point.y * s;
		float ynew = point.x * s + point.y * c;
		// Translate point back
		point.x = xnew + center.x;
		point.y = ynew + center.y;
		return point;
	}
}