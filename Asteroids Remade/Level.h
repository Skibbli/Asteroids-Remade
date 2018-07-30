#ifndef LEVEL_H
#define LEVEL_H

#include "stdafx.h"

#include "Gamestate.h"
#include "Player.h"
#include "AsteroidSpawner.h"
#include "PowerupSpawner.h"
#include "UFOSpawner.h"


class Level : public Gamestate
{
	public:
		Level();
		~Level();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

		void UpdateDisplaySize(DisplayInfo _displaySize);

	private:
		void GetInput();

		bool m_gameOver;

		Player m_player;	

		// Spawns and controls UFOs
		UFOSpawner m_ufoSpawner;
		// Spawns and controls Asteroids
		AsteroidSpawner m_astSpawner;
		// Spawns and controls powerups
		PowerupSpawner m_pupSpawner;

		weak<MusicSample> m_BGM;
};

#endif