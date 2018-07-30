#include "stdafx.h"

#include "Gamestate.h"
#include "Slider.h"


class RectButton;

class Options : public Gamestate
{
	public:
		Options();
		~Options();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

	private:	
		Slider *m_masterVolume;
		Slider *m_musicVolume;
		Slider *m_sfxVolume;

		RectButton *m_yes;
		RectButton *m_no;

		float m_masVol, m_musVol, m_sfxVol;

		Bitmap m_cursorBMP;
		ALLEGRO_MOUSE_CURSOR *m_cursor;
		weak<ALLEGRO_FONT> m_font;
};