#include "stdafx.h"

#include "Input.h"
#include "Gamestate.h"

Input::Input() {}

Input& Input::GetInstance()
{
	static Input instance;

	return instance;
}

void Input::Initialise(ALLEGRO_DISPLAY *_display)
{
	ResetButtons();
	ResetUpButtons();
	ResetDownButtons();
	ResetKeys();
	ResetUpKeys();
	ResetDownKeys();
	ResetKeyBindStatus();

	m_displayClose = false;

	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_R, RELOAD));
	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_E, INTERACT));
	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_SPACE, FIRE));
	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_UP, MOVE_FORWARD));
	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_DOWN, MOVE_BACKWARD));
	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_LEFT, STRAFE_LEFT));
	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_RIGHT, STRAFE_RIGHT));
	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_W, MOVE_FORWARD));
	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_A, TURN_LEFT));
	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_S, MOVE_BACKWARD));
	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_D, TURN_RIGHT));
	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_LCTRL, CROUCH));
	m_keyMaps.insert(std::pair<int, Keybinding>(ALLEGRO_KEY_ALT, PRONE));

	m_eventQueue = al_create_event_queue();

	al_install_keyboard();
	al_install_mouse();

	//========================================
	//LOADING EVENT SOURCES & START TIMER
	//========================================

	al_register_event_source(m_eventQueue, al_get_keyboard_event_source());
	al_register_event_source(m_eventQueue, al_get_mouse_event_source());
}

bool Input::CheckForInput()
{
	bool eventHappened = false;

	ResetUpButtons();
	ResetDownButtons();
	ResetUpKeys();
	ResetDownKeys();
	m_pressedKeys.clear();

	m_displayClose = false;

	while (al_get_next_event(m_eventQueue, &m_event))
	{
		switch (m_event.type)
		{
			case ALLEGRO_EVENT_KEY_CHAR:
			{
				m_pressedKeys.push_back(m_event.keyboard.unichar);
			}
			/// Intentional break missing
			case ALLEGRO_EVENT_KEY_DOWN:
			{
				m_keysDown[m_event.keyboard.keycode] = true;
				m_keys[m_event.keyboard.keycode] = true;
				
				if (CheckIfBound(m_event.keyboard.keycode))
				{
					m_events[m_keyMaps[m_event.keyboard.keycode]] = true;
				}
			}
			break;
			case ALLEGRO_EVENT_KEY_UP:
			{
				m_keysUp[m_event.keyboard.keycode] = true;
				m_keys[m_event.keyboard.keycode] = false;

				if (CheckIfBound(m_event.keyboard.keycode))
				{
					m_events[m_keyMaps[m_event.keyboard.keycode]] = false;
				}
			}
			break;
			case ALLEGRO_EVENT_MOUSE_AXES:
			{
				m_mousePos.x = m_event.mouse.x;
				m_mousePos.y = m_event.mouse.y;

				m_mouseMovement.x = m_event.mouse.dx / m_mouseMoveLimit;
				m_mouseMovement.y = m_event.mouse.dy / m_mouseMoveLimit;
			}
			break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			{
				m_mouseButtons[m_event.mouse.button - 1] = true;
				m_mouseButtonsDown[m_event.mouse.button - 1] = true;
			}
			break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			{
				m_mouseButtons[m_event.mouse.button - 1] = false;
				m_mouseButtonsUp[m_event.mouse.button - 1] = true;
			}
			break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
			{
				m_displayClose = true;
			}
			break;
			default:;
		}
	}

	return true;
}

Vec2 Input::GetMouseAxis()
{
	return m_mousePos;
}

Vec2 Input::GetCursorScreenPos()
{
	// Not implemented yet
	return Vec2();
}

Vec2 Input::GetCursorWindowPos()
{
	// Not implemented yet
	return Vec2();
}

Vec2 Input::GetGamePadAxis()
{
	// Not implemented yet
	return Vec2();
}


/// ++++++++++++++++++++++++
/// Mouse functions
/// ++++++++++++++++++++++++

////
/// Returns whether the given button is pressed
bool Input::GetButton(int _button)
{
	return m_mouseButtons[_button];
}

//// Returns whether the given button was released this frame
bool Input::GetButtonUp(int _button)
{
	return m_mouseButtonsUp[_button];
}

//// Returns whether the given button was pressed this frame
bool Input::GetButtonDown(int _button)
{
	return m_mouseButtonsDown[_button];
}

//// Returns normalised mouse movement for this frame
glm::vec2 Input::GetMouseMovement()
{
	return m_mouseMovement;
}

/// ++++++++++++++++++++++
/// Keyboard functions
/// ++++++++++++++++++++++

//// Returns whether the given key is pressed
bool Input::GetKey(int _keycode)
{
	return m_keys[_keycode];
}

//// Returns whether the given key was released this frame
bool Input::GetKeyUp(int _keycode)
{
	return m_keysUp[_keycode];
}

//// Returns whether the given key was pressed this frame
bool Input::GetKeyDown(int _keycode)
{
	return m_keysDown[_keycode];
}

/// Returns all keys pressed down that frame
std::vector<int>& Input::GetKeysPressed()
{
	return m_pressedKeys;
}

//// Returns whether the given event was triggered this frame
bool Input::CheckEvent(Keybinding _event)
{
	return m_events[_event];
}

bool Input::CheckDisplayClose()
{
	return m_displayClose;
}

void Input::ReassignKeybind(Keybinding _bind, int _keycode)
{
	if (CheckIfBound(_keycode))
	{
		m_keyMaps[_keycode] = _bind;
	}

	else
		m_keyMaps.insert(std::pair<int, Keybinding>(_keycode, _bind));
}

/// Reset mouse input functions

void Input::ResetMouseInput()
{
	ResetButtons();
	ResetDownButtons();
	ResetUpButtons();
}

void Input::ResetButtons()
{
	for (int i = 0; i < 5; i++)
	{
		m_mouseButtons[i] = false;
	}
}

void Input::ResetUpButtons()
{
	for (int i = 0; i < 5; i++)
	{
		m_mouseButtonsUp[i] = false;
	}
}

void Input::ResetDownButtons()
{
	for (int i = 0; i < 5; i++)
	{
		m_mouseButtonsDown[i] = false;
	}
}

/// Reset keyboard input functions

void Input::ResetKeyboardInput()
{
	ResetKeys();
	ResetDownKeys();
	ResetUpKeys();
	m_pressedKeys.clear();
}

void Input::ResetKeys()
{
	for (int i = 0; i < 255; i++)
	{
		m_keys[i] = false;
	}
}

void Input::ResetUpKeys()
{
	for (int i = 0; i < 255; i++)
	{
		m_keysUp[i] = false;
	}
}

void Input::ResetDownKeys()
{
	for (int i = 0; i < 255; i++)
	{
		m_keysDown[i] = false;
	}
}

void Input::ResetKeyBindStatus()
{
	for (int i = 0; i < MAX_KEYBINDINGS; i++)
	{
		m_events[i] = false;
	}
}

// Checks if the given key is bound to an action e.g. shoot, jump etc
bool Input::CheckIfBound(int _keycode)
{
	for each (std::pair<int, Keybinding> bind in m_keyMaps)
	{
		if (m_event.keyboard.keycode == bind.first)
		{
			m_events[bind.second] = true;
			return true;
		}
	}

	return false;
}

void Input::Shutdown()
{
	al_destroy_event_queue(m_eventQueue);
}

Input::~Input() {}
