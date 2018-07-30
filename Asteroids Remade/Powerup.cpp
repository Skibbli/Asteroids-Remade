#include "stdafx.h"

#include "Powerup.h"
#include "Core.h"
#include "Time.h"
#include "Resources.h"
#include "Maths.h"


// Base powerup
Powerup::Powerup()
{
	m_distLimit = 2500;
	m_distTravelled = 0;

	m_vel = 135;

	m_bitmap = Resources::GetInstance().LoadBmp("Powerup1.png");
	m_pupFX = Resources::GetInstance().LoadSFXSample("Power Up!.ogg");
}

void Powerup::Start()
{
	m_collider = std::make_shared<RectangleCollider>(Enums::OBJECTS::EXTRA_LIFE, m_transform.m_pos, 0, m_bitmap.s_frameWidth, m_bitmap.s_frameHeight);
	Core::GetInstance().AddCollider(m_collider);
}

// Updates position of powerup, checks for collisions and returns if live or not
bool Powerup::Update()
{
	m_transform.m_pos.x += m_vel * cos(m_transform.m_direction) * Time::GetDeltaTime();
	m_transform.m_pos.y += m_vel * sin(m_transform.m_direction) * Time::GetDeltaTime();

	LimitCheck();

	m_collider->Update(m_transform.m_pos, 0.00f);

	m_distTravelled += m_vel * Time::GetDeltaTime();

	if (m_distTravelled > m_distLimit)
	{
		m_isLive = false;
		m_collider->SetIsLive(false);
	}

	CheckCollisions();

	return true;
}

void Powerup::Render()
{
	al_draw_bitmap(m_bitmap.GetBitmap(), m_transform.m_pos.x - m_bitmap.s_frameWidth / 2, m_transform.m_pos.y - m_bitmap.s_frameHeight / 2, 0);
}

// Spawns the specified type of powerup in a random position outside of the window
void Powerup::Spawn(int _type)
{
	m_isLive = true;

	m_distTravelled = 0;

	int x = GenRandNo(0, 1);

	if (x)
	{
		float x = GenRandNo(0, m_displaySize.s_width);
		m_transform.m_pos.x = x;
		m_transform.m_pos.y = m_displaySize.s_height + 200;
	}

	else
	{
		float y = GenRandNo(0, m_displaySize.s_height);
		m_transform.m_pos.y = y;
		m_transform.m_pos.x = m_displaySize.s_width + 200;
	}

	m_transform.m_direction = GenRandNo(0, 360) * degToRad;

	m_collider->SetIsLive(true);
	m_collider->SetColliderType((Enums::OBJECTS)(_type + 4));
	m_collider->Update(m_transform.m_pos, 0.00f);

	m_bitmap = Resources::GetInstance().LoadBmp("Powerup" + std::to_string(_type) + ".png");
}

// Checks for collisions recorded this frame and processes them
void Powerup::CheckCollisions()
{
	std::vector<Collision> collisions = m_collider->GetCollisions();

	for (Collision col : collisions)
	{
		if (col.s_collTypeHit == Enums::OBJECTS::PLAYER)
		{
			m_pupFX.lock()->PlaySample();
			m_isLive = false;
			m_collider->SetIsLive(false);
		}
	}

	m_collider->ResetCollisions();
}

void Powerup::Shutdown()
{
	m_collider.reset();
}

Powerup::~Powerup() {}