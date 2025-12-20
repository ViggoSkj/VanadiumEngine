#pragma once
#include "pch.h"
#include "core/Util/Rect.h"
#include "core/Util/RotatableRect.h"
#include "Shapes/RectShape.h"
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

	std::optional<ShapeDrawCall> PopDrawCall();
	
	RectShape PopRectShape();
private:
	inline static ShapeRenderer* s_instance = nullptr;

	std::vector<RectShape> m_rectShapes;
	std::vector<ShapeDrawCall> m_drawCalls;
};

enum ShapeBuffers
{
	RectBuffer,
};