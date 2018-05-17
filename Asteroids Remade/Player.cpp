#include "stdafx.h"

#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "Resources.h"


Player::Player()
{

}

void Player::Start(Bullet *_bullets)
{
	m_bullets = _bullets;
	m_fireRate = 50;
	m_fireCD = 0;
	m_bulletSpeed = 5;
	m_dmg = 10;
	m_health = 100;
	m_lives = 3;
	m_score = 0;
	m_vel.x = m_vel.y = m_totalVelocity = 0.0f;
	m_direction = 270 * degToRad;
	m_maxVelocity = 5.0;
	m_acceleration = 0.25f;
	m_isFiring = false;

	m_pos.x = 500;
	m_pos.y = 500;

	m_bitmap = Resources::GetInstance().LoadBmp("ULTIMATE SHIP.png");

	m_frameWidth = al_get_bitmap_width(m_bitmap.lock().get());
	m_frameHeight = al_get_bitmap_height(m_bitmap.lock().get());

	m_boundRadius = m_frameWidth / 2;
}

bool Player::Update()
{
	m_pos.x += m_vel.x * Time::GetDeltaTime() * 50;
	m_pos.y += m_vel.y * Time::GetDeltaTime() * 50;

	if (m_totalVelocity > m_maxVelocity)
	{
		m_vel.x *= m_maxVelocity / m_totalVelocity;
		m_vel.y *= m_maxVelocity / m_totalVelocity;
	}

	if (m_isFiring)
	{
		return Fire();
	}

	else
		return false;
}

void Player::Input()
{
	bool moved = false;

	if (Input::GetKey(ALLEGRO_KEY_W))
	{
		m_vel.x += cos(m_direction) * m_acceleration;
		m_vel.y += sin(m_direction) * m_acceleration;

		m_totalVelocity = sqrt((m_vel.x * m_vel.x) + (m_vel.y * m_vel.y));
		moved = true;
	}

	if (Input::GetKey(ALLEGRO_KEY_S))
	{
		m_vel.x += -cos(m_direction) * m_acceleration;
		m_vel.y += -sin(m_direction) * m_acceleration;

		m_totalVelocity = sqrt((m_vel.x * m_vel.x) + (m_vel.y * m_vel.y));
		moved = true;
	}

	if (!moved)
		Deccelerate();

	else
	{
		if (m_totalVelocity > m_maxVelocity)
		{
			m_vel.x *= m_maxVelocity / m_totalVelocity;
			m_vel.y *= m_maxVelocity / m_totalVelocity;
		}
	}

	if (Input::GetKey(ALLEGRO_KEY_A))
		m_direction -= 0.05f;

	if (Input::GetKey(ALLEGRO_KEY_D))
		m_direction += 0.05f;

	if (Input::GetKeyDown(ALLEGRO_KEY_SPACE))
		m_isFiring = true;

	if (Input::GetKeyUp(ALLEGRO_KEY_SPACE))
		m_isFiring = false;	
}

bool Player::Fire()
{
	if (m_fireCD - m_fireRate < 0)
	{
		m_fireCD = 250;

		return true;
	}

	else
	{
		m_fireCD -= m_fireRate;
		return false;
	}
}

void Player::GetBulletDets(Bullet &_bullet)
{
	_bullet.Spawn(m_pos, m_direction, m_dmg);
}

void Player::Deccelerate()
{
	if (m_totalVelocity > 1.10 || m_totalVelocity < -1.10)
	{
		m_vel.x *= 0.975;
		m_vel.y *= 0.975;

		m_totalVelocity = sqrt((m_vel.x * m_vel.x) + (m_vel.y * m_vel.y));
	}		
}

void Player::Render()
{
	al_draw_rotated_bitmap(m_bitmap.lock().get(), m_frameWidth / 2, m_frameHeight / 2, m_pos.x, m_pos.y, m_direction, 0);
}

Player::~Player()
{

}