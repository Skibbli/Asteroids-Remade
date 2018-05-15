#ifndef LEVEL_H
#define LEVEL_H

#include "stdafx.h"

#include "Gamestate.h"
#include "Player.h"
#include "Asteroid.h"


class Level : public Gamestate
{
	public:
		Level(GamestateManager *_manager, ALLEGRO_DISPLAY *_display);
		~Level();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

	private:
		int m_numBullets;

		float m_displayWidth, m_displayHeight;

		Player m_player;
		
		Bullet *m_bullets;
		
		weak<ALLEGRO_FONT> m_font;

		void FireBullet();
		bool GetInput();
		
};

#endif