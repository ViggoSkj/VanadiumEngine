#include "ButtonElement.h"

void ButtonElement::Awake()
{
	m_screenElementHandle = Vanadium::ECS::CreateHandle(*GetEntity().GetComponent<ScreenElement>());
}

ScreenElement& ButtonElement::GetScreenElement()
{
	return m_screenElementHandle.Get();
}