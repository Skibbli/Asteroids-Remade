#include "stdafx.h"

#include "Gamestate.h"
#include "Button.h"


class Title : public Gamestate
{
	public:
		Title(GamestateManager *_manager, ALLEGRO_DISPLAY *_display);
		~Title();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

	private:
		CircleButton m_circleButton;
		RectButton m_rectButton;
};