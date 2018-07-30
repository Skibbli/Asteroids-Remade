#include "stdafx.h"

#include "PowerupSpawner.h"
#include "Time.h"
#include "Core.h"
#include "Maths.h"


PowerupSpawner::PowerupSpawner()
{
	m_timePassed = 10;
	m_spawnCD = 35;
}

void PowerupSpawner::Start()
{
	m_powerup.Start();
}

// Updates live powerups and despawns them after timer expires
void PowerupSpawner::Update()
{
	m_timePassed += Time::GetDeltaTime();
	
	if (m_powerup.GetIsLive())
		m_powerup.Update();

	if (m_timePassed >= m_spawnCD)
	{
		SpawnPowerup();
		m_timePassed = 0;
	}
}

void PowerupSpawner::Render()
{
	if (m_powerup.GetIsLive())
		m_powerup.Render();
}

// Spawns a random type of powerup
void PowerupSpawner::SpawnPowerup()
{
	m_powerup.Spawn(GenRandNo(1, 4));
	m_powerupLive = true;
}

void PowerupSpawner::Shutdown()
{
	m_powerup.Shutdown();
}

PowerupSpawner::~PowerupSpawner()
{
}