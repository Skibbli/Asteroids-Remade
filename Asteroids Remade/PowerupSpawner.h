#ifndef POWERUP_SPAWNER_H
#define POWERUP_SPAWNER_H

#include "stdafx.h"

#include "Powerup.h"


// Handles spawning and control of powerups
class PowerupSpawner
{
	public:
		PowerupSpawner();
		~PowerupSpawner();

		void Start();
		void Update();
		void Render();
		void Shutdown();

		void SpawnPowerup();

	private:
		Powerup m_powerup;

		bool m_powerupLive;

		// Powerup counters
		float m_spawnCD;
		float m_timePassed;
};

#endif