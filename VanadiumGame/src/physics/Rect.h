#pragma once
#include "glm/glm.hpp"

struct Rect
{
	glm::vec2 start;
	glm::vec2 end;

	glm::vec2 GetSize() const
	{
		return end - start;
	}

	glm::vec2 Center() const
	{
		return (start + end) * 0.5f;
	}

	bool Contains(const glm::vec2& point) const
	{
		return point.x >= start.x && point.x <= end.x &&
			point.y >= start.y && point.y <= end.y;
	}

	bool Intersects(const Rect& other) const
	{
		return !(other.start.x > end.x || other.end.x < start.x ||
			other.start.y > end.y || other.end.y < start.y);
	}
};