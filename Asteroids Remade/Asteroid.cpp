#include "stdafx.h"

#include "Asteroid.h"
#include "Time.h"
#include "CircleCollider.h"
#include "Core.h"
#include "Resources.h"
#include "Maths.h"


Asteroid::Asteroid()
{
	m_bitmap = Resources::GetInstance().LoadBmp("Asteroid.png");

	m_bitmap.s_frameWidth = al_get_bitmap_width(m_bitmap.GetBitmap());
	m_bitmap.s_frameHeight = al_get_bitmap_height(m_bitmap.GetBitmap());
}

void Asteroid::Start()
{
	m_collider = std::make_shared<CircleCollider>(Enums::OBJECTS::ASTEROID, m_transform.m_pos, m_colDmg, m_radius);
	Core::GetInstance().AddCollider(m_collider);
}

// Updates asteroid position, adjusts animation rotation and despawns it if health is reduced to zero
bool Asteroid::Update()
{
	m_transform.m_pos.x += m_vel * cos(m_transform.m_direction) * Time::GetDeltaTime();
	m_transform.m_pos.y += m_vel * sin(m_transform.m_direction) * Time::GetDeltaTime();

	m_collider->Update(m_transform.m_pos);

	LimitCheck();

	CheckCollisions();

	// Adjusts rotation amount
	if (m_rotDir)
	{
		m_rotation = (ALLEGRO_PI * 2) - (ALLEGRO_PI * 2) * (m_frameNo / m_frameCount);
	}

	else
	{
		m_rotation = (ALLEGRO_PI * 2) * (m_frameNo / m_frameCount);
	}

	m_frameNo++;

	if (m_frameNo > m_frameCount)
	{
		m_frameNo = 0;
	}

	if (m_health <= 0)
	{
		m_isLive = false;
		m_collider->SetIsLive(false);

		return false;
	}

	else
		return true;
}

void Asteroid::Render()
{
	al_draw_scaled_rotated_bitmap(m_bitmap.GetBitmap(), 0.5 * m_bitmap.s_frameWidth, 0.5 * m_bitmap.s_frameHeight, m_transform.m_pos.x, m_transform.m_pos.y, m_size, m_size, m_rotation, 0);
}

void Asteroid::Spawn() {}

Vec2 Asteroid::GetPos()
{
	return m_transform.m_pos;
}

// Checks for and processes collisions recorded this frame
void Asteroid::CheckCollisions()
{
	std::vector<Collision> collisions = m_collider->GetCollisions();

	for (Collision coll : collisions)
	{
		if (coll.s_collTypeHit == Enums::OBJECTS::PLAYER_BULLET)
		{
			m_health -= coll.s_dmg;
		}

		else if (coll.s_collTypeHit == Enums::OBJECTS::PLAYER)
		{
			m_health = 0;
		}

		else
			break;
	}

	m_collider->ResetCollisions();
}

// Keeps asteroid inside the window and rotation amount within limits
void Asteroid::LimitCheck()
{
	if (m_transform.m_pos.y < 0 - m_bitmap.s_frameHeight * m_size / 2)
		m_transform.m_pos.y = m_defWinHeight + (m_bitmap.s_frameHeight * m_size / 2);
	if (m_transform.m_pos.y > m_defWinHeight + (m_bitmap.s_frameHeight * m_size / 2))
		m_transform.m_pos.y = 0 - m_bitmap.s_frameHeight * m_size / 2;
	if (m_transform.m_pos.x > m_defWinWidth + (m_bitmap.s_frameWidth * m_size / 2))
		m_transform.m_pos.x = 0 - m_bitmap.s_frameWidth * m_size / 2;
	if (m_transform.m_pos.x < 0 - m_bitmap.s_frameWidth * m_size / 2)
		m_transform.m_pos.x = m_defWinWidth + (m_bitmap.s_frameWidth * m_size / 2);

	if (m_transform.m_direction > ALLEGRO_PI * 2)
		m_transform.m_direction = 0;

	if (m_transform.m_direction < 0)
		m_transform.m_direction = ALLEGRO_PI * 2;
}

void Asteroid::Shutdown()
{
	m_collider.reset();
}

Asteroid::~Asteroid() {}

// Big Asteroid

BigAsteroid::BigAsteroid()
{
	m_maxHealth = 60;
	m_vel = 65;
	m_colDmg = 100;

	m_size = 1.85;
	m_sizeID = 5;
	m_radius = (m_bitmap.s_frameWidth * m_size) / 2.3;
}

// Spawns asteroid at the given position with a random rotation direction and speed
void BigAsteroid::Spawn(Vec2 _pos)
{
	m_transform.m_pos = _pos;

	int dir = GenRandNo(0, 360);
	m_transform.m_direction = dir * degToRad;

	m_rotDir = dir % 2;

	m_frameCount = GenRandNo(470, 530);
	m_frameNo = 0;

	m_isLive = true;
	m_collider->SetIsLive(true);
	m_collider->Update(m_transform.m_pos);
	m_health = m_maxHealth;
}

BigAsteroid::~BigAsteroid() {}

// Medium Asteroid

MedAsteroid::MedAsteroid()
{
	m_maxHealth = 40;
	m_vel = 95;
	m_colDmg = 50;

	m_size = 1.325;
	m_sizeID = 3;
	m_radius = (m_bitmap.s_frameWidth * m_size) / 2.3;
}

// Spawns asteroid at the given position with a random rotation direction and speed
void MedAsteroid::Spawn(Vec2 _pos)
{
	m_transform.m_pos  = _pos;

	int dir = GenRandNo(0, 360);
	m_transform.m_direction = dir * degToRad;

	m_rotDir = dir % 2;

	m_frameCount = GenRandNo(370, 430);
	m_frameNo = 0;

	m_isLive = true;
	m_collider->SetIsLive(true);
	m_collider->Update(m_transform.m_pos);
	m_health = m_maxHealth;
}

MedAsteroid::~MedAsteroid() {}

// Small Asteroid

SmallAsteroid::SmallAsteroid()
{
	m_maxHealth = 20;
	m_vel = 130.0;
	m_colDmg = 25;

	m_size = 0.85;
	m_sizeID = 1;
	m_radius = (m_bitmap.s_frameWidth * m_size) / 2.3;
}

// Spawns asteroid at the given position with a random rotation direction and speed
void SmallAsteroid::Spawn(Vec2 _pos)
{
	m_transform.m_pos = _pos;

	int dir = GenRandNo(0, 360);
	m_transform.m_direction = dir * degToRad;

	m_rotDir = dir % 2;

	m_frameCount = GenRandNo(270, 330);
	m_frameNo = 0;

	m_isLive = true;
	m_collider->SetIsLive(true);
	m_collider->Update(m_transform.m_pos);
	m_health = m_maxHealth;
}

SmallAsteroid::~SmallAsteroid() {}