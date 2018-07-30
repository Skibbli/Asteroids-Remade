#include "stdafx.h"

#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "CircleCollider.h"
#include "Core.h"
#include "Resources.h"
#include "Title.h"
#include "GameOver.h"


Player::Player()
{
	m_lives = 3;
	m_score = 0;
	m_vel.x = m_vel.y = m_totalVelocity = 0.0f;
	m_transform.m_direction = 270 * degToRad;
	m_maxVelocity = 250.0;
	m_acceleration = 14.0f;

	// Create the weapons used by the player
	m_weapPUP = false;
	m_guns.push_back(new RegGun());
	m_guns.push_back(new DoubleGun());
	m_guns.push_back(new BigGun());
	m_guns.push_back(new MultiGun());

	m_weaponCD = 8.0f;
	m_activeGun = 0;
	m_firing = false;

	m_tempInv = false;
	m_tempInvCD = 3.0f;
	m_tempInvTimer = 0.0f;

	m_transform.m_pos.x = 500;
	m_transform.m_pos.y = 500;

	m_bitmap = Resources::GetInstance().LoadBmp("ULTIMATE SHIP.png");
	m_font = Resources::GetInstance().LoadFont("Are You Freakin Serious.ttf", 30);

	m_bitmap.s_frameWidth = al_get_bitmap_width(m_bitmap.GetBitmap());
	m_bitmap.s_frameHeight = al_get_bitmap_height(m_bitmap.GetBitmap());

	m_boundRadius = m_bitmap.s_frameWidth / 2;
}

void Player::Start()
{
	m_collider = std::make_shared<CircleCollider>(Enums::OBJECTS::PLAYER, m_transform.m_pos, 500, m_bitmap.s_frameWidth / 2);
	Core::GetInstance().AddCollider(m_collider);

	m_collider->SetIsLive(true);

	for (Weapon *weap : m_guns)
	{
		weap->Start();
	}
}

bool Player::Update()
{
	m_transform.m_pos.x += m_vel.x * Time::GetDeltaTime();
	m_transform.m_pos.y += m_vel.y * Time::GetDeltaTime();

	LimitCheck();

	for (Weapon *weap : m_guns)
	{
		weap->Update(m_transform.m_pos, m_transform.m_direction, (m_totalVelocity / m_maxVelocity));
	}

	m_collider->Update(m_transform.m_pos);

	CheckCollisions();

	if (m_explosion.GetIsLive())
	{
		m_explosion.Update();
	}

	// Updates weapon powerup counters
	if (m_weapPUP)
	{
		m_weaponTimer += Time::GetDeltaTime();

		if (m_weaponTimer > m_weaponCD)
		{
			m_weaponTimer = 0;
			m_guns.at(m_activeGun)->SetIsFiring(false);
			m_activeGun = 0;

			if (m_firing)
			{
				m_guns.at(m_activeGun)->SetIsFiring(true);
			}

			m_weapPUP = false;
		}
	}

	// Updates temp invincibility counter
	if (m_tempInv)
	{
		m_tempInvTimer += Time::GetDeltaTime();

		if (m_tempInvTimer > m_tempInvCD)
		{
			m_tempInvTimer = 0;
			m_tempInv = false;
		}
	}

	if (m_lives < 0)
	{
		Core::GetInstance().GetStateManager().AddState(std::make_shared<GameOver>(m_score));

		return false;
	}

	else
		return true;
}

void Player::Render()
{
	al_draw_rotated_bitmap(m_bitmap.GetBitmap(), 0.5 *m_bitmap.s_frameWidth, 0.5 * m_bitmap.s_frameHeight, m_transform.m_pos.x, m_transform.m_pos.y, m_transform.m_direction, 0);

	for (Weapon *weap : m_guns)
	{
		weap->Render();
	}

	if (m_tempInv)
	{
		al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 0.5 * m_defWinWidth, 0.5 * m_defWinHeight, ALLEGRO_ALIGN_CENTRE, "Temporary invincibility for %i", int(4 - m_tempInvTimer));
	}

	al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 0.020 * m_defWinWidth, 0.90 * m_defWinHeight, ALLEGRO_ALIGN_LEFT, "Score: %i", m_score);
	al_draw_textf(m_font.lock().get(), al_map_rgb(255, 255, 255), 0.020 * m_defWinWidth, 0.95 * m_defWinHeight, ALLEGRO_ALIGN_LEFT, "Lives:");

	for (int i = 0; i < m_lives; i++)
	{
		al_draw_scaled_rotated_bitmap(m_bitmap.GetBitmap(), 0.5 * m_bitmap.s_frameWidth, 0.5 * m_bitmap.s_frameHeight, 0.100 * m_defWinWidth + ((i * m_bitmap.s_frameWidth) + 0.005 * m_defWinWidth), 0.96 * m_defWinHeight, 0.7, 0.7, 270 * degToRad, 0);
	}

	if (m_explosion.GetIsLive())
	{
		m_explosion.Render();
	}
}

// Updates player velocity and firing status based on player input
void Player::Input()
{
	bool moved = false;

	if (Input::GetInstance().CheckEvent(Keybinding::MOVE_FORWARD))
	{
		m_vel.x += cos(m_transform.m_direction) * m_acceleration;
		m_vel.y += sin(m_transform.m_direction) * m_acceleration;

		m_totalVelocity = sqrt((m_vel.x * m_vel.x) + (m_vel.y * m_vel.y));
		moved = true;
	}

	if (Input::GetInstance().CheckEvent(Keybinding::MOVE_BACKWARD))
	{
		m_vel.x += -cos(m_transform.m_direction) * m_acceleration;
		m_vel.y += -sin(m_transform.m_direction) * m_acceleration;

		m_totalVelocity = sqrt((m_vel.x * m_vel.x) + (m_vel.y * m_vel.y));
		moved = true;
	}

	if (Input::GetInstance().CheckEvent(Keybinding::STRAFE_LEFT))
	{
		m_vel.x += cos(m_transform.m_direction - 90 * degToRad) * m_acceleration;
		m_vel.y += sin(m_transform.m_direction - 90 * degToRad) * m_acceleration;

		m_totalVelocity = sqrt((m_vel.x * m_vel.x) + (m_vel.y * m_vel.y));
		moved = true;
	}

	if (Input::GetInstance().CheckEvent(Keybinding::STRAFE_RIGHT))
	{
		m_vel.x += cos(m_transform.m_direction + 90 * degToRad) * m_acceleration;
		m_vel.y += sin(m_transform.m_direction + 90 * degToRad) * m_acceleration;

		m_totalVelocity = sqrt((m_vel.x * m_vel.x) + (m_vel.y * m_vel.y));
		moved = true;
	}

	// If no user input deccelerate ship
	if (!moved)
		Deccelerate();

	// Limits total velocity to predefined max
	else
	{
		if (m_totalVelocity > m_maxVelocity)
		{
			m_vel.x *= m_maxVelocity / m_totalVelocity;
			m_vel.y *= m_maxVelocity / m_totalVelocity;
		}
	}

	if (Input::GetInstance().CheckEvent(Keybinding::TURN_LEFT))
		m_transform.m_direction -= 0.05f;

	if (Input::GetInstance().CheckEvent(Keybinding::TURN_RIGHT))
		m_transform.m_direction += 0.05f;

	if (Input::GetInstance().CheckEvent(Keybinding::FIRE))
	{
		m_guns.at(m_activeGun)->SetIsFiring(true);
		m_firing = true;
	}

	if (Input::GetInstance().GetKeyUp(ALLEGRO_KEY_SPACE))
	{
		m_guns.at(m_activeGun)->SetIsFiring(false);
		m_firing = false;
	}
}

// Deccelerates player if no movement input is detected this frame
void Player::Deccelerate()
{
	if (m_totalVelocity > 1.10 || m_totalVelocity < -1.10)
	{
		m_vel.x *= 0.975;
		m_vel.y *= 0.975;

		m_totalVelocity = sqrt((m_vel.x * m_vel.x) + (m_vel.y * m_vel.y));
	}
}

// Checks for and processes collisions recorded this frame
void Player::CheckCollisions()
{
	std::vector<Collision> collisions = m_collider->GetCollisions();

	for (Collision col : collisions)
	{
		switch (col.s_collTypeHit)
		{
			case Enums::OBJECTS::ASTEROID:
			{
				if (!m_tempInv)
				{
					m_score += col.s_dmg;
					ReduceLife();
				}
			}
			break;
			case Enums::OBJECTS::UFO:
			{
				if (!m_tempInv)
				{
					m_score += 200;
					ReduceLife();
				}
			}
			break;
			case Enums::OBJECTS::UFO_BULLET:
			{
				if (!m_tempInv)
				{
					ReduceLife();
				}
			}
				break;
			case Enums::OBJECTS::DOUBLE_LASER:
			{
				ChangeWeapon(1);
			}
			break;
			case Enums::OBJECTS::BIG_LASER:
			{
				ChangeWeapon(2);
			}
			break;
			case Enums::OBJECTS::MULTI_LASER:
			{
				ChangeWeapon(3);
			}
			break;
			case Enums::OBJECTS::EXTRA_LIFE:
			{
				m_lives++;
			}
			break;
			default: {}
		}
	}

	m_collider->ResetCollisions();
}

// Reduces player life and procs temporary invincibility
void Player::ReduceLife()
{
	m_explosion.Spawn(m_transform.m_pos, 1.0);

	m_lives -= 1;
	m_transform.m_pos = Vec2(500, 500);
	m_vel.x = m_vel.y = m_totalVelocity = 0.0f;
	m_transform.m_direction = 270 * degToRad;
	m_tempInv = true;
}

// Changes to the specified weapon
void Player::ChangeWeapon(int _weap)
{
	m_guns.at(m_activeGun)->SetIsFiring(false);

	m_activeGun = _weap;
	m_weapPUP = true;

	if (m_firing)
		m_guns.at(m_activeGun)->SetIsFiring(true);
}

Vec2 Player::GetPos()
{
	return m_transform.m_pos;
}

int Player::GetScore()
{
	return m_score;
}

void Player::AddScore(int _score)
{
	m_score += _score;
}

void Player::Shutdown()
{
	for (Weapon *weap : m_guns)
	{
		weap->Shutdown();
		delete weap;
	}

	m_guns.clear();
	m_collider.reset();
}

Player::~Player() {}