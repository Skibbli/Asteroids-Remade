#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "stdafx.h"

#include "ResourceStructs.h"


class Gamestate;

// Handles updates and rendering of gamestates
class GamestateManager
{
	public:
		//Constructor and destructor
		GamestateManager();
		~GamestateManager();

		//Functions to change, add and remove gamestates
		void ChangeState(shared<Gamestate> _state);
		void AddState(shared<Gamestate> _state);
		void RemoveLastState();
		void Shutdown();

		//Functions that call update and render on the active gamestate
		bool Update();
		void Render();

		void SetDisplay(ALLEGRO_DISPLAY* _display);
		void UpdateDisplaySize(DisplayInfo &_displaySize);

private:
	std::vector<shared<Gamestate>> m_gameStates;

	bool m_addState, m_changeState;

	shared<Gamestate> m_nextState;
	ALLEGRO_BITMAP* m_bitmap;

	ALLEGRO_DISPLAY* m_display;
	DisplayInfo m_displaySize;
};

#endif