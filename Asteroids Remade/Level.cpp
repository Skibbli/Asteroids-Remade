#include "stdafx.h"

#include "Level.h"
#include "Input.h"
#include "Resources.h"
#include "Fade.h"


Level::Level(GamestateManager *_manager, ALLEGRO_DISPLAY *_display)
{
	m_stateManager = _manager;
	m_display = _display;
}

void Level::Start()
{
	m_background = Resources::GetInstance().LoadBmp("SpaceBG.png");
	m_font = Resources::GetInstance().LoadFont("arial.ttf");
	m_cursor = Resources::GetInstance().LoadBmp("Cursor.png");

	m_displayWidth = al_get_display_width(m_display);
	m_displayHeight = al_get_display_height(m_display);

	m_player.Start(m_bullets);
	m_spawner.Start();

	m_numBullets = 200;
	m_bullets = new Bullet[m_numBullets];
}

bool Level::Update()
{
	if (!GetInput())
		return false;

	if (m_player.Update())
		FireBullet();

	for (int x = 0; x < m_numBullets; x++)
	{
		if (m_bullets[x].IsLive())
		{
			if (!m_bullets[x].Update())
			{
				m_bullets[x].SetLive(false);
			}

			m_bullets[x].LimitCheck(m_displayWidth, m_displayHeight);
		}
	}

	m_spawner.Update();

	m_player.LimitCheck(m_displayWidth, m_displayHeight);
	
	m_spawner.CheckForCollisions(m_bullets, m_numBullets);

	return true;
}

void Level::Render()
{
	al_draw_bitmap(m_background.lock().get(), 0, 0, 0);
	m_player.Render();

	for (int x = 0; x < m_numBullets; x++)
	{
		if (m_bullets[x].IsLive())
		{
			m_bullets[x].Render();
		}
	}

	m_spawner.Render();

	/*al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 20, 20, 0, "X Pos: %f", m_player.GetPos().x);
	al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 20, 50, 0, "Y Pos: %f", m_player.GetPos().y);

	al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 20, 80, 0, "X Vel: %f", m_player.GetXVel());
	al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 20, 110, 0, "Y Vel: %f", m_player.GetYVel());
	al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 20, 140, 0, "Direction: %f", m_player.GetDirection());*/

	Vec2 cursorPos = Input::GetMouseAxis();

	al_draw_bitmap(m_cursor.lock().get(), cursorPos.x, cursorPos.y, 0);
}

void Level::FireBullet()
{
	for (int x = 0; x < m_numBullets; x++)
	{
		if (!m_bullets[x].IsLive())
		{
			m_player.GetBulletDets(m_bullets[x]);
			m_bullets[x].SetLive(true);
			break;
		}
	}
}

bool Level::GetInput()
{
	if (Input::GetKeyDown(ALLEGRO_KEY_ESCAPE))
	{
		return false;
	}

	m_player.Input();

	if (Input::GetKeyDown(ALLEGRO_KEY_P))
	{
		m_stateManager->AddState(new Fade(m_stateManager, m_display, WHITE, 500));
	}

	return true;
}



void Level::Shutdown()
{
	delete []m_bullets;
	
}

Level::~Level()
{

}