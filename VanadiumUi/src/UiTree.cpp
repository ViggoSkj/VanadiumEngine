#include "UiTree.h"
#include "ECS.h"
#include "TextElement.h"

// returns the highest available y position
i32 BlockLine(UiNode* parent, UiNode* previous)
{
	if (previous == nullptr)
		return parent->resolvedProperties.box.position.y +
		parent->resolvedProperties.box.border.top +
		parent->resolvedProperties.box.padding.top;

	if (previous->style.display == Style::Block)
		return previous->resolvedProperties.box.Full().y + previous->resolvedProperties.box.position.y;

	return previous->resolvedProperties.box.position.y;
}

i32 StartLine(UiNode* parent, UiNode* previous)
{
	if (previous == nullptr || previous->style.display == Style::Block)
		return parent->resolvedProperties.box.position.x +
		parent->resolvedProperties.box.border.left +
		parent->resolvedProperties.box.padding.left;

	return previous->resolvedProperties.box.position.x + previous->resolvedProperties.box.Full().x;
}

Vector2I TryPosition(UiNode* parent, UiNode* previous)
{
	return Vector2I(StartLine(parent, previous), BlockLine(parent, previous));
}

i32 MesurementToPixels(Mesurement mesurement, float full)
{
	if (mesurement.unit == StyleUnit::Pixel)
		return mesurement.number;
	else if (mesurement.unit == StyleUnit::Fraction)
		return full * mesurement.number;
}

BoxDirections<i32> MesurementToPixels(BoxDirections<Mesurement> mesurement, Vector2 full)
{
	BoxDirections<i32> result;
	result.top = MesurementToPixels(mesurement.top, full.y);
	result.right = MesurementToPixels(mesurement.right, full.x);
	result.bottom = MesurementToPixels(mesurement.bottom, full.y);
	result.left = MesurementToPixels(mesurement.left, full.x);
	return result;
}

void CalculateLayout(UiTree& tree)
{
	std::vector<std::shared_ptr<UiNode>> nodes = tree.GetNodes();

	for (u32 i = 0; i < 3; i++)
	{
		UiNode* previous = nullptr;
		for (auto nodePtr : nodes)
		{
			UiNode& node = *nodePtr;
			ResolvedStyle& style = node.style;

#define PARENT_CONTENT (node.parent == nullptr ? tree.screenResolution : node.parent->resolvedProperties.box.content)

			if (previous != nullptr && previous->parent != node.parent)
				previous = nullptr;

			node.resolvedProperties.box.padding = MesurementToPixels(style.padding, PARENT_CONTENT);
			node.resolvedProperties.box.border = MesurementToPixels(style.border, PARENT_CONTENT);

			if (style.display == Style::Block)
			{
				if (style.position == Style::Absolute)
				{
					if (style.widthAuto)
					{
						node.resolvedProperties.box.AdjustSize(Vector2I(
							PARENT_CONTENT.x - MesurementToPixels(style.margin, PARENT_CONTENT).Horizontal(),
							MesurementToPixels(style.height, PARENT_CONTENT.y)
						));
					}
					else
					{
						node.resolvedProperties.box.AdjustSize(Vector2I(
							MesurementToPixels(style.width, PARENT_CONTENT.x),
							MesurementToPixels(style.height, PARENT_CONTENT.y)
						));
					}

					if (style.xPosition.rule == Rule::Unset)
					{
						node.resolvedProperties.box.position = Vector2(
							MesurementToPixels(style.margin.left, PARENT_CONTENT.x),
							MesurementToPixels(style.yPosition, PARENT_CONTENT.y)
						);
					}
					else
					{
						node.resolvedProperties.box.position = Vector2(
							MesurementToPixels(style.xPosition.value, PARENT_CONTENT.x),
							MesurementToPixels(style.yPosition, PARENT_CONTENT.y)
						);
					}

					if (style.heightAuto)
					{
						i32 yContentTop = node.children.back()->resolvedProperties.box.position.y + node.children.back()->resolvedProperties.box.Visible().y - node.children.front()->resolvedProperties.box.position.y;
						i32 marginTop = node.children.front()->resolvedProperties.box.margin.top;
						i32 marginBottom = node.children.back()->resolvedProperties.box.margin.bottom;

						marginTop = std::max(0, marginTop - node.resolvedProperties.box.padding.top);
						marginBottom = std::max(0, marginBottom - node.resolvedProperties.box.padding.bottom);

						node.resolvedProperties.box.content.y = marginTop + yContentTop + marginBottom;
					}
				}

				if (style.position == Style::Flow)
				{
					assert(node.parent != nullptr);

					node.resolvedProperties.box.AdjustSize(Vector2I(
						MesurementToPixels(style.width, PARENT_CONTENT.x),
						MesurementToPixels(style.height, PARENT_CONTENT.y)
					));

					if (style.widthAuto)
					{
						float availableWidth = node.parent->resolvedProperties.box.content.x;
						node.resolvedProperties.box.AdjustSize(Vector2I(availableWidth, node.resolvedProperties.box.Visible().y));
					}

					if (style.marginAuto.left && style.marginAuto.right)
					{
						float availableWidth = PARENT_CONTENT.x - node.resolvedProperties.box.Visible().x;
						node.resolvedProperties.box.margin.left = availableWidth / 2;
						node.resolvedProperties.box.margin.right = availableWidth / 2;
					}

					node.resolvedProperties.box.margin.top = MesurementToPixels(style.margin.top, node.parent->resolvedProperties.box.content.y);
					node.resolvedProperties.box.margin.bottom = MesurementToPixels(style.margin.bottom, node.parent->resolvedProperties.box.content.y);

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
			}
			else if (style.display == Style::Inline)
			{
				Vector2I start = TryPosition(node.parent.get(), previous);
				node.resolvedProperties.box.position = start;
				node.resolvedProperties.box.AdjustSize(Vector2I(
					MesurementToPixels(style.width, PARENT_CONTENT.x),
					MesurementToPixels(style.height, PARENT_CONTENT.y)
				));;

				if (node.resolvedProperties.box.RightVisible() >= node.parent->resolvedProperties.box.RightContent())
				{
					start.x = StartLine(node.parent.get(), nullptr);
					start.y += MesurementToPixels(node.style.height, node.parent->resolvedProperties.box.content.y);
					node.resolvedProperties.box.position = start;
				}
			}

			previous = &node;
		}
	}

	for (auto nodePtr : nodes)
	{
		UiNode& node = *nodePtr;
		if (node.transform.IsEmpty())
			continue;

		ScreenElement& t = node.transform.Get();
		t.box = node.resolvedProperties.box;
	}
}

void ResolveChildren(std::shared_ptr<UiNode> node)
{
	if (node->transform.IsEmpty())
		return;

	auto children = node->transform.Get().GetChildren();

	for (auto& child : children)
	{
		std::shared_ptr<UiNode> childNode = std::make_shared<UiNode>();
		childNode->transform = Vanadium::ECS::CreateHandle(*child);
		childNode->style = child->style;
		childNode->parent = node;

		if (TextElement* textElement = child->GetEntity().GetComponent<TextElement>())
		{
			TextProperties props = TextProperties{
				textElement->symbolRenderer,
				textElement->text
			};

			for (char c : props.text)
			{
				std::shared_ptr<UiNode> cNode = std::make_shared<UiNode>();
				cNode->parent = childNode;
				cNode->style.display = Style::Inline;
				Vector2 size = textElement->symbolRenderer->Sheet()->GetSymbolSize(c, 16);
				cNode->style.width = Mesurement(size.x, StyleUnit::Pixel);
				cNode->style.height = Mesurement(size.y, StyleUnit::Pixel);

				childNode->children.push_back(cNode);
			}

			childNode->special.variant = props;
		}
		else
		{
			ResolveChildren(childNode);
		}

		node->children.push_back(childNode);
	}
}

std::vector<std::shared_ptr<UiNode>> UiTree::GetNodes()
{
	if (root == nullptr)
		return {};

	std::vector<std::shared_ptr<UiNode>> nodes = { root };

	i32 lastLayerIndex = 0;

	// bfs
	while (lastLayerIndex < nodes.size())
	{
		i32 newLast = nodes.size();
		for (i32 i = lastLayerIndex; i < newLast; i++)
			for (auto& child : nodes[i]->children)
				nodes.push_back(child);
		lastLayerIndex = newLast;
	}

	return nodes;
}