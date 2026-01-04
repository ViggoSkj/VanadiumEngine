#include "UiTree.h"
#include "ECS.h"
#include "TextElement.h"

void CalculateLayout(UiTree& tree)
{
	std::vector<UiNode*> nodes = tree.GetNodes();

	for (u32 i = 0; i < 3; i++)
	{
		UiNode* previous = nullptr;
		for (auto nodePtr : nodes)
		{
			UiNode& node = *nodePtr;
			Style& style = node.style;

			if (previous != nullptr && previous->parent != node.parent)
				previous = nullptr;

			node.resolvedProperties.box.padding = style.padding;
			node.resolvedProperties.box.border = style.border;

			if (style.position == Style::Absolute)
			{
				node.resolvedProperties.box.position = Vector2(style.xPosition, style.yPosition);
				node.resolvedProperties.box.AdjustSize(Vector2I(style.width, style.height));

				if (style.heightAuto)
				{
					i32 yContentTop = node.children.back().resolvedProperties.box.position.y + node.children.back().resolvedProperties.box.Visible().y - node.children.front().resolvedProperties.box.position.y;
					i32 marginTop = node.children.front().resolvedProperties.box.margin.top;
					i32 marginBottom = node.children.back().resolvedProperties.box.margin.bottom;

					marginTop = std::max(0, marginTop - node.resolvedProperties.box.padding.top);
					marginBottom = std::max(0, marginBottom - node.resolvedProperties.box.padding.bottom);

					node.resolvedProperties.box.content.y = marginTop + yContentTop + marginBottom;
				}
			}

			if (style.position == Style::Flow)
			{
				node.resolvedProperties.box.AdjustSize(Vector2I(style.width, style.height));

				if (style.widthAuto)
				{
					float availableWidth = node.parent->resolvedProperties.box.content.x;
					node.resolvedProperties.box.AdjustSize(Vector2I(availableWidth, node.resolvedProperties.box.Visible().y));
				}

				if (style.margin.marginAuto.left && style.margin.marginAuto.right)
				{
					float availableWidth = node.parent->resolvedProperties.box.content.x;
					availableWidth -= node.resolvedProperties.box.Visible().x;
					node.resolvedProperties.box.margin.left = availableWidth / 2;
					node.resolvedProperties.box.margin.right = availableWidth / 2;
				}

				node.resolvedProperties.box.margin.top = style.margin.margin.top;
				node.resolvedProperties.box.margin.bottom = style.margin.margin.bottom;

				if (node.parent != nullptr)
				{
					i32 paddingOverhead = 0;
					i32 minY = 0;
					i32 x = node.parent->resolvedProperties.box.position.x +
						node.parent->resolvedProperties.box.border.left +
						node.parent->resolvedProperties.box.padding.left;
					i32 prevMarginBottom = 0;

					if (previous != nullptr)
					{
						minY = previous->resolvedProperties.box.Visible().y + previous->resolvedProperties.box.position.y;
						prevMarginBottom = previous->resolvedProperties.box.margin.bottom;
					}
					else
					{
						minY = node.parent->resolvedProperties.box.position.y +
							node.parent->resolvedProperties.box.border.top +
							node.parent->resolvedProperties.box.padding.top;
						paddingOverhead = node.parent->resolvedProperties.box.padding.top;
					}

					i32 y = minY + std::max((std::max(prevMarginBottom, node.resolvedProperties.box.margin.top) - paddingOverhead), 0);
					x += node.resolvedProperties.box.margin.left;

					node.resolvedProperties.box.position = Vector2(x, y);
				}
			}

			previous = &node;
		}
	}

	for (auto nodePtr : nodes)
	{
		UiNode& node = *nodePtr;
		ScreenElement& t = node.transform.Get();
		t.box = node.resolvedProperties.box;
	}
}

void ResolveChildren(UiNode& node)
{
	if (node.transform.IsEmpty())
		return;

	auto children = node.transform.Get().GetChildren();

	for (auto& child : children)
	{
		UiNode childNode;
		childNode.transform = Vanadium::ECS::CreateHandle(*child);
		childNode.style = child->style;
		childNode.parent = &node;

		if (TextElement* textElement = child->GetEntity().GetComponent<TextElement>())
		{
			childNode.special.variant = TextProperties(textElement->text);
		}

		ResolveChildren(childNode);
		node.children.push_back(childNode);
	}
}

std::vector<UiNode*> UiTree::GetNodes()
{
	std::vector<UiNode*> nodes = { &root };

	i32 lastLayerIndex = 0;

	// bfs
	while (lastLayerIndex < nodes.size())
	{
		i32 newLast = nodes.size();
		for (i32 i = lastLayerIndex; i < nodes.size(); i++)
			for (auto& child : nodes[i]->children)
				nodes.push_back(&child);
		lastLayerIndex = newLast;
	}

	return nodes;
}