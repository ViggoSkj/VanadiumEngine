#pragma once
#include "pch.h"
#include "Key.h"

namespace Vanadium
{
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
		bool m_leftShiftDown = false;
		bool m_leftCtrlDown = false;
		bool m_leftAltDown = false;

		KeyState m_keyStates[Key::_LAST];
	};
}