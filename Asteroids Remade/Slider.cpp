#include "stdafx.h"

#include "Slider.h"
#include "Input.h"
#include "Resources.h"
#include "Core.h"


Slider::Slider(Vec2 _pos, float _width, float _currVal, std::string _text)
{
	m_transform.m_pos.x = _pos.x * m_defWinWidth;
	m_transform.m_pos.y = _pos.y * m_defWinHeight;
	m_width = _width * m_defWinWidth;
	m_text = _text;

	m_buttonPos.x = m_transform.m_pos.x + m_width * _currVal;
	m_buttonPos.y = m_transform.m_pos.y;
	m_buttonWidth = 0.018 * m_defWinWidth;
	m_buttonHeight = 0.030 * m_defWinHeight;

	m_val = _currVal;
	m_clicked = false;

	m_font = Resources::GetInstance().LoadFont("Arial.ttf", 30);
}

// Checks for mouse collision for the slider and whether the slider button has been moved
bool Slider::Update()
{
	Vec2 mousePos = Input::GetInstance().GetMouseAxis();

	if((mousePos.x - m_displaySize.s_wOffset) / m_displaySize.s_wRatio > m_buttonPos.x - (m_buttonWidth * 0.5) && (mousePos.x - m_displaySize.s_wOffset) / m_displaySize.s_wRatio < m_buttonPos.x + (m_buttonWidth * 0.5)
		&& (mousePos.y - m_displaySize.s_hOffset) / m_displaySize.s_hRatio > m_buttonPos.y - (m_buttonHeight * 0.5) && (mousePos.y - m_displaySize.s_hOffset) / m_displaySize.s_hRatio < m_buttonPos.y + (m_buttonHeight * 0.5))
	{
		if(Input::GetInstance().GetButtonDown(0))
		{
			m_clicked = true;
		}
	}

	if(Input::GetInstance().GetButtonDown(2))
	{
		int x = 5;
	}

	if(m_clicked)
	{
		m_buttonPos.x = (mousePos.x - m_displaySize.s_wOffset) / m_displaySize.s_wRatio;

		if(m_buttonPos.x < m_transform.m_pos.x)
		{
			m_buttonPos.x = m_transform.m_pos.x;
		}

		if(m_buttonPos.x > m_transform.m_pos.x + m_width)
		{
			m_buttonPos.x = m_transform.m_pos.x + m_width;
		}

		m_val = ((m_buttonPos.x - m_transform.m_pos.x) / m_width);

		if(Input::GetInstance().GetButtonUp(0))
		{
			m_clicked = false;
		}

		return true;
	}

	else
		return false;
}

void Slider::Render()
{
	al_draw_line(m_transform.m_pos.x, m_transform.m_pos.y, m_transform.m_pos.x + m_width, m_transform.m_pos.y, al_map_rgb(0, 0, 255), 10);
	al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), m_transform.m_pos.x, m_transform.m_pos.y - 0.050 * m_defWinHeight, NULL, m_text.c_str());
	al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), m_transform.m_pos.x + m_width - 0.040 * m_defWinWidth, m_transform.m_pos.y - 0.050 * m_defWinHeight, NULL, "%i", (int)(m_val * 100));

	al_draw_filled_rectangle(m_buttonPos.x - m_buttonWidth * 0.5, m_buttonPos.y - m_buttonHeight * 0.5, m_buttonPos.x + m_buttonWidth * 0.5, m_buttonPos.y + m_buttonHeight * 0.5, al_map_rgb(0, 255, 0));
}

// Returns current % value of the slider
float Slider::GetCurrentValue()
{
	return m_val;
}

Slider::~Slider() {}