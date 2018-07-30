#include "stdafx.h"

#include "Bullet.h"
#include "Time.h"
#include "Core.h"
#include "CircleCollider.h"
#include "Resources.h"


Bullet::Bullet()
{
	m_transform.m_direction = 0;
	m_distTravelled = 0;
	m_distLimit = 800;
	m_dmg = 0;	
}

void Bullet::Start(Enums::OBJECTS _type, std::string _imgName, int _dmg, float _vel)
{
	m_bitmap = Resources::GetInstance().LoadBmp(_imgName);
	m_radius = m_bitmap.s_frameWidth / 2.3;

	m_collisionFX = Resources::GetInstance().LoadSFXSample("Bullet Collision.ogg");

	m_collider = std::make_shared<CircleCollider>(_type, m_transform.m_pos, m_dmg, m_radius);

	Core::GetInstance().AddCollider(m_collider);

	m_dmg = _dmg;
	m_vel = _vel;

	m_bulletType = _type;
}

// Updates bullet position and sets false if travelled beyond distance limit
bool Bullet::Update()
{
	m_transform.m_pos.x += m_vel * cos(m_transform.m_direction) * Time::GetDeltaTime();
	m_transform.m_pos.y += m_vel * sin(m_transform.m_direction) * Time::GetDeltaTime();

	LimitCheck();

	m_collider->Update(m_transform.m_pos);

	m_distTravelled += m_vel * Time::GetDeltaTime();

	if (m_distTravelled > m_distLimit)
	{
		m_isLive = false;
		m_collider->SetIsLive(false);
	}

	return true;
}

void Bullet::Render()
{
	al_draw_rotated_bitmap(m_bitmap.GetBitmap(), m_bitmap.s_frameWidth / 2, m_bitmap.s_frameHeight / 2, m_transform.m_pos.x, m_transform.m_pos.y, m_transform.m_direction, 0);
}

// Spawns bullets with given parameters. Inv is for the big gun to prevent bullet despawning on collision
void Bullet::Spawn(Vec2 _pos, float _dir, float _vel, bool _inv)
{
	m_transform.m_pos = _pos;
	m_transform.m_direction = _dir;
	m_vel = _vel;
	m_inv = _inv;
	m_collider->SetDamage(m_dmg);
	m_distTravelled = 0;
	m_isLive = true;
	m_collider->SetIsLive(true);
	m_collider->Update(m_transform.m_pos);
}

void Bullet::Despawn()
{
	m_isLive = false;
	m_collider->SetIsLive(false);
}

// Checks for and processes collisions recorded this frame
void Bullet::CheckCollisions()
{
	std::vector<Collision> collisions = m_collider->GetCollisions();

	for (Collision col : collisions)
	{
		if (m_bulletType == Enums::OBJECTS::PLAYER_BULLET)
		{
			if (col.s_collTypeHit == Enums::OBJECTS::ASTEROID || col.s_collTypeHit == Enums::OBJECTS::UFO)
			{
				// Inv is for the big gun so that bullets don't despawn on collision
				if (!m_inv)
				{
					m_isLive = false;
					m_collider->SetIsLive(false);
				}

				m_collisionFX.lock()->PlaySample();
			}
		}

		else if (m_bulletType == Enums::OBJECTS::UFO_BULLET)
		{
			if (col.s_collTypeHit == Enums::OBJECTS::PLAYER)
			{
				m_isLive = false;
				m_collider->SetIsLive(false);
				m_collisionFX.lock()->PlaySample();
			}
		}
	}

	m_collider->ResetCollisions();
}

void Bullet::Shutdown()
{
	m_collider.reset();
}

Bullet::~Bullet() {}