#ifndef FADE_H
#define FADE_H

#include "stdafx.h"

#include "Gamestate.h"


// Class for fading graphics in and out for gamestate transitions
class Fade : public Gamestate
{
	public:
		Fade(Enums::COLOUR _col, float _fadeTime, bool _fadeIn, Enums::GAMESTATE _nextState);
		~Fade();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

		void EndFade();

	private:
		float m_fadeTime;
		float m_fadeTimeCounter;
		float m_timeStep;
		float m_alphaDecVal;
		bool m_fadeIn;

		float m_alpha;

		Enums::GAMESTATE m_nextState;
};

#endif