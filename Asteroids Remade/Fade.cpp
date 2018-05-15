#include "stdafx.h"

#include "Fade.h"
#include "Input.h"

Fade::Fade(GamestateManager *_manager, ALLEGRO_DISPLAY *_display, COLOUR _col, int _fadeLength)
{
	m_stateManager = _manager;
	m_display = _display;
}

void Fade::Start()
{
	//al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
}

bool Fade::Update()
{
	if (Input::GetButtonDown(0))
	{
		m_stateManager->RemoveLastState();
	}

	return true;
}

void Fade::Render()
{
	al_draw_filled_rectangle(0, 0, 1000, 1000, al_map_rgba_f(0.5, 0.5, 0.5, 0.2));
}

void Fade::Shutdown()
{

}

Fade::~Fade()
{

}