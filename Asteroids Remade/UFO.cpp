#include "stdafx.h"

#include "UFO.h"
#include "CircleCollider.h"
#include "Core.h"
#include "Maths.h"
#include "Time.h"
#include "Resources.h"
#include "Bullet.h"
#include "Player.h"


UFO::UFO()
{
	m_bitmap = Resources::GetInstance().LoadBmp("UFO Ship.png");
	m_vel = 100;
	m_distLimit = 3000;

	m_numBullets = 15;
	m_bullets = new Bullet[m_numBullets];
	m_bulletsLive = false;

	m_health = 3;

	m_fireCD = 200;
	m_fireCounter = 0;
	m_fireRate = 2;
	m_bulletDamage = 10;
	m_bulletSpeed = 300;
}

void UFO::Start(Player *_player)
{
	m_collider = std::make_shared<CircleCollider>(Enums::OBJECTS::UFO, m_transform.m_pos, 500, m_bitmap.s_frameWidth / 2);
	Core::GetInstance().AddCollider(m_collider);

	for (int i = 0; i < m_numBullets; i++)
	{
		m_bullets[i].Start(Enums::OBJECTS::UFO_BULLET, "UFOBullet.png", m_bulletDamage, m_bulletSpeed);
	}

	m_player = _player;
}

// Updates UFO position, checks if collisions recorded with other objects and returns whether the UFO is alive to the UFO spawner
bool UFO::Update()
{
	m_diedThisFrame = false;

	if (m_isLive)
	{
		m_transform.m_pos.x += m_vel * cos(m_transform.m_direction) * Time::GetDeltaTime();
		m_transform.m_pos.y += m_vel * sin(m_transform.m_direction) * Time::GetDeltaTime();

		LimitCheck();

		m_collider->Update(m_transform.m_pos);

		m_distTravelled += m_vel * Time::GetDeltaTime();
		m_dirChangeDist += m_vel * Time::GetDeltaTime();

		if (m_distTravelled > m_distLimit)
		{
			m_isLive = false;
			m_collider->SetIsLive(false);
		}

		// Change direction every 250 pixels
		if (m_dirChangeDist > 250)
		{
			if (GenRandNo(0, 1))
			{
				m_transform.m_direction += 0.425;
			}

			else
			{
				m_transform.m_direction -= 0.425;
			}

			m_dirChangeDist = 0;
		}

		Fire();

		CheckCollisions();
	}

	for (int i = 0; i < m_numBullets; i++)
	{
		if (m_bullets[i].GetIsLive())
		{
			m_bullets[i].Update();
			m_bullets[i].CheckCollisions();
		}
	}

	return m_diedThisFrame;
}

void UFO::Render()
{
	if (m_isLive)
	{
		al_draw_bitmap(m_bitmap.GetBitmap(), m_transform.m_pos.x - m_bitmap.s_frameWidth / 2, m_transform.m_pos.y - m_bitmap.s_frameHeight / 2, 0);
	}

	if (m_bulletsLive)
	{
		for (int i = 0; i < m_numBullets; i++)
		{
			if (m_bullets[i].GetIsLive())
			{
				m_bullets[i].Render();
			}
		}
	}
}

Vec2 UFO::GetPos()
{
	return m_transform.m_pos;
}

// Spawns the UFO at a random position outside of the window
void UFO::Spawn()
{
	m_isLive = true;
	m_health = 3;

	int x = GenRandNo(0, 1);

	if (x)
	{
		float x = GenRandNo(0, m_defWinWidth);
		m_transform.m_pos.x = x;
		m_transform.m_pos.y = m_defWinHeight + 200;
	}

	else
	{
		float y = GenRandNo(0, m_defWinHeight);
		m_transform.m_pos.y = y;
		m_transform.m_pos.x = m_defWinWidth + 200;
	}

	m_transform.m_direction = GenRandNo(0, 360) * degToRad;

	m_collider->SetIsLive(true);
	m_collider->Update(m_transform.m_pos);

	m_distTravelled = 0.0f;
	m_dirChangeDist = 0.0f;

	for (int i = 0; i < m_numBullets; i++)
	{
		m_bullets[i].Despawn();	
	}
}

// Checks if bullet is ready to fire and spawns a bullet if it is
void UFO::Fire()
{
	if (m_fireCD - m_fireCounter < 0)
	{
		for (int i = 0; i < m_numBullets; i++)
		{
			if (!m_bullets[i].GetIsLive())
			{
				float direction = atan2(m_player->GetPos().y - m_transform.m_pos.y, m_player->GetPos().x - m_transform.m_pos.x);
				m_bullets[i].Spawn(m_transform.m_pos, direction, m_bulletSpeed, false);
				m_fireCounter = 0;
				m_bulletsLive = true;

				break;
			}
		}
	}

	else
	{
		m_fireCounter += m_fireRate;
	}
}

// Checks for and processes collisions recorded this frame
void UFO::CheckCollisions()
{
	std::vector<Collision> collisions = m_collider->GetCollisions();

	for (Collision col : collisions)
	{
		switch (col.s_collTypeHit)
		{
			case Enums::OBJECTS::PLAYER_BULLET:
			{
				m_health -= 1;

				if (m_health == 0)
				{
					m_isLive = false;
					m_diedThisFrame = true;
					m_collider->SetIsLive(false);
				}
			}
			break;
			case Enums::OBJECTS::PLAYER:
			{
				m_isLive = false;
				m_diedThisFrame = true;
				m_collider->SetIsLive(false);
			}
			break;
			default: {}
		}
	}

	m_collider->ResetCollisions();
}

void UFO::Shutdown()
{
	m_player = nullptr;

	for (int i = 0; i < m_numBullets; i++)
	{
		m_bullets[i].Shutdown();
	}

	delete[] m_bullets;

	m_collider.reset();
}

UFO::~UFO() {}