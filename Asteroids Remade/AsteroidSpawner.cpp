#include "stdafx.h"

#include "AsteroidSpawner.h"

AsteroidSpawner::AsteroidSpawner()
{
	m_maxBigAst = 50;
	m_maxMedAst = 100;
	m_maxSmallAst = 150;

	m_bigAsteroids = new BigAsteroid[m_maxBigAst];
	m_medAsteroids = new MedAsteroid[m_maxMedAst];
	m_smallAsteroids = new SmallAsteroid[m_maxSmallAst];

	ALLEGRO_MONITOR_INFO info;
	al_get_monitor_info(0, &info);

	m_displayWidth = info.x2;
	m_displayHeight = info.y2;
}

void AsteroidSpawner::Start()
{
	SpawnAsteroids(5, 0);
}

void AsteroidSpawner::Update()
{
	for (int x = 0; x < m_maxBigAst; x++)
	{
		if (m_bigAsteroids[x].IsLive())
		{
			m_bigAsteroids[x].Update();
			m_bigAsteroids[x].LimitCheck(m_displayWidth, m_displayHeight);
		}
	}

	for (int x = 0; x < m_maxMedAst; x++)
	{
		if (m_medAsteroids[x].IsLive())
		{
			m_medAsteroids[x].Update();
			m_medAsteroids[x].LimitCheck(m_displayWidth, m_displayHeight);
		}
	}

	for (int x = 0; x < m_maxSmallAst; x++)
	{
		if (m_smallAsteroids[x].IsLive())
		{
			m_smallAsteroids[x].Update();
			m_smallAsteroids[x].LimitCheck(m_displayWidth, m_displayHeight);
		}
	}
}

void AsteroidSpawner::Render()
{
	for (int x = 0; x < m_maxBigAst; x++)
	{
		if (m_bigAsteroids[x].IsLive())
		{
			m_bigAsteroids[x].Render();
		}
	}

	for (int x = 0; x < m_maxMedAst; x++)
	{
		if (m_medAsteroids[x].IsLive())
		{
			m_medAsteroids[x].Render();
		}
	}

	for (int x = 0; x < m_maxSmallAst; x++)
	{
		if (m_smallAsteroids[x].IsLive())
		{
			m_smallAsteroids[x].Render();
		}
	}
}

void AsteroidSpawner::SpawnAsteroids(int _num, int _size)
{
	int y = 0;

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(1, 2);

	int z = distr(eng);

	if (_size == 0)
	{
		for (int x = 0; x < m_maxBigAst && y < _num; x++)
		{
			if (!m_bigAsteroids[x].IsLive())
			{
				float xCo, yCo;

				if (z == 1)
				{
					std::uniform_int_distribution<> distr(0, 1000);
					xCo = distr(eng);
					yCo = 1100;
				}

				if (z == 2)
				{
					std::uniform_int_distribution<> distr(0, 1000);
					xCo = 1100;
					yCo = distr(eng);
				}

				m_bigAsteroids[x].Spawn(Vec2(xCo, yCo));
				y++;
			}
		}
	}

	else if (_size == 1)
	{
		for (int x = 0; x < m_maxMedAst && y < _num; x++)
		{
			if (!m_medAsteroids[x].IsLive())
			{
				float xCo, yCo;

				if (z == 1)
				{
					std::uniform_int_distribution<> distr(0, 1000);
					xCo = distr(eng);
					yCo = 1100;
				}

				if (z == 2)
				{
					std::uniform_int_distribution<> distr(0, 1000);
					xCo = 1100;
					yCo = distr(eng);
				}

				m_medAsteroids[x].Spawn(Vec2(xCo, yCo));
				y++;
			}
		}
	}

	else if (_size == 2)
	{
		for (int x = 0; x < m_maxSmallAst && y < _num; x++)
		{
			if (!m_smallAsteroids[x].IsLive())
			{
				float xCo, yCo;

				if (z == 1)
				{
					std::uniform_int_distribution<> distr(0, 1000);
					xCo = distr(eng);
					yCo = 1100;
				}

				if (z == 2)
				{
					std::uniform_int_distribution<> distr(0, 1000);
					xCo = 1100;
					yCo = distr(eng);
				}

				m_smallAsteroids[x].Spawn(Vec2(xCo, yCo));
				y++;
			}
		}
	}
}

AsteroidSpawner::~AsteroidSpawner()
{
	delete[]m_bigAsteroids;
	delete[]m_medAsteroids;
	delete[]m_smallAsteroids;
}