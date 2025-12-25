#pragma once
#include "pch.h"
#include "core/Util/Rect.h"
#include "core/Util/RotatableRect.h"
#include "Shapes/Shapes.h"
#include "ShapeDrawCall.h"


class ShapeRenderer
{
public:
	static ShapeRenderer* Get()
	{
		if (s_instance == nullptr)
			s_instance = new ShapeRenderer();
		return s_instance;
	}

	void FillRect(Vector2 Center, Vector2 Size, float rotation, Vector4 color);
	void FillRect(Vector2 Center, Vector2 Size, Vector4 color);
	void FillRect(Rect rect, float rotation, Vector4 color);
	void FillRect(Rect rect, Vector4 color);
	void FillRect(RotatableRect rect, Vector4 color);
	RectShape PopRectShape();

	void DrawArrow(Vector2 start, Vector2 end, Vector4 color);
	ArrowShape PopArrowShape();

	void FillCircle(Vector2 center, float radius, Vector4 color);
	CircleShape PopCircleShape();

	std::optional<ShapeDrawCall> PopDrawCall();
private:
	inline static ShapeRenderer* s_instance = nullptr;

	std::vector<RectShape> m_rectShapes;
	std::vector<ArrowShape> m_arrowShapes;
	std::vector<CircleShape> m_cirlceShapes;
	std::vector<ShapeDrawCall> m_drawCalls;
};

enum ShapeBuffers
{
	RectBuffer,
	ArrowBuffer,
	CirlceBuffer,
};