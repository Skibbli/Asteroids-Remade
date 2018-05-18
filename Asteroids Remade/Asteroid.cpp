#include "stdafx.h"

#include "Asteroid.h"
#include "Resources.h"
#include "Time.h"
#include "Core.h"


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
	m_pos.x += m_vel * cos(m_direction) * Time::GetDeltaTime();
	m_pos.y += m_vel * sin(m_direction) * Time::GetDeltaTime();

	if (m_health <= 0)
		return false;

	else
		return true;
}

void Asteroid::Render()
{

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

void Asteroid::Spawn()
{

}

void Asteroid::TakeDmg(int _dmg)
{
	if (_dmg == -1)
		m_health = 0;

	else
		m_health -= _dmg;	
}

Asteroid::~Asteroid()
{

}

// Big Asteroid

BigAsteroid::BigAsteroid()
{
	m_maxHealth = 100;
	m_vel = 78;

	m_size = 1.85;
	m_radius = (m_frameWidth * m_size) / 2.3;

	m_collider = std::make_shared<Collider>(OBJECTS::PLAYER, m_pos, m_radius);
	Core::GetInstance().AddCollider(m_collider);
}

void BigAsteroid::Start()
{

}

void BigAsteroid::Render()
{
	if (m_rotDir)
		m_rotation = (ALLEGRO_PI * 2) - (ALLEGRO_PI * 2) * (m_frameNo / m_frameCount);

	else
		m_rotation = (ALLEGRO_PI * 2) * (m_frameNo / m_frameCount);

	al_draw_scaled_rotated_bitmap(m_bitmap.lock().get(), m_frameWidth / 2, m_frameHeight / 2, m_pos.x, m_pos.y, m_size, m_size, m_rotation, 0);

	m_frameNo++;

	if (m_frameNo > m_frameCount)
		m_frameNo = 0;

	/*al_draw_scaled_bitmap(m_bitmap.lock().get(), 0, 0, m_frameWidth, m_frameHeight, m_pos.x - ((m_frameWidth * m_size) / 2),
		m_pos.y - ((m_frameHeight * m_size) / 2), m_frameWidth * m_size, m_frameHeight * m_size, 0);*/
}

void BigAsteroid::Spawn(Vec2 _pos)
{
	m_pos = _pos;

	std::random_device rd;
	std::mt19937 eng(rd());

	std::uniform_int_distribution<> dirDistr(0, 360);
	m_direction = dirDistr(eng) * degToRad;

	m_rotDir = dirDistr(eng) % 2;

	std::uniform_int_distribution<> rotSpeedDistr(470, 530);

	m_frameCount = rotSpeedDistr(eng);
	m_frameNo = 0;

	m_isLive = true;
	m_collider.get()->SetIsLive(true);
	m_health = m_maxHealth;
}

BigAsteroid::~BigAsteroid()
{

}

// Medium Asteroid

MedAsteroid::MedAsteroid()
{
	m_maxHealth = 50;
	m_vel = 107.5;

	m_size = 1.325;
	m_radius = (m_frameWidth * m_size) / 2.3;

	m_collider = std::make_shared<Collider>(OBJECTS::PLAYER, m_pos, m_radius);
	Core::GetInstance().AddCollider(m_collider);	
}

void MedAsteroid::Start()
{

}

void MedAsteroid::Render()
{
	if (m_rotDir)
		m_rotation = (ALLEGRO_PI * 2) - (ALLEGRO_PI * 2) * (m_frameNo / m_frameCount);

	else
		m_rotation = (ALLEGRO_PI * 2) * (m_frameNo / m_frameCount);

	al_draw_scaled_rotated_bitmap(m_bitmap.lock().get(), m_frameWidth / 2, m_frameHeight / 2, m_pos.x, m_pos.y, m_size, m_size, m_rotation, 0);

	m_frameNo++;

	if (m_frameNo > m_frameCount)
		m_frameNo = 0;

	/*al_draw_scaled_bitmap(m_bitmap.lock().get(), 0, 0, m_frameWidth, m_frameHeight, m_pos.x - ((m_frameWidth * m_size) / 2),
		m_pos.y - ((m_frameHeight * m_size) / 2), m_frameWidth * m_size, m_frameHeight * m_size, 0);*/
}

void MedAsteroid::Spawn(Vec2 _pos)
{
	m_pos = _pos;

	std::random_device rd;
	std::mt19937 eng(rd());

	std::uniform_int_distribution<> dirDistr(0, 360);
	m_direction = dirDistr(eng) * degToRad;

	m_rotDir = dirDistr(eng) % 2;

	std::uniform_int_distribution<> rotSpeed(370, 430);
	
	m_frameCount = rotSpeed(eng);
	m_frameNo = 0;

	m_isLive = true;
	m_collider.get()->SetIsLive(true);
	m_health = m_maxHealth;
}

MedAsteroid::~MedAsteroid()
{

}

// Small Asteroid

SmallAsteroid::SmallAsteroid()
{
	m_maxHealth = 25;
	m_vel = 150.0;

	m_size = 0.85;
	m_radius = (m_frameWidth * m_size) / 2.3;

	m_collider = std::make_shared<Collider>(OBJECTS::PLAYER, m_pos, m_radius);
	Core::GetInstance().AddCollider(m_collider);
}

void SmallAsteroid::Start()
{

}

void SmallAsteroid::Render()
{
	if (m_rotDir)
		m_rotation = (ALLEGRO_PI * 2) - (ALLEGRO_PI * 2) * (m_frameNo / m_frameCount);

	else
		m_rotation = (ALLEGRO_PI * 2) * (m_frameNo / m_frameCount);

	al_draw_scaled_rotated_bitmap(m_bitmap.lock().get(), m_frameWidth / 2, m_frameHeight / 2, m_pos.x, m_pos.y, m_size, m_size, m_rotation, 0);

	m_frameNo++;

	if (m_frameNo > m_frameCount)
		m_frameNo = 0;

	/*al_draw_scaled_bitmap(m_bitmap.lock().get(), 0, 0, m_frameWidth, m_frameHeight, m_pos.x - ((m_frameWidth * m_size) / 2),
		m_pos.y - ((m_frameHeight * m_size) / 2), m_frameWidth * m_size, m_frameHeight * m_size, 0);*/
}

void SmallAsteroid::Spawn(Vec2 _pos)
{
	m_pos = _pos;

	std::random_device rd;
	std::mt19937 eng(rd());

	std::uniform_int_distribution<> dirDistr(0, 360);
	m_direction = dirDistr(eng) * degToRad;

	m_rotDir = dirDistr(eng) % 2;

	std::uniform_int_distribution<> rotSpeedDistr(270, 330);

	m_frameCount = rotSpeedDistr(eng);
	m_frameNo = 0;

	m_isLive = true;
	m_collider.get()->SetIsLive(true);
	m_health = m_maxHealth;
}

SmallAsteroid::~SmallAsteroid()
{

}