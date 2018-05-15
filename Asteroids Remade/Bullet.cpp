#include "stdafx.h"

#include "Bullet.h"
#include "Resources.h"


Bullet::Bullet()
{
	m_pos.x = 0;
	m_pos.y = 0;
	m_direction = 0;
	m_vel = 10;
	m_distTravelled = 0;
	m_distLimit = 800;
	m_dmg = 0;
	m_isLive = false;
	m_bitmap = Resources::GetInstance().LoadBmp("Bullet.png");

	m_frameWidth = al_get_bitmap_width(m_bitmap.lock().get());
	m_frameHeight = al_get_bitmap_height(m_bitmap.lock().get());
}

void Bullet::Start()
{

}

bool Bullet::Update()
{
	m_pos.x += m_vel * cos(m_direction);
	m_pos.y += m_vel * sin(m_direction);

	m_distTravelled += m_vel;

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