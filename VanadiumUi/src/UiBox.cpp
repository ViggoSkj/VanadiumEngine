#include "UiBox.h"

void UiBox::AdjustSize(Vector2I newVisible)
{
	Vector2 diff = newVisible - Visible();
	content += diff;

	assert(content.x >= 0);
	assert(content.y >= 0);
}

bool UiBox::InsideVisible(Vector2I point)
{
	return VisibleRect().Inside(point);
}

RectI UiBox::VisibleRect()
{
	Vector2I visible = Visible();
	return { position, position + visible };
}