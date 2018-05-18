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

	m_displayWidth = 1000;
	m_displayHeight = 1000;
}

void AsteroidSpawner::Start()
{
	SpawnAsteroids(4, 0, Vec2(0,0), true);
}

void AsteroidSpawner::Update()
{
	for (int x = 0; x < m_maxBigAst; x++)
	{
		if (m_bigAsteroids[x].IsLive())
		{
			if (m_bigAsteroids[x].Update())
			{
				m_bigAsteroids[x].LimitCheck();
			}

			else
			{
				SpawnAsteroids(4, 1, m_bigAsteroids[x].GetPos(), false);
				m_bigAsteroids[x].SetIsLive(false);
			}
		}
	}

	for (int x = 0; x < m_maxMedAst; x++)
	{
		if (m_medAsteroids[x].IsLive())
		{
			if (m_medAsteroids[x].Update())
			{
				m_medAsteroids[x].LimitCheck();
			}

			else
			{
				SpawnAsteroids(4, 1, m_medAsteroids[x].GetPos(), false);
				m_medAsteroids[x].SetIsLive(false);
			}
		}
	}

	for (int x = 0; x < m_maxSmallAst; x++)
	{
		if (m_smallAsteroids[x].IsLive())
		{
			if (m_smallAsteroids[x].Update())
			{
				m_smallAsteroids[x].LimitCheck();
			}

			else
			{
				m_smallAsteroids[x].SetIsLive(false);
			}
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

void AsteroidSpawner::SpawnAsteroids(int _num, int _size, Vec2 _pos, bool _random)
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
				if (_random)
				{
					if (z == 1)
					{
						std::uniform_int_distribution<> distr(0, 1000);
						_pos.x = distr(eng);
						_pos.y = 1100;
					}

					if (z == 2)
					{
						std::uniform_int_distribution<> distr(0, 1000);
						_pos.x = 1100;
						_pos.y = distr(eng);
					}
				}

				m_bigAsteroids[x].Spawn(_pos);
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
				if (_random)
				{
					if (z == 1)
					{
						std::uniform_int_distribution<> distr(0, 1000);
						_pos.x = distr(eng);
						_pos.y = 1100;
					}

					if (z == 2)
					{
						std::uniform_int_distribution<> distr(0, 1000);
						_pos.x = 1100;
						_pos.y = distr(eng);
					}
				}

				m_medAsteroids[x].Spawn(_pos);
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
				if (_random)
				{
					if (z == 1)
					{
						std::uniform_int_distribution<> distr(0, 1000);
						_pos.x = distr(eng);
						_pos.y = 1100;
					}

					if (z == 2)
					{
						std::uniform_int_distribution<> distr(0, 1000);
						_pos.x = 1100;
						_pos.y = distr(eng);
					}
				}

				m_smallAsteroids[x].Spawn(_pos);
				y++;
			}
		}
	}
}

void AsteroidSpawner::CheckForCollisions(Bullet _bullets[], int _numBullets)
{
	/*for (int x = 0; x < _numBullets; x++)
	{
		if (_bullets[x].IsLive())
		{
			for (int y = 0; y < m_maxBigAst; y++)
			{
				if (m_bigAsteroids[y].IsLive())
				{
					if (m_bigAsteroids[y].CheckCollision(_bullets[x].GetPos(), _bullets[x].GetRadius()))
					{
						_bullets[x].SetLive(false);

						if (m_bigAsteroids[y].DealDamage(_bullets[x].GetDamage()))
						{
							SpawnAsteroids(4, 1, m_bigAsteroids[y].GetPos(), false);
						}
					}
				}
			}

			for (int y = 0; y < m_maxMedAst; y++)
			{
				if (m_medAsteroids[y].IsLive())
				{
					if (m_medAsteroids[y].CheckCollision(_bullets[x].GetPos(), _bullets[x].GetRadius()))
					{
						_bullets[x].SetLive(false);

						if (m_medAsteroids[y].DealDamage(_bullets[x].GetDamage()))
						{
							SpawnAsteroids(4, 2, m_medAsteroids[y].GetPos(), false);
						}
					}
				}
			}

			for (int y = 0; y < m_maxSmallAst; y++)
			{
				if (m_smallAsteroids[y].IsLive())
				{
					if (m_smallAsteroids[y].CheckCollision(_bullets[x].GetPos(), _bullets[x].GetRadius()))
					{
						_bullets[x].SetLive(false);

						m_smallAsteroids[y].DealDamage(_bullets[x].GetDamage());

					}
				}
			}
		}
	}*/
}

AsteroidSpawner::~AsteroidSpawner()
{
	delete[]m_bigAsteroids;
	delete[]m_medAsteroids;
	delete[]m_smallAsteroids;
}