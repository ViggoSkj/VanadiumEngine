#include "ScreenElement.h"

std::vector<ScreenElement*> ScreenElement::GetChildren()
{
	std::vector<ScreenElement*> handles;
	UnorderedVector<ScreenElement>& transforms = Application::Get().GetECS()->GetComponentStore<ScreenElement>()->GetComponents();
	for (auto& t : transforms)
	{
		if (t.Parent == *this)
			handles.push_back(&t);
	}

	return handles;
}