#pragma once
#include "Key.h"

class InputManager
{
public:
	InputManager();

	void ReportNewKeyStates(bool keys[Key::_LAST]);

	KeyState GetKey(Key key) const
	{
		return m_keyStates[key];
	}

	bool Down(Key key) const
	{
		return m_keyStates[key] == KeyState::Pressed || m_keyStates[key] == KeyState::Down;
	}

	const bool& ShiftDown = m_leftShiftDown;
	const bool& AltDown = m_leftAltDown;
	const bool& CtrlDown = m_leftCtrlDown;

private:
	bool m_leftShiftDown;
	bool m_leftCtrlDown;
	bool m_leftAltDown;

	KeyState m_keyStates[Key::_LAST];
};