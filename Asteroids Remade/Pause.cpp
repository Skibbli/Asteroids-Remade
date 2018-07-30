#include "stdafx.h"

#include "Pause.h"
#include "Core.h"
#include "Resources.h"
#include "Button.h"
#include "Fade.h"
#include "Options.h"
#include "Input.h"


Pause::Pause()
{
	m_menuQuit = false;
	m_gameQuit = false;
}

void Pause::Start()
{
	//m_background = Resources::GetInstance().LoadBmp("SpaceBG.png");
	m_cursorBMP = Resources::GetInstance().LoadBmp("Cursor.png");
	m_font = Resources::GetInstance().LoadFont("Arial.ttf", 50);

	m_cursor = al_create_mouse_cursor(m_cursorBMP.GetBitmap(), 0, 0);
	al_set_mouse_cursor(Core::GetInstance().GetDisplay(), m_cursor);
	al_show_mouse_cursor(Core::GetInstance().GetDisplay());

	m_optBut = new RectButton("Options", Colour(255,0,0,255), "Arial.ttf", 45, Vec2(0.5, 0.32), 0.35, 0.10, Colour(80, 80, 255, 255));
	m_contBut = new RectButton("Continue", Colour(255,0,0,255), "Arial.ttf", 45, Vec2(0.5, 0.44), 0.35, 0.10, Colour(80, 80, 255, 255));

	m_menuQuitBut = new RectButton("Quit to Menu", Colour(255,0,0,255), "Arial.ttf", 45, Vec2(0.5, 0.56), 0.35, 0.10, Colour(80, 80, 255, 255));
	m_menuQuitYesBut = new RectButton("Yes", Colour(255,0,0,255), "Arial.ttf", 45, Vec2(0.445, 0.54), 0.09, 0.06, Colour(80, 80, 255, 255));
	m_menuQuitNoBut = new RectButton("No", Colour(255,0,0,255), "Arial.ttf", 45, Vec2(0.555, 0.54), 0.09, 0.06, Colour(80, 80, 255, 255));

	m_gameQuitBut = new RectButton("Quit to Desktop", Colour(255,0,0,255), "Arial.ttf", 45, Vec2(0.5, 0.68), 0.35, 0.10, Colour(80, 80, 255, 255));
	m_gameQuitYesBut = new RectButton("Yes", Colour(255,0,0,255), "Arial.ttf", 45, Vec2(0.445, 0.54), 0.09, 0.06, Colour(80, 80, 255, 255));
	m_gameQuitNoBut = new RectButton("No", Colour(255,0,0,255), "Arial.ttf", 45, Vec2(0.555, 0.54), 0.09, 0.06, Colour(80, 80, 255, 255));
}

bool Pause::Update()
{
	Vec2 mousePos = Input::GetInstance().GetMouseAxis();

	// If neither quit button has been clicked
	if(!m_menuQuit && !m_gameQuit)
	{
		if(m_optBut->Update())
		{
			Core::GetInstance().GetStateManager().AddState(std::make_shared<Options>());
			return true;
		}

		if(m_contBut->Update())
		{
			Core::GetInstance().GetStateManager().RemoveLastState();
			return true;
		}

		if(Input::GetInstance().GetKeyDown(ALLEGRO_KEY_ESCAPE))
		{
			Core::GetInstance().GetStateManager().RemoveLastState();
			return true;
		}

		if(m_menuQuitBut->Update())
		{
			m_menuQuit = true;
			return true;
		}

		if(m_gameQuitBut->Update())
		{
			m_gameQuit = true;
			return true;
		}
	}

	// If menuQuit button has been clicked
	if(m_menuQuit)
	{
		if(m_menuQuitYesBut->Update())
		{
			Core::GetInstance().GetStateManager().AddState(std::make_shared<Fade>(Enums::COLOUR::BLACK, 0.5, false, Enums::GAMESTATE::TITLE));
		}

		else if(m_menuQuitNoBut->Update())
		{
			m_menuQuit = false;
		}
	}

	// If game quit button has been clicked
	if(m_gameQuit)
	{
		if(m_gameQuitYesBut->Update())
		{
			return false;
		}

		else if(m_gameQuitNoBut->Update())
		{
			m_gameQuit = false;
		}
	}

	return true;
}

void Pause::Render()
{
	al_draw_filled_rounded_rectangle(0.285 * m_defWinWidth, 0.175 * m_defWinHeight, 0.715 * m_defWinWidth, 0.75 * m_defWinHeight, 15, 15, al_map_rgb(255,200,255));
	al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.2 * m_defWinHeight, ALLEGRO_ALIGN_CENTRE, "Paused");

	m_optBut->Render();
	m_contBut->Render();
	m_menuQuitBut->Render();
	m_gameQuitBut->Render();

	// If menuQuit button has been clicked
	if(m_menuQuit)
	{
		al_draw_filled_rounded_rectangle(0.308 * m_defWinWidth, 0.42 * m_defWinHeight, 0.692 * m_defWinWidth, 0.6 * m_defWinHeight, 15, 15, al_map_rgb(255,100,255));
		al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.44 * m_defWinHeight, ALLEGRO_ALIGN_CENTRE, "Quit to Menu?");

		m_menuQuitYesBut->Render();
		m_menuQuitNoBut->Render();
	}

	// If game quit button has been clicked
	if(m_gameQuit)
	{
		al_draw_filled_rounded_rectangle(0.295 * m_defWinWidth, 0.42 * m_defWinHeight, 0.705 * m_defWinWidth, 0.6 * m_defWinHeight, 15, 15, al_map_rgb(255,100,255));
		al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.44 * m_defWinHeight, ALLEGRO_ALIGN_CENTRE, "Quit to Desktop?");

		m_menuQuitYesBut->Render();
		m_menuQuitNoBut->Render();
	}
}

void Pause::Shutdown() {}

Pause::~Pause()
{
	delete m_optBut;
	delete m_contBut;
	 
	delete m_menuQuitBut;
	delete m_menuQuitYesBut;
	delete m_menuQuitNoBut;
	 
	delete m_gameQuitBut;
	delete m_gameQuitYesBut;
	delete m_gameQuitNoBut;
}