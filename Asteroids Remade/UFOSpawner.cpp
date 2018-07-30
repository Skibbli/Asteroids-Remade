#include "stdafx.h"

#include "UFOSpawner.h"
#include "Time.h"


UFOSpawner::UFOSpawner()
{
	m_spawnCD = 20.0f;
	m_spawnTimer = 0.0f;

	m_numUFOs = 10;
	m_numExplosion = 4;

	m_UFOs = new UFO[m_numUFOs];
	m_explosions = new Explosion[m_numExplosion];
}

void UFOSpawner::Start(Player *_player)
{
	m_player = _player;

	for (int i = 0; i < m_numUFOs; i++)
	{
		m_UFOs[i].Start(_player);
	}
}

// Updates live UFOs, explosions and spawn timers
void UFOSpawner::Update()
{
	for (int i = 0; i < m_numUFOs; i++)
	{
		if (m_UFOs[i].Update())
		{
			SpawnExplosion(m_UFOs[i].GetPos(), 1.2);
		}
	}

	for (int i = 0; i < m_numExplosion; i++)
	{
		if (m_explosions[i].GetIsLive())
		{
			m_explosions[i].Update();
		}
	}

	m_spawnTimer += Time::GetDeltaTime();

	if (m_spawnTimer > m_spawnCD)
	{
		for (int i = 0; i < m_numUFOs; i++)
		{
			if (!m_UFOs[i].GetIsLive())
			{
				m_UFOs[i].Spawn();
				break;
			}
		}

		m_spawnTimer = 0.0f;
	}
}

void UFOSpawner::Render()
{
	for (int i = 0; i < m_numUFOs; i++)
	{
		m_UFOs[i].Render();
	}

	for (int i = 0; i < m_numExplosion; i++)
	{
		if (m_explosions[i].GetIsLive())
		{
			m_explosions[i].Render();
		}
	}
}

void UFOSpawner::SetSpawnCD(float _spawnCD)
{
	m_spawnCD = _spawnCD;
}

void UFOSpawner::SpawnExplosion(Vec2 _pos, float _size)
{
	for (int i = 0; i < m_numExplosion; i++)
	{
		if (!m_explosions[i].GetIsLive())
		{
			m_explosions[i].Spawn(_pos, _size);
		}
	}
}

void UFOSpawner::Shutdown()
{
	m_player = nullptr;

	for (int i = 0; i < m_numUFOs; i++)
	{
		m_UFOs[i].Shutdown();
	}

	delete[] m_UFOs;
}

UFOSpawner::~UFOSpawner() {}