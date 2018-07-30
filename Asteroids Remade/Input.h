#ifndef INPUT_H
#define INPUT_H

#include "stdafx.h"

class Gamestate;

// Key bindings for typical game actions
enum Keybinding
{
	RELOAD, INTERACT, CROUCH, PRONE, JUMP, FIRE, MOVE_FORWARD, MOVE_BACKWARD, TURN_LEFT, TURN_RIGHT, STRAFE_LEFT, STRAFE_RIGHT,
	MAX_KEYBINDINGS
};

class Input
{
	public:
		static Input& GetInstance();

		// Initialises the Input module
		void Initialise(ALLEGRO_DISPLAY *_display);
		// Shuts down the Input module
		void Shutdown();

		// Checks for any input this frame
		bool CheckForInput();

		// Returns how much the mouse has moved since the last frame, between -1 and 1 for each axis
		Vec2 GetMouseAxis();
		// Returns the mouse position on the screen
		Vec2 GetCursorScreenPos();
		// Returns the mouse position on the Allegro window
		Vec2 GetCursorWindowPos();

		// Returns how much the mouse has moved since the last frame, between -1 and 1 for each axis
		Vec2 GetGamePadAxis();

		// Returns whether the given button is pressed
		bool GetButton(int _button);
		// Returns whether the given button was released that frame
		bool GetButtonUp(int _button);
		// Returns whether the given button was pressed that frame
		bool GetButtonDown(int _button);
		// Returns normalised mouse movement for the frame
		glm::vec2 GetMouseMovement();
		// Returns whether the given key is pressed
		bool GetKey(int _keycode);
		// Returns whether the given key was released that frame
		bool GetKeyUp(int _keycode);
		// Returns whether the given key was pressed that frame
		bool GetKeyDown(int _keycode);
		// Returns all keys pressed that frame
		std::vector<int>& GetKeysPressed();

		// Returns whether the key linked to the given event was pressed this frame
		bool CheckEvent(Keybinding _event);
		// Check if display is being closed
		bool CheckDisplayClose();
		// Reassign a keybinding
		void ReassignKeybind(Keybinding _bind, int _keycode);
	
	private:
		Input();
		~Input();

		// Resets mouse variables
		void ResetMouseInput();
		// Resets the Button array
		void ResetButtons();
		// Resets the Up Button array
		void ResetUpButtons();
		// Resets the Down Buttton array
		void ResetDownButtons();

		// Resets keyboard variables
		void ResetKeyboardInput();
		// Resets the Key array
		void ResetKeys();
		// Resets the Up Key array
		void ResetUpKeys();
		// Resets the Down Key array
		void ResetDownKeys();

		// Resets the array tracking if a keybind has been input
		void ResetKeyBindStatus();

		// Checks if the given key is bound to an event
		bool CheckIfBound(int _keycode);

		Vec2 m_mousePos;
		float m_mouseMoveLimit;
		Vec2 m_mouseMovement;
		bool m_mouseButtons[5];
		bool m_mouseButtonsUp[5];
		bool m_mouseButtonsDown[5];
			 
		bool m_keys[255];
		bool m_keysUp[255];
		bool m_keysDown[255];
		std::map<int, Keybinding> m_keyMaps;
		bool m_events[Keybinding::MAX_KEYBINDINGS];
		bool m_displayClose;

		ALLEGRO_EVENT_QUEUE* m_eventQueue;
		ALLEGRO_EVENT m_event;

		std::vector<int> m_pressedKeys;
};

#endif