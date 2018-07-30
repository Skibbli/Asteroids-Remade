#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "stdafx.h"

#include "GamestateManager.h"
#include "ResourceStructs.h"


// Base class for gamestates to inherit from
class Gamestate
{
	public:
		Gamestate();
		~Gamestate();

		virtual void Start() = 0;
		virtual bool Update() = 0;
		virtual void Render() = 0;
		virtual void Shutdown() = 0;

	protected:
		// Default window width and height
		float m_defWinWidth, m_defWinHeight;

		Bitmap m_background;

	private:
};

#endif