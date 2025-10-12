#include "pch.h"
#include "InputManager.h"
#include <iostream>

InputManager::InputManager()
{
	for (int i = 0; i < Key::_LAST; i++)
	{
		m_keyStates[i] = KeyState::Up;
	}
}

void InputManager::ReportNewKeyStates(bool keys[Key::_LAST])
{
	for (int i = 0; i < Key::_LAST; i++)
	{
		KeyState other = m_keyStates[i];
		if (keys[i])
		{
			if (other == KeyState::Pressed)
				m_keyStates[i] = KeyState::Down;
			if (other == KeyState::Released || other == KeyState::Up)
				m_keyStates[i] = KeyState::Pressed;
		}
		else
		{
			if (other == KeyState::Released)
				m_keyStates[i] = KeyState::Up;
			if (other == KeyState::Pressed || other == KeyState::Down)
				m_keyStates[i] = KeyState::Released;
		}
	}

	m_leftShiftDown = Down(Key::LeftShift);
	m_leftCtrlDown = Down(Key::LeftCtrl);
	m_leftAltDown = Down(Key::LeftAlt);
}