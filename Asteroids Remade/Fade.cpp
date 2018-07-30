#include "stdafx.h"

#include "Fade.h"
#include "Input.h"
#include "Core.h"
#include "Time.h"
#include "Level.h"
#include "Title.h"
#include "HiScore.h"
#include "Options.h"


Fade::Fade(Enums::COLOUR _col, float _fadeTime, bool _fadeIn, Enums::GAMESTATE _nextState)
{
	m_fadeIn = _fadeIn;
	m_nextState = _nextState;
	m_alpha = 255;
	m_fadeTime = _fadeTime;
	m_fadeTimeCounter = 0;
	m_timeStep = _fadeTime / 255;
	m_alphaDecVal = 255 / (_fadeTime * 100);
	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
}

void Fade::Start()
{
	
}

// Cycles the fade in the specified direction for the given time and colour
bool Fade::Update()
{
	m_fadeTimeCounter += Time::GetDeltaTime();

	if (m_fadeTimeCounter > m_timeStep)
	{
		m_alpha -= m_alphaDecVal;
		m_fadeTimeCounter = 0;

		if (m_alpha < 0)
		{
			m_alpha = 0;
		}
	}

	return true;
}

void Fade::Render()
{
	if(m_alpha < 0)
		m_alpha = 0;

	if(m_alpha > 255)
		m_alpha = 255;

	if (m_fadeIn)
	{
		al_draw_filled_rectangle(0, 0, m_defWinWidth, m_defWinHeight, al_map_rgba(0, 0, 0, m_alpha));
	}
	
	else
	{
		al_draw_filled_rectangle(0, 0, m_defWinWidth, m_defWinHeight, al_map_rgba(0, 0, 0, 255 - m_alpha));
	}

	if (m_alpha == 0)
	{
		EndFade();
	}
}

// When the fade in/out is complete gamestate is changed to the given state
void Fade::EndFade()
{
	switch (m_nextState)
	{
		case Enums::GAMESTATE::LEVEL:
		{
			Core::GetInstance().GetStateManager().ChangeState(std::make_shared<Level>());
		}
		break;
		case Enums::GAMESTATE::OPTIONS:
		{
			Core::GetInstance().GetStateManager().ChangeState(std::make_shared<Options>());
		}
			break;
		case Enums::GAMESTATE::TITLE:
		{
			Core::GetInstance().GetStateManager().ChangeState(std::make_shared<Title>());
		}
			break;
		case Enums::GAMESTATE::HISCORES:
		{
			Core::GetInstance().GetStateManager().ChangeState(std::make_shared<HiScore>());
		}
			break;
		case Enums::GAMESTATE::QUIT:
		{
			Core::GetInstance().GetStateManager().ChangeState(std::make_shared<Title>());
		}
			break;
		case Enums::GAMESTATE::NONE:
		{
			Core::GetInstance().GetStateManager().RemoveLastState();
		}
			break;
		default: {}
	}
}

void Fade::Shutdown() {}

Fade::~Fade() {}