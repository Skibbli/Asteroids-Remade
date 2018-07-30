#include "stdafx.h"

#include "Button.h"
#include "Input.h"
#include "Resources.h"
#include "Core.h"


Button::Button()
{
	m_collision = false;
	m_isLive = false;
	m_clicked = false;
	m_hasBitmap = false;

	m_displaySize = Core::GetInstance().GetDisplaySize();
}

void Button::Start() {}

bool Button::Update() { return false; }

void Button::Render() {}

void Button::SetText(std::string _fontName, int _fontSize, std::string _text, Colour _col)
{
	m_font = Resources::GetInstance().LoadFont(_fontName, _fontSize);
	m_text = _text;
	m_textCol = _col;
}

Button::~Button() {}

// Circle Button

CircleButton::CircleButton() {}

/// Button sizes are % of window size
CircleButton::CircleButton(std::string _text, Colour _textCol, std::string _font, int _fontSize, Vec2 _pos, float _radius, Colour _col)
{
	m_font = Resources::GetInstance().LoadFont(_font, _fontSize);
	m_text = _text;
	m_textCol = _textCol;

	m_transform.m_pos.x = _pos.x * 1000;
	m_transform.m_pos.y = _pos.y * 1000;
	m_radius = _radius * m_displaySize.s_width;
	m_buttonCol = _col;
}

/// Button sizes are % of window size
CircleButton::CircleButton(std::string _bitmap, Vec2 _pos, float _radius)
{
	m_bitmap = Resources::GetInstance().LoadBmp(_bitmap);
	m_radius = _radius * 1000;
	m_transform.m_pos.x = _pos.x * 1000;
	m_transform.m_pos.y = _pos.y * 1000;

	m_hasBitmap = true;
}

void CircleButton::Start()
{
	
}

// Checks for collision and mouse clicking and returns whether both conditions are true
bool CircleButton::Update()
{
	m_collision = false;
	m_clicked = false;

	if (Input::GetInstance().GetButtonDown(0))
	{
		m_clicked = true;
	}

	Vec2 mousePos = Input::GetInstance().GetMouseAxis();
	mousePos.x = (mousePos.x - m_displaySize.s_wOffset) / m_displaySize.s_wRatio;
	mousePos.y = (mousePos.y - m_displaySize.s_hOffset) / m_displaySize.s_hRatio;

	Vec2 diff = m_transform.m_pos - mousePos;

	float dist = glm::length(diff);

	if (dist < m_radius)
	{
		m_collision = true;
	}

	return m_collision && m_clicked;
}

void CircleButton::Render()
{
	if(m_hasBitmap)
	{
		al_draw_scaled_bitmap(m_bitmap.GetBitmap(), 0, 0, m_bitmap.s_frameWidth, m_bitmap.s_frameHeight, m_transform.m_pos.x - m_radius, m_transform.m_pos.y - m_radius, m_radius * 2, m_radius * 2, NULL);
	}

	else
	{
		al_draw_filled_circle(m_transform.m_pos.x, m_transform.m_pos.y, m_radius, al_map_rgba(m_buttonCol.r, m_buttonCol.b, m_buttonCol.g, m_buttonCol.a));
		al_draw_textf(m_font.lock().get(), al_map_rgba(m_textCol.r, m_textCol.b, m_textCol.g, m_textCol.a), m_transform.m_pos.x, m_transform.m_pos.y - m_font.lock()->height, ALLEGRO_ALIGN_CENTRE, m_text.c_str());
	}

	if (m_collision)
	{
		al_draw_circle(m_transform.m_pos.x, m_transform.m_pos.y, m_radius, al_map_rgb(255, 0, 255), 4);
	}
}

CircleButton::~CircleButton() {}

// Rectangle Button

RectButton::RectButton() {}

/// Button sizes are % of window size
RectButton::RectButton(std::string _text, Colour _textCol, std::string _font, int _fontSize, Vec2 _pos, float _width, float _height, Colour _col)
{
	m_font = Resources::GetInstance().LoadFont(_font, _fontSize);
	m_text = _text;
	m_textCol = _textCol;

	m_width = _width * 1000;
	m_height = _height * 1000;
	m_transform.m_pos.x = _pos.x * 1000;
	m_transform.m_pos.y = _pos.y * 1000;
	m_buttonCol = _col;

	m_hasBitmap = false;
}

/// Button sizes are % of window size. If width or height are 0 the width and height of the bitmap will be used by default
RectButton::RectButton(std::string _bitmap, Vec2 _pos, float _width, float _height)
{
	m_bitmap = Resources::GetInstance().LoadBmp(_bitmap);

	if(_width == 0 || _height == 0)
	{
		m_width = m_bitmap.s_frameWidth;
		m_height = m_bitmap.s_frameHeight;
	}

	else
	{
		m_width = _width * 1000;
		m_height = _height * 1000;
	}

	m_transform.m_pos.x = _pos.x * 1000;
	m_transform.m_pos.y = _pos.y * 1000;

	m_hasBitmap = true;
}

void RectButton::Start() {}

// Checks for collision and mouse clicking and returns whether both conditions are true
bool RectButton::Update()
{
	m_collision = false;
	m_clicked = false;

	Vec2 mousePos = Input::GetInstance().GetMouseAxis();

	if (Input::GetInstance().GetButtonDown(0))
		m_clicked = true;

	if ((mousePos.x - m_displaySize.s_wOffset) / m_displaySize.s_wRatio > m_transform.m_pos.x - (m_width * 0.5) && (mousePos.x - m_displaySize.s_wOffset) / m_displaySize.s_wRatio < m_transform.m_pos.x + (m_width * 0.5) &&
		(mousePos.y - m_displaySize.s_hOffset) / m_displaySize.s_hRatio > m_transform.m_pos.y - (m_height * 0.5) && (mousePos.y - m_displaySize.s_hOffset) / m_displaySize.s_hRatio < m_transform.m_pos.y + (m_height * 0.5))
	{
		m_collision = true;
	}

	return m_collision && m_clicked;
}

void RectButton::Render()
{
	if(m_hasBitmap)
	{
		al_draw_scaled_bitmap(m_bitmap.GetBitmap(), 0, 0, m_bitmap.s_frameWidth, m_bitmap.s_frameHeight, m_transform.m_pos.x - 0.5 * m_width, m_transform.m_pos.y - 0.5 * m_height, m_width, m_height, NULL);
	}

	else
	{
		al_draw_filled_rounded_rectangle(m_transform.m_pos.x - 0.5 * m_width, m_transform.m_pos.y - 0.5 * m_height, m_transform.m_pos.x + 0.5 * m_width, m_transform.m_pos.y + 0.5 * m_height, 0.001 * m_defWinWidth, 0.001 * m_defWinHeight, al_map_rgba(m_buttonCol.r, m_buttonCol.b, m_buttonCol.g, m_buttonCol.a));
		al_draw_textf(m_font.lock().get(), al_map_rgba(m_textCol.r, m_textCol.b, m_textCol.g, m_textCol.a), m_transform.m_pos.x, m_transform.m_pos.y - m_font.lock()->height * 0.5, ALLEGRO_ALIGN_CENTRE, m_text.c_str());
	}

	if (m_collision)
	{
		al_draw_rectangle(m_transform.m_pos.x - 0.5 * m_width, m_transform.m_pos.y - 0.5 * m_height, m_transform.m_pos.x + 0.5 * m_width, m_transform.m_pos.y + 0.5 * m_height, al_map_rgb(255, 0, 255), 4);
	}
}

RectButton::~RectButton() {}