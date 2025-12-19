#include "pch.h"
#include "ShapeRenderer.h"


void ShapeRenderer::FillRect(Vector2 Center, Vector2 Size, Vector4 color)
{
	FillRect(Center, Size, 0, color);
}

void ShapeRenderer::FillRect(Vector2 Center, Vector2 Size, float rotation, Vector4 color)
{
	m_rectShapes.push_back(RectShape(Center, Size, rotation));
	m_drawCalls.push_back(ShapeDrawCall(ShapeBuffers::RectBuffer, color));
}

std::optional<ShapeDrawCall> ShapeRenderer::PopDrawCall()
{
	if (m_drawCalls.size() < 1)
		return std::nullopt;
	ShapeDrawCall call = m_drawCalls.back();
	m_drawCalls.pop_back();
	return call;
}

RectShape ShapeRenderer::PopRectShape()
{
	RectShape rect = m_rectShapes.back();
	m_rectShapes.pop_back();
	return rect;
}
