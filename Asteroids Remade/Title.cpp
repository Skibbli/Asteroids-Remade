#include "stdafx.h"

#include "Title.h"
#include "Level.h"
#include "Resources.h"
#include "Input.h"

Title::Title(GamestateManager *_manager, ALLEGRO_DISPLAY *_display)
{
	m_stateManager = _manager;
	m_display = _display;	
}

void Title::Start()
{
	m_circleButton.Start(Vec2(500, 300), 150);
	m_rectButton.Start(Vec2(500, 800), 500, 200);

	m_background = Resources::GetInstance().LoadBmp("SpaceBG.png");
	m_cursor = Resources::GetInstance().LoadBmp("Cursor.png");
}

bool Title::Update()
{
	if (m_circleButton.Update())
	{
		m_stateManager->ChangeState(new Level(m_stateManager, m_display));
		return true;
	}

	if (m_rectButton.Update())
		return false;

	return true;
}

void Title::Render()
{
	al_draw_bitmap(m_background.lock().get(), 0, 0, 0);

	m_circleButton.Render();
	m_rectButton.Render();

	Vec2 cursorPos = Input::GetMouseAxis();

	al_draw_bitmap(m_cursor.lock().get(), cursorPos.x, cursorPos.y, 0);
}

void Title::Shutdown()
{

}

Title::~Title()
{

}