#ifndef UFOSPAWNER_H
#define UFOSPAWNER_H

#include "stdafx.h"

#include "UFO.h"
#include "Explosion.h"

class Player;

// Handles spawning and control of UFOs
class UFOSpawner
{
	public:
		UFOSpawner();
		~UFOSpawner();

		void Start(Player* _player);
		void Update();
		void Render();
		void Shutdown();

		void SetSpawnCD(float _spawnCD);
		void SpawnExplosion(Vec2 _pos, float _size);

	private:
		UFO* m_UFOs;
		int m_numUFOs;
		int m_numExplosion;

		// Timers for UFO spawn rate
		float m_spawnCD;
		float m_spawnTimer;

		Explosion* m_explosions;
		// Pointer to player to control aiming
		Player* m_player;
};

#endif