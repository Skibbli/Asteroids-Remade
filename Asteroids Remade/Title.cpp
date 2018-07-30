#include "stdafx.h"

#include "Title.h"
#include "Level.h"
#include "Resources.h"
#include "Input.h"
#include "Core.h"
#include "Fade.h"
#include "HiScore.h"
#include "Button.h"


Title::Title() {}

void Title::Start()
{
	m_startButton = new RectButton("StartButton.png", Vec2(0.5, 0.3), 0.6, 0.2);
    m_hiScoresButton = new RectButton("HiScoreButton.png", Vec2(0.5, 0.55), 0.6, 0.2);
	m_quitButton = new RectButton("QuitButton.png", Vec2(0.5, 0.8), 0.6, 0.2);

	m_background = Resources::GetInstance().LoadBmp("SpaceBG.png");
	m_cursorBMP = Resources::GetInstance().LoadBmp("Cursor.png");

	m_font72 = Resources::GetInstance().LoadFont("Orange Juice 2.0.ttf", 120);

	m_cursor = al_create_mouse_cursor(m_cursorBMP.GetBitmap(), 0, 0);
	al_set_mouse_cursor(Core::GetInstance().GetDisplay(), m_cursor);
	al_show_mouse_cursor(Core::GetInstance().GetDisplay());

	// Fade in effect when gamestate first loads
	Core::GetInstance().GetStateManager().AddState(std::make_shared<Fade>(Enums::COLOUR::BLACK, 0.5, true, Enums::GAMESTATE::NONE));
}

bool Title::Update()
{
	Vec2 mousePos = Input::GetInstance().GetMouseAxis();

	if (m_startButton->Update())
	{
		Core::GetInstance().GetStateManager().AddState(std::make_shared<Fade>(Enums::COLOUR::BLACK, 1, false, Enums::GAMESTATE::LEVEL));
		return true;
	}

	if(m_hiScoresButton->Update())
	{
		Core::GetInstance().GetStateManager().AddState(std::make_shared<HiScore>());
	}

	if (m_quitButton->Update())
	{
		return false;
	}

	if(Input::GetInstance().CheckDisplayClose())
	{
		return false;
	}

	return true;
}

void Title::Render()
{
	al_draw_bitmap(m_background.GetBitmap(), 0, 0, NULL);

	al_draw_textf(m_font72.lock().get(), al_map_rgb(255, 0, 255), 0.5 * m_defWinWidth, 0.05 * m_defWinHeight, ALLEGRO_ALIGN_CENTER, "Asteroids!... Again");
	m_startButton->Render();
	m_hiScoresButton->Render();
	m_quitButton->Render();
}

void Title::Shutdown()
{
	delete m_startButton;
	delete m_quitButton;
}

Title::~Title() {}