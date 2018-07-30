#include "stdafx.h"

#include "Options.h"
#include "Resources.h"
#include "Core.h"
#include "Input.h"
#include "Button.h"


Options::Options() {}

void Options::Start()
{
	m_cursorBMP = Resources::GetInstance().LoadBmp("Cursor.png");
	m_font = Resources::GetInstance().LoadFont("Arial.ttf", 50);

	m_cursor = al_create_mouse_cursor(m_cursorBMP.GetBitmap(), 0, 0);
	al_set_mouse_cursor(Core::GetInstance().GetDisplay(), m_cursor);
	al_show_mouse_cursor(Core::GetInstance().GetDisplay());

	Resources::GetInstance().GetVolumes(m_masVol, m_musVol, m_sfxVol);
	Core::GetInstance().GetDisplaySize();

	m_masterVolume = new Slider(Vec2(0.3, 0.4), 0.4, m_masVol, "Master Volume");
	m_musicVolume = new Slider(Vec2(0.3, 0.5), 0.4, m_musVol, "Music Volume");
	m_sfxVolume = new Slider(Vec2(0.3, 0.6), 0.4, m_sfxVol, "SFX Volume");

	m_yes = new RectButton("Yes", Colour(255,0,0,255), "Arial.ttf", 45, Vec2(0.425, 0.725), 0.09, 0.06, Colour(80, 80, 255, 255));
	m_no = new RectButton("No", Colour(255,0,0,255), "Arial.ttf", 45, Vec2(0.575, 0.725), 0.09, 0.06, Colour(80, 80, 255, 255));
}

bool Options::Update()
{
	// Checks if master volume slider has been moved
	if(m_masterVolume->Update())
	{
		Resources::GetInstance().SetMasterGain(m_masterVolume->GetCurrentValue());
	}

	// Checks if music volume slider has been moved
	else if(m_musicVolume->Update())
	{
		Resources::GetInstance().SetMusicGain(m_musicVolume->GetCurrentValue());
	}

	// Checks if SFX volume slider has been moved
	else if(m_sfxVolume->Update())
	{
		Resources::GetInstance().SetSFXGain(m_sfxVolume->GetCurrentValue());
	}

	// Confirms volume changes
	if(m_yes->Update())
	{
		Core::GetInstance().GetStateManager().RemoveLastState();
	}

	// Reverts volumes levels to previous
	else if(m_no->Update())
	{
		Resources::GetInstance().SetMasterGain(m_masVol);
		Resources::GetInstance().SetMusicGain(m_musVol);
		Resources::GetInstance().SetSFXGain(m_sfxVol);
		Core::GetInstance().GetStateManager().RemoveLastState();
	}

	if(Input::GetInstance().GetKeyDown(ALLEGRO_KEY_ESCAPE))
	{
		Core::GetInstance().GetStateManager().RemoveLastState();
	}

	return true;
}

void Options::Render()
{
	al_draw_filled_rounded_rectangle(0.25 * m_defWinWidth, 0.25 * m_defWinHeight, 0.75 * m_defWinWidth, 0.80 * m_defWinHeight, 15, 15, al_map_rgb(255,200,255));
	al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.275 * m_defWinHeight, ALLEGRO_ALIGN_CENTRE, "Options");
	al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.63 * m_defWinHeight, ALLEGRO_ALIGN_CENTRE, "Confirm Changes?");

	m_masterVolume->Render();
	m_musicVolume->Render();
	m_sfxVolume->Render();

	m_yes->Render();
	m_no->Render();
}

void Options::Shutdown()
{
	delete m_masterVolume;
	delete m_musicVolume;
	delete m_sfxVolume;

	delete m_yes;
	delete m_no;
}

Options::~Options() {}