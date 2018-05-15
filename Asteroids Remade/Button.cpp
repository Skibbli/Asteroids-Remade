#include "stdafx.h"

#include "Button.h"
#include "Input.h"
#include "Resources.h"

Button::Button()
{
	m_collision = false;
	m_isLive = false;
	m_clicked = false;
}

void Button::Start()
{

}

bool Button::Update()
{
	return m_collision;
}

void Button::Render()
{

}

Button::~Button()
{

}

// Circle Button

CircleButton::CircleButton()
{

}

void CircleButton::Start(Vec2 _pos, float _radius)
{
	m_pos = _pos;
	m_radius = _radius;

	m_bitmap = Resources::GetInstance().LoadBmp("StartButton.png");

	m_radius = al_get_bitmap_width(m_bitmap.lock().get()) / 2;
}

bool CircleButton::Update()
{
	m_collision = false;
	m_clicked = false;

	if (Input::GetButtonDown(0))
		m_clicked = true;

	Vec2 mousePos = Input::GetMouseAxis();
	Vec2 diff = m_pos - mousePos;

	float dist = glm::length(diff);

	if (dist < m_radius)
	{
		m_collision = true;
	}

	return m_collision && m_clicked;
}

void CircleButton::Render()
{
	al_draw_bitmap(m_bitmap.lock().get(), m_pos.x - m_radius, m_pos.y - m_radius, 0);

	if (m_collision)
	{
		al_draw_circle(m_pos.x, m_pos.y, m_radius, al_map_rgb(255, 0, 255), 4);
	}
}

CircleButton::~CircleButton()
{

}

// Rectangle Button

RectButton::RectButton()
{

}

void RectButton::Start(Vec2 _pos, float _width, float _height)
{
	m_pos = _pos;
	m_width = _width;
	m_height = _height;

	m_bitmap = Resources::GetInstance().LoadBmp("QuitButton.png");

	m_width = al_get_bitmap_width(m_bitmap.lock().get());
	m_height = al_get_bitmap_height(m_bitmap.lock().get());
}

bool RectButton::Update()
{
	m_collision = false;
	m_clicked = false;

	if (Input::GetButtonDown(0))
		m_clicked = true;

	Vec2 mousePos = Input::GetMouseAxis();

	if (mousePos.x > m_pos.x - m_width / 2 && mousePos.x < m_pos.x + m_width / 2 &&
		mousePos.y > m_pos.y - m_height / 2 && mousePos.y < m_pos.y + m_height / 2)
	{
		m_collision = true;
	}
		
	return m_collision && m_clicked;
}

void RectButton::Render()
{
	al_draw_bitmap(m_bitmap.lock().get(), m_pos.x - m_width / 2, m_pos.y - m_height / 2, 0);

	if (m_collision)
	{
		al_draw_rectangle(m_pos.x - m_width / 2, m_pos.y - m_height / 2, m_pos.x + m_width / 2, m_pos.y + m_height / 2, al_map_rgb(255, 0, 255), 4);
	}
}

RectButton::~RectButton()
{

}