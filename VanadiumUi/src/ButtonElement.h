#pragma once
#include "Core.h"
#include "ScreenElement.h"

class ButtonElement : public Component
{
public:
	using Component::Component;

	void Awake() override;

	ScreenElement& GetScreenElement();
	
private:
	Vanadium::ComponentHandle<ScreenElement> m_screenElementHandle;
};