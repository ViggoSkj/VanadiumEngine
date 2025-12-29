#pragma once
#include "core/CoreTypes.h"

namespace Math
{
#define E_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

	inline const float PI = E_PI;

	float Angle(Vector2 point);

	Vector2 RotatePoint(Vector2 point, Vector2 center, float rads);
	inline Vector2 RotatePoint(Vector2 point, float rads)
	{
		return RotatePoint(point, Vector2(0.0f, 0.0f), rads);
	}

	inline float Sqrt(float v)
	{
		return sqrt(v);
	}

	inline float Sqr(float v)
	{
		return v * v;
	}

	inline float Random()
	{
		return static_cast<float>(rand()) / RAND_MAX;
	}

	inline float Clamp(float value, float min , float max)
	{
		if (value < min)
			return min;
		if (value > max)
			return max;
		return value;
	}

	inline float Length2(Vector2 v)
	{
		return v.x * v.x + v.y * v.y;
	}

	namespace Units
	{
		inline float DegToRad(float deg)
		{
			return (deg / 360.0) * 2 * E_PI;
		}
	}

	namespace Linear
	{
		inline Vector2 ProjectOnto(Vector2 point, Vector2 a, Vector2 b)
		{
			Vector2 AB = b - a;
			Vector2 AP = point - a;

			float k = glm::dot(AB, AP)/glm::dot(AB, AB);

			return a + AB * k;
		}

		inline float PointToLineDistance2(Vector2 point, Vector2 a, Vector2 b)
		{
			return Length2(point - ProjectOnto(point, a, b));
		}

		inline float PointToLineDistance(Vector2 point, Vector2 a, Vector2 b)
		{
			return sqrt(PointToLineDistance2(point, a, b));
		}

		inline float Cross(Vector2 a, Vector2 b)
		{
			return a.x * b.y - a.y * b.x;
		}

		inline bool Intersects(Vector2 a1, Vector2 a2, Vector2 b1, Vector2 b2)
		{
			Vector2 r = a2 - a1;
			Vector2 s = b2 - b1;

			float denom = Cross(r, s);
			float numer1 = Cross(b1 - a1, r);
			float numer2 = Cross(b1 - a1, s);

			if (denom == 0.0f)
			{
				// Parallel or collinear
				return false; // handle separately if needed
			}

			float t = numer2 / denom;
			float u = numer1 / denom;

			return (t >= 0 && t <= 1 && u >= 0 && u <= 1);
		}
	}
}