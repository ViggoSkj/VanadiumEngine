#include "pch.h"
#include "ShapeRenderer.h"


#pragma region Rect Shapes

void ShapeRenderer::FillRect(Vector2 Center, Vector2 Size, Vector4 color)
{
	FillRect(Center, Size, 0, color);
}
void ShapeRenderer::FillRect(Rect rect, float rotation, Vector4 color)
{
	FillRect(rect.Center(), rect.Size(), rotation, color);
}
void ShapeRenderer::FillRect(Rect rect, Vector4 color)
{
	FillRect(rect, 0, color);
}
void ShapeRenderer::FillRect(RotatableRect rect, Vector4 color)
{
	FillRect(rect.Rect, rect.Rotation, color);
}

void ShapeRenderer::FillRect(Vector2 Center, Vector2 Size, float rotation, Vector4 color)
{
	m_rectShapes.push_back(RectShape(Center, Size, rotation));
	m_drawCalls.push_back(ShapeDrawCall(ShapeBuffers::RectBuffer, color));
}

RectShape ShapeRenderer::PopRectShape()
{
	RectShape rect = m_rectShapes.back();
	m_rectShapes.pop_back();
	return rect;
}

#pragma endregion

#pragma region Arrow Shapes

void ShapeRenderer::DrawArrow(Vector2 start, Vector2 end, Vector4 color)
{
	m_arrowShapes.push_back(ArrowShape(start, end));
	m_drawCalls.push_back(ShapeDrawCall(ShapeBuffers::ArrowBuffer, color));
}

ArrowShape ShapeRenderer::PopArrowShape()
{
	ArrowShape rect = m_arrowShapes.back();
	m_arrowShapes.pop_back();
	return rect;
}

#pragma endregion

#pragma region Circle

void ShapeRenderer::FillCircle(Vector2 center, float radius, Vector4 color)
{
	m_drawCalls.push_back(ShapeDrawCall(ShapeBuffers::CirlceBuffer, color));
	m_cirlceShapes.push_back(CircleShape(center, radius));
}

CircleShape ShapeRenderer::PopCircleShape()
{
	CircleShape shape = m_cirlceShapes.back();
	m_cirlceShapes.pop_back();
	return shape;
}

#pragma endregion

std::optional<ShapeDrawCall> ShapeRenderer::PopDrawCall()
{
	if (m_drawCalls.size() < 1)
		return std::nullopt;
	ShapeDrawCall call = m_drawCalls.back();
	m_drawCalls.pop_back();
	return call;
}