#include "stdafx.h"

#include "Gamestate.h"
#include "GamestateManager.h"


class Fade : public Gamestate
{
	public:
		Fade(GamestateManager *_manager, ALLEGRO_DISPLAY *_display, COLOUR _col, int _fadeLength);
		~Fade();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

	private:
		int m_fadeLength;
};