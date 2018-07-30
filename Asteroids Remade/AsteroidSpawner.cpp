#include "stdafx.h"

#include "AsteroidSpawner.h"
#include "Asteroid.h"
#include "Core.h"
#include "Maths.h"
#include "Time.h"
#include "Resources.h"
#include "Player.h"


AsteroidSpawner::AsteroidSpawner()
{
	m_defWinWidth = 1000;
	m_defWinHeight = 1000;

	m_font = Resources::GetInstance().LoadFont("Are You Freakin Serious.ttf", 80);

	m_maxBigAst = 50;
	m_maxMedAst = 100;
	m_maxSmallAst = 150;
	m_maxExp = 10;

	m_bigAsteroids = new BigAsteroid[m_maxBigAst];
	m_medAsteroids = new MedAsteroid[m_maxMedAst];
	m_smallAsteroids = new SmallAsteroid[m_maxSmallAst];

	m_explosions = new Explosion[m_maxExp];

	m_waveCD = 2.00f;
	m_waveCDCounter = 0.00f;
	m_waveActive = false;
	m_waveAnnounce = false;
	m_waveNo = 0;
	m_fontAlpha = 0.0f;
	m_fadeIn = true;

	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
}

void AsteroidSpawner::Start(Player* _player)
{
	m_player = _player;

	for (int x = 0; x < m_maxBigAst; x++)
	{
		m_bigAsteroids[x].Start();
	}

	for (int x = 0; x < m_maxMedAst; x++)
	{
		m_medAsteroids[x].Start();
	}

	for (int x = 0; x < m_maxSmallAst; x++)
	{
		m_smallAsteroids[x].Start();
	}
}

void AsteroidSpawner::Update()
{
	bool bigAstAlive = false;
	bool medAstAlive = false;
	bool smallAstAlive = false;

	// Updates live asteroids and spawns new asteroids if existing ones get destroyed
	if (m_waveActive)
	{
		for (int x = 0; x < m_maxBigAst; x++)
		{
			if (m_bigAsteroids[x].GetIsLive())
			{
				if (!m_bigAsteroids[x].Update())
				{
					SpawnAsteroids(3, 1, m_bigAsteroids[x].GetPos(), false);
					SpawnExplosion(m_bigAsteroids[x].GetPos(), 1.5);
					m_player->AddScore(100);
				}

				else
					bigAstAlive = true;
			}
		}

		for (int x = 0; x < m_maxMedAst; x++)
		{
			if (m_medAsteroids[x].GetIsLive())
			{
				if (!m_medAsteroids[x].Update())
				{
					SpawnAsteroids(4, 2, m_medAsteroids[x].GetPos(), false);
					SpawnExplosion(m_medAsteroids[x].GetPos(), 1.1);
					m_player->AddScore(40);
				}

				else
					medAstAlive = true;
			}
		}

		for (int x = 0; x < m_maxSmallAst; x++)
		{
			if (m_smallAsteroids[x].GetIsLive())
			{
				if (!m_smallAsteroids[x].Update())
				{
					SpawnExplosion(m_smallAsteroids[x].GetPos(), 0.8);
					m_player->AddScore(20);
				}

				else
					smallAstAlive = true;
			}
		}
	}

	if (!bigAstAlive && !medAstAlive && !smallAstAlive)
	{
		m_waveActive = false;
	}

	// If no asteroids are alive update between-wave timer and spawn asteroids when it is over
	if (!m_waveActive)
	{
		m_waveCDCounter += Time::GetDeltaTime();

		if (m_waveCDCounter > m_waveCD)
		{
			SpawnAsteroids(3 + m_waveNo, 0, Vec2(0, 0), true);
			m_waveCDCounter = 0.00f;
			m_waveAnnounce = true;
		}
	}

	// Update any live explosions
	for (int i = 0; i < m_maxExp; i++)
	{
		if (m_explosions[i].GetIsLive())
		{
			m_explosions[i].Update();
		}
	}

	// If start of wave is being announced fade font out
	if (m_waveAnnounce)
	{
		FadeFont();
	}		
}

void AsteroidSpawner::Render()
{
	if (m_waveAnnounce)
	{
		al_draw_textf(m_font.lock().get(), al_map_rgba(255, 255, 255, m_fontAlpha), 500, 350, ALLEGRO_ALIGN_CENTRE, "Wave %i", m_waveNo);
	}

	for (int x = 0; x < m_maxBigAst; x++)
	{
		if (m_bigAsteroids[x].GetIsLive()) 
		{
			m_bigAsteroids[x].Render();
		}
	}

	for (int x = 0; x < m_maxMedAst; x++)
	{
		if (m_medAsteroids[x].GetIsLive())
		{
			m_medAsteroids[x].Render();
		}
	}

	for (int x = 0; x < m_maxSmallAst; x++)
	{
		if (m_smallAsteroids[x].GetIsLive())
		{
			m_smallAsteroids[x].Render();
		}
	}

	for (int i = 0; i < m_maxExp; i++)
	{
		if (m_explosions[i].GetIsLive())
		{
			m_explosions[i].Render();
		}
	}
}

// Spawn num of asteroids of given size, either in a random position or the position given
// Uses object pooling for efficiency
void AsteroidSpawner::SpawnAsteroids(int _num, int _size, Vec2 _pos, bool _random)
{
	int y = 0;

	if (_size == 0)
	{
		m_waveActive = true;
		m_waveNo++;

		for (int x = 0; x < m_maxBigAst && y < _num; x++)
		{
			if (!m_bigAsteroids[x].GetIsLive())
			{
				if (_random)
				{
					int x = GenRandNo(0, 1);

					if (x)
					{
						float x = GenRandNo(0, m_defWinWidth);
						_pos.x = x;
						_pos.y = m_defWinHeight + 200;
					}

					else
					{
						float y = GenRandNo(0, m_defWinHeight);
						_pos.y = y;
						_pos.x = m_defWinWidth + 200;
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
			if (!m_medAsteroids[x].GetIsLive())
			{
				if (_random)
				{
					if (x)
					{
						float x = GenRandNo(0, m_defWinWidth);
						_pos.x = x;
						_pos.y = m_defWinHeight + 200;
					}

					else
					{
						float y = GenRandNo(0, m_defWinHeight);
						_pos.y = y;
						_pos.x = m_defWinWidth + 200;
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
			if (!m_smallAsteroids[x].GetIsLive())
			{
				if (_random)
				{
					if (x)
					{
						float x = GenRandNo(0, m_defWinWidth);
						_pos.x = x;
						_pos.y = m_defWinHeight + 200;
					}

					else
					{
						float y = GenRandNo(0, m_defWinHeight);
						_pos.y = y;
						_pos.x = m_defWinWidth + 200;
					}
				}

				m_smallAsteroids[x].Spawn(_pos);
				y++;
			}
		}
	}
}

void AsteroidSpawner::SpawnExplosion(Vec2 _pos, float _size)
{
	for (int i = 0; i < m_maxExp; i++)
	{
		if (!m_explosions[i].GetIsLive())
		{
			m_explosions[i].Spawn(_pos, _size);
			break;
		}
	}
}

// Fade wave announcement font out
void AsteroidSpawner::FadeFont()
{
	if (m_fadeIn)
	{
		m_fontAlpha += 2;

		if (m_fontAlpha > 255)
		{
			m_fadeIn = false;
			m_fontAlpha = 255;
		}
	}

	else
	{
		m_fontAlpha -= 2;

		if (m_fontAlpha < 0)
		{
			m_waveAnnounce = false;
			m_fontAlpha = 0;
			m_fadeIn = true;
		}
	}
}

void AsteroidSpawner::Shutdown()
{
	for (int x = 0; x < m_maxBigAst; x++)
	{
		m_bigAsteroids[x].Shutdown();
	}

	for (int x = 0; x < m_maxMedAst; x++)
	{
		m_medAsteroids[x].Shutdown();
	}

	for (int x = 0; x < m_maxSmallAst; x++)
	{
		m_smallAsteroids[x].Shutdown();
	}

	m_player = nullptr;

	delete[] m_bigAsteroids;
	delete[] m_medAsteroids;
	delete[] m_smallAsteroids;
}

AsteroidSpawner::~AsteroidSpawner() {}