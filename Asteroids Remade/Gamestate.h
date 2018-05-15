#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "stdafx.h"

#include "GamestateManager.h"


class Gamestate
{
	public:
		Gamestate();
		~Gamestate();

		virtual void Start() = 0;
		virtual bool Update() = 0;
		virtual void Render() = 0;
		virtual void Shutdown() = 0;

	protected:
		GamestateManager *m_stateManager;
		ALLEGRO_DISPLAY *m_display;

		weak<ALLEGRO_BITMAP> m_background;
		weak<ALLEGRO_BITMAP> m_cursor;

		/*ALLEGRO_EVENT m_event;
		ALLEGRO_EVENT_QUEUE *m_eventQueue;*/

	private:

};

#endif