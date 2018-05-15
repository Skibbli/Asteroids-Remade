#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include "stdafx.h"


class Gamestate;

class GamestateManager
{
	public:
		//Constructor and destructor
		GamestateManager();
		~GamestateManager();

		//Functions to change, add and remove gamestates
		void ChangeState(Gamestate *_state);
		void AddState(Gamestate *_state);
		void RemoveLastState();

		//Functions that call update and render on the active gamestate
		bool Update();
		void Render();

private:
	std::vector <Gamestate*> m_gameStates;
};

#endif