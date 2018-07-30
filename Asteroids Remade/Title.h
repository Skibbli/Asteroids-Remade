#ifndef TITLE_H
#define TITLE_H

#include "stdafx.h"

#include "Gamestate.h"


class CircleButton;
class RectButton;

class Title : public Gamestate
{
	public:
		Title();
		~Title();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

	private:
		RectButton* m_startButton;
		RectButton* m_hiScoresButton;
		RectButton* m_quitButton;

		Bitmap m_cursorBMP;
		ALLEGRO_MOUSE_CURSOR *m_cursor;

		weak<ALLEGRO_FONT> m_font72;
};

#endif