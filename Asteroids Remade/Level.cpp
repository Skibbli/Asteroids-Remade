#include "stdafx.h"

#include "Level.h"
#include "Input.h"
#include "Resources.h"
#include "Fade.h"
#include "Core.h"
#include "Title.h"
#include "Pause.h"


Level::Level() {}

void Level::Start()
{
	m_background = Resources::GetInstance().LoadBmp("SpaceBG.png");
	m_BGM = Resources::GetInstance().LoadMusicSample("Background Music.ogg");

	m_player.Start();
	m_ufoSpawner.Start(&m_player);
	m_astSpawner.Start(&m_player);
	m_pupSpawner.Start();

	m_gameOver = false;

	al_hide_mouse_cursor(Core::GetInstance().GetDisplay());
	Core::GetInstance().GetStateManager().AddState(std::make_shared<Fade>(Enums::COLOUR::BLACK, 1, true, Enums::GAMESTATE::NONE));

	m_BGM.lock()->PlaySample();
}

bool Level::Update()
{
	GetInput();

	if(!m_gameOver)
	{
		m_ufoSpawner.Update();
		m_astSpawner.Update();
		m_pupSpawner.Update();

		if (!m_player.Update())
		{
			m_gameOver = true;
		}

		Core::GetInstance().UpdatePhysics();
	}

	return true;
}

void Level::Render()
{
	al_draw_bitmap(m_background.GetBitmap(), 0, 0, NULL);

	if(!m_gameOver)
	{
		m_ufoSpawner.Render();
		m_pupSpawner.Render();
		m_astSpawner.Render();
	}

	m_player.Render();
}

void Level::GetInput()
{
	if (Input::GetInstance().GetKeyDown(ALLEGRO_KEY_P))
	{
		Core::GetInstance().GetStateManager().AddState(std::make_shared<Pause>());
	}

	if (Input::GetInstance().GetKeyDown(ALLEGRO_KEY_ESCAPE))
	{
		Core::GetInstance().GetStateManager().AddState(std::make_shared<Pause>());
	}

	if (Input::GetInstance().CheckDisplayClose())
	{
		Core::GetInstance().GetStateManager().AddState(std::make_shared<Pause>());
	}

	m_player.Input();
}

void Level::Shutdown()
{
	m_player.Shutdown();

	m_ufoSpawner.Shutdown();
	m_astSpawner.Shutdown();
	m_pupSpawner.Shutdown();

	m_BGM.lock()->StopSample();

	Core::GetInstance().ResetPhysicsEngine();
}

Level::~Level() {}