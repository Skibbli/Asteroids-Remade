#include "stdafx.h"

#include "Asteroid.h"
#include "Resources.h"

Asteroid::Asteroid()
{
	m_isLive = false;
	m_bitmap = Resources::GetInstance().LoadBmp("Asteroid.png");

	m_frameWidth = al_get_bitmap_width(m_bitmap.lock().get());
	m_frameHeight = al_get_bitmap_height(m_bitmap.lock().get());

	m_radius = m_frameWidth / 2;
}

void Asteroid::Start()
{

}

bool Asteroid::Update()
{
	return true;
}

void Asteroid::Render()
{

}

void Asteroid::Spawn(Vec2 _pos)
{
	m_pos = _pos;

	std::random_device rd;
	std::mt19937 eng(rd());
	
	std::uniform_int_distribution<> distr(0, 360);
	m_direction = distr(eng) * degToRad;

	m_isLive = true;
	m_health = m_maxHealth;
}

bool Asteroid::CheckCollision(Vec2 _pos, float _radius)
{
	Vec2 distance = m_pos - _pos;
	float length = glm::length(distance);

	if (length <= m_radius + _radius)
		return true;

	else
		return false;
}

bool Asteroid::DealDamage(int _dmg)
{
	m_health -= _dmg;

	if (m_health <= 0)
	{
		m_isLive = false;
		return true;
	}		

	else
		return false;
}

Asteroid::~Asteroid()
{

}

// Big Asteroid

BigAsteroid::BigAsteroid()
{
	m_maxHealth = 100;
	m_vel = 3;
}

void BigAsteroid::Start()
{

}

bool BigAsteroid::Update()
{
	m_pos.x += m_vel * cos(m_direction);
	m_pos.y += m_vel * sin(m_direction);

	return true;
}

void BigAsteroid::Render()
{
	al_draw_bitmap(m_bitmap.lock().get(), m_pos.x - m_frameWidth / 2, m_pos.y - m_frameHeight / 2, 0);

	//al_draw_scaled_bitmap(m_bitmap.lock().get(), 0, 0, m_frameWidth, m_frameHeight, m_pos.x - m_frameWidth / 2, m_pos.y - m_frameHeight / 2, m_frameWidth, m_frameHeight, 0);
	al_draw_circle(m_pos.x, m_pos.y, 2, al_map_rgb(255, 255, 0), 1);
}

BigAsteroid::~BigAsteroid()
{

}

// Medium Asteroid

MedAsteroid::MedAsteroid()
{
	m_maxHealth = 50;
	m_vel = 6;
}

void MedAsteroid::Start()
{

}

bool MedAsteroid::Update()
{
	m_pos.x += m_vel * cos(m_direction);
	m_pos.y += m_vel * sin(m_direction);

	return true;
}

void MedAsteroid::Render()
{
	//al_draw_bitmap(m_bitmap.lock().get(), m_pos.x - m_frameWidth / 2, m_pos.x - m_frameHeight / 2, 0);

	al_draw_scaled_bitmap(m_bitmap.lock().get(), 0, 0, m_frameWidth, m_frameHeight, m_pos.x - m_frameWidth / 4, m_pos.y - m_frameHeight / 4, m_frameWidth / 2, m_frameHeight / 2, 0);
	al_draw_circle(m_pos.x, m_pos.y, 2, al_map_rgb(255, 255, 0), 1);
}

MedAsteroid::~MedAsteroid()
{

}

// Small Asteroid

SmallAsteroid::SmallAsteroid()
{
	m_maxHealth = 25;
	m_vel = 10;
}

void SmallAsteroid::Start()
{

}

bool SmallAsteroid::Update()
{
	m_pos.x += m_vel * cos(m_direction);
	m_pos.y += m_vel * sin(m_direction);

	return true;
}

void SmallAsteroid::Render()
{
	//al_draw_bitmap(m_bitmap.lock().get(), m_pos.x - m_frameWidth / 2, m_pos.x - m_frameHeight / 2, 0);

	al_draw_scaled_bitmap(m_bitmap.lock().get(), 0, 0, m_frameWidth, m_frameHeight, m_pos.x - m_frameWidth / 6, m_pos.y - m_frameHeight / 6, m_frameWidth / 3, m_frameHeight / 3, 0);
	al_draw_circle(m_pos.x, m_pos.y, 2, al_map_rgb(255, 255, 0), 1);
}

SmallAsteroid::~SmallAsteroid()
{

}