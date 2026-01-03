#include "UiTree.h"
#include "ECS.h"

void CalculateLayout(UiTree& tree)
{
	std::vector<UiNode*> nodes = { &tree.root };

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

			if (style.position == Style::Absolute)
			{
				node.resolvedProperties.box.position = Vector2(style.xPosition, style.yPosition);
				node.resolvedProperties.box.AdjustSize(Vector2I(style.width, style.height));

				if (style.heightAuto)
				{
					float goalBottom = node.children.back().resolvedProperties.box.position.y + node.children.back().resolvedProperties.box.Full().y;
					float bottom = node.resolvedProperties.box.position.y + 
						node.resolvedProperties.box.content.y +
						node.resolvedProperties.box.border.top +
						node.resolvedProperties.box.padding.top;

					node.resolvedProperties.box.content.y += goalBottom - bottom;
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
					i32 y = 0;
					i32 x = node.parent->resolvedProperties.box.position.x +
						node.parent->resolvedProperties.box.border.left +
						node.parent->resolvedProperties.box.padding.left;
					i32 prevMarginBottom = 0;

					if (previous != nullptr)
					{
						y = previous->resolvedProperties.box.Visible().y + previous->resolvedProperties.box.position.y;
						prevMarginBottom = previous->resolvedProperties.box.margin.bottom;
					}
					else
					{
						y = node.parent->resolvedProperties.box.position.y +
							node.parent->resolvedProperties.box.border.top +
							node.parent->resolvedProperties.box.padding.top;
					}

					y += std::max(prevMarginBottom, node.resolvedProperties.box.margin.top);
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