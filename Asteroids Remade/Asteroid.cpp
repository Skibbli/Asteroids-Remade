#include "stdafx.h"

#include "Asteroid.h"
#include "Resources.h"
#include "Time.h"


Asteroid::Asteroid()
{
	m_isLive = false;
	m_bitmap = Resources::GetInstance().LoadBmp("Asteroid.png");

	m_frameWidth = al_get_bitmap_width(m_bitmap.lock().get());
	m_frameHeight = al_get_bitmap_height(m_bitmap.lock().get());
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

void Asteroid::LimitCheck()
{
	float _width = 1000;
	float _height = 1000;

	if (m_pos.y < 0 - m_frameWidth * m_size / 2)
		m_pos.y = _height + m_frameWidth * m_size / 2;
	if (m_pos.y > _height + m_frameWidth * m_size / 2)
		m_pos.y = 0 - m_frameWidth * m_size / 2;
	if (m_pos.x > _width + m_frameWidth * m_size / 2)
		m_pos.x = 0 - m_frameWidth * m_size / 2;
	if (m_pos.x < 0 - m_frameWidth * m_size / 2)
		m_pos.x = _width + m_frameWidth * m_size / 2;

	if (m_direction > ALLEGRO_PI * 2)
		m_direction = 0;

	if (m_direction < 0)
		m_direction = ALLEGRO_PI * 2;
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
	m_vel = 1.55;

	m_size = 1.85;
	m_radius = (m_frameWidth * m_size) / 2;

	m_frameCount = 500;
	m_frameNo = 0;
}

void BigAsteroid::Start()
{

}

bool BigAsteroid::Update()
{
	m_pos.x += m_vel * cos(m_direction) * Time::GetDeltaTime() * 50;
	m_pos.y += m_vel * sin(m_direction) * Time::GetDeltaTime() * 50;

	return true;
}

void BigAsteroid::Render()
{
	al_draw_scaled_rotated_bitmap(m_bitmap.lock().get(), m_frameWidth / 2, m_frameHeight / 2, m_pos.x, m_pos.y, m_size, m_size, (ALLEGRO_PI * 2) * (m_frameNo / m_frameCount), 0);

	m_frameNo++;

	if (m_frameNo > m_frameCount)
		m_frameNo = 0;

	/*al_draw_scaled_bitmap(m_bitmap.lock().get(), 0, 0, m_frameWidth, m_frameHeight, m_pos.x - ((m_frameWidth * m_size) / 2),
		m_pos.y - ((m_frameHeight * m_size) / 2), m_frameWidth * m_size, m_frameHeight * m_size, 0);*/
}

BigAsteroid::~BigAsteroid()
{

}

// Medium Asteroid

MedAsteroid::MedAsteroid()
{
	m_maxHealth = 50;
	m_vel = 2.15;

	m_size = 1.325;
	m_radius = (m_frameWidth * m_size) / 2;

	m_frameCount = 400;
	m_frameNo = 0;
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
	al_draw_scaled_rotated_bitmap(m_bitmap.lock().get(), m_frameWidth / 2, m_frameHeight / 2, m_pos.x, m_pos.y, m_size, m_size, (ALLEGRO_PI * 2) * (m_frameNo / m_frameCount), 0);

	m_frameNo++;

	if (m_frameNo > m_frameCount)
		m_frameNo = 0;

	/*al_draw_scaled_bitmap(m_bitmap.lock().get(), 0, 0, m_frameWidth, m_frameHeight, m_pos.x - ((m_frameWidth * m_size) / 2),
		m_pos.y - ((m_frameHeight * m_size) / 2), m_frameWidth * m_size, m_frameHeight * m_size, 0);*/
}

MedAsteroid::~MedAsteroid()
{

}

// Small Asteroid

SmallAsteroid::SmallAsteroid()
{
	m_maxHealth = 25;
	m_vel = 3.0;

	m_size = 0.85;
	m_radius = (m_frameWidth * m_size) / 2;

	m_frameCount = 300;
	m_frameNo = 0;
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
	al_draw_scaled_rotated_bitmap(m_bitmap.lock().get(), m_frameWidth / 2, m_frameHeight / 2, m_pos.x, m_pos.y, m_size, m_size, (ALLEGRO_PI * 2) * (m_frameNo / m_frameCount), 0);

	m_frameNo++;

	if (m_frameNo > m_frameCount)
		m_frameNo = 0;

	/*al_draw_scaled_bitmap(m_bitmap.lock().get(), 0, 0, m_frameWidth, m_frameHeight, m_pos.x - ((m_frameWidth * m_size) / 2),
		m_pos.y - ((m_frameHeight * m_size) / 2), m_frameWidth * m_size, m_frameHeight * m_size, 0);*/
}

SmallAsteroid::~SmallAsteroid()
{

}