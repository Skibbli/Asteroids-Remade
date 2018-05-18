#include "stdafx.h"

#include "Bullet.h"
#include "Resources.h"
#include "Time.h"
#include "Core.h"


Bullet::Bullet()
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_direction = 0;
	m_vel = 340;
	m_distTravelled = 0;
	m_distLimit = 800;
	m_dmg = 0;
	m_isLive = false;
	m_bitmap = Resources::GetInstance().LoadBmp("Bullet.png");

	m_frameWidth = al_get_bitmap_width(m_bitmap.lock().get());
	m_frameHeight = al_get_bitmap_height(m_bitmap.lock().get());
	m_radius = m_frameWidth / 2.3;

	m_collider = std::make_shared<Collider>(OBJECTS::PLAYER, m_pos, m_radius);
	Core::GetInstance().AddCollider(m_collider);
}

void Bullet::Start()
{

}

bool Bullet::Update()
{
	m_pos.x += m_vel * cos(m_direction) * Time::GetDeltaTime();
	m_pos.y += m_vel * sin(m_direction) * Time::GetDeltaTime();

	m_distTravelled += m_vel * Time::GetDeltaTime();

	if (m_distTravelled > m_distLimit)
		return false;

	else
		return true;
}

void Bullet::Render()
{
	al_draw_rotated_bitmap(m_bitmap.lock().get(), m_frameWidth / 2, m_frameHeight / 2, m_pos.x, m_pos.y, m_direction, 0);
}

bool Bullet::IsLive()
{
	return m_isLive;
}

void Bullet::Spawn(Vec2 _pos, float _dir, int _dmg)
{
	m_pos = _pos;
	m_direction = _dir;
	m_dmg = _dmg;
	m_distTravelled = 0;
	m_isLive = true;
}

float Bullet::GetRadius()
{
	return m_radius;
}

void Bullet::SetLive(bool _isLive)
{
	m_isLive = _isLive;
}

int Bullet::GetDamage()
{
	return m_dmg;
}

Bullet::~Bullet()
{

}