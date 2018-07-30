#include "stdafx.h"

#include "GamestateManager.h"
#include "Gamestate.h"


GamestateManager::GamestateManager()
{
	m_addState = false;
	m_changeState = false;

	m_bitmap = nullptr;
}

//Deletes all previous states and adds provided state to the list
//Used if new state is to be the main state and the previous state
//is no longer required e.g. from menu to playing a level
void GamestateManager::ChangeState(shared<Gamestate> _state)
{
	m_changeState = true;
	m_nextState = _state;

	for (unsigned int i = 0; i < m_gameStates.size(); i++)
	{
		m_gameStates.at(i).get()->Shutdown();
	}

	m_gameStates.clear();

	m_gameStates.push_back(m_nextState);
	m_nextState->Start();
}

//Adds the provided state to the list of states
void GamestateManager::AddState(shared<Gamestate> _state)
{
	if(m_bitmap == nullptr)
	{
		m_bitmap = al_create_bitmap(1000,1000);
	}

	m_addState = true;
	m_nextState = _state;

	m_gameStates.push_back(m_nextState);
	m_nextState->Start();
}

//Removes the last state added to the list of states
void GamestateManager::RemoveLastState()
{
	m_gameStates.back().get()->Shutdown();
	m_gameStates.pop_back();
}

//Checks if there is a state in the list and if there is calls update
//function from that state. If that update loop returns false it means
//the game has been quit and this is then conveyed to the main game loop.
//If quit is not initiated the function returns false and play continues
bool GamestateManager::Update()
{
	bool gameRunning = true;

	if (m_gameStates.size() > 0)
	{
		gameRunning = m_gameStates.back()->Update();
	}

	else if (m_addState || m_changeState)
	{
		gameRunning = true;
	}

	else
		gameRunning = false;

	return gameRunning;
}

//Calls draw on all states in the list. Draws to a blank bitmap and then scales that bitmap to the window size
void GamestateManager::Render()
{
	al_set_target_bitmap(m_bitmap);

	for (unsigned int i = 0; i < m_gameStates.size(); i++)
	{
		m_gameStates.at(i)->Render();
	}

	al_set_target_bitmap(al_get_backbuffer(m_display));

	al_draw_scaled_bitmap(m_bitmap, 0, 0, 1000, 1000, 0 + m_displaySize.s_wOffset, 0 + m_displaySize.s_hOffset, m_displaySize.s_width - 2 * m_displaySize.s_wOffset, m_displaySize.s_height - 2 * m_displaySize.s_hOffset, NULL);

	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void GamestateManager::SetDisplay(ALLEGRO_DISPLAY* _display)
{
	m_display = _display;
}

void GamestateManager::UpdateDisplaySize(DisplayInfo &_displaySize)
{
	m_displaySize = _displaySize;
}

void GamestateManager::Shutdown()
{
	for (unsigned int i = 0; i < m_gameStates.size(); i++)
	{
		m_gameStates.at(i)->Shutdown();
	}

	m_gameStates.clear();

	al_destroy_bitmap(m_bitmap);
	m_display = NULL;
}

// Destructor - cleans up list of states by calling delete on each
// state in the list
GamestateManager::~GamestateManager()
{
	for (unsigned int i = 0; i < m_gameStates.size(); i++)
	{
		m_gameStates.at(i)->Shutdown();
	}

	m_gameStates.clear();
}