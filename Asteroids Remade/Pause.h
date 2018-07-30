#include "stdafx.h"

#include "Gamestate.h"



class RectButton;

class Pause : public Gamestate
{
	public:
		Pause();
		~Pause();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

	private:
		bool m_menuQuit;
		bool m_gameQuit;

		RectButton *m_optBut;
		RectButton *m_contBut;

		RectButton *m_menuQuitBut;
		RectButton *m_menuQuitYesBut;
		RectButton *m_menuQuitNoBut;

		RectButton *m_gameQuitBut;
		RectButton *m_gameQuitYesBut;
		RectButton *m_gameQuitNoBut;

		Bitmap m_cursorBMP;
		ALLEGRO_MOUSE_CURSOR *m_cursor;
		weak<ALLEGRO_FONT> m_font;
};