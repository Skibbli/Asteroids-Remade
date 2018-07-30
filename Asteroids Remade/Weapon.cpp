#include "stdafx.h"

#include "Weapon.h"
#include "Time.h"
#include "Resources.h"
#include "Maths.h"


Weapon::Weapon()
{
	m_fireCounter = 0;
	m_fireCD = 15;
	m_isFiring = false;
	m_bulletsLive = false;
}

void Weapon::Start() {}

void Weapon::Update(Vec2 _pos, float _dir, float _bonusVel) {}

void Weapon::Render()
{
	if (m_bulletsLive)
	{
		for (int i = 0; i < m_numBullets; i++)
		{
			if (m_bullets[i].GetIsLive())
			{
				m_bullets[i].Render();
			}
		}
	}	
}

void Weapon::SetIsFiring(bool _isFiring)
{
	m_isFiring = _isFiring;
}

void Weapon::Fire() {}

void Weapon::CheckCollision()
{
	for (int i = 0; i < m_numBullets; i++)
	{
		if (m_bullets[i].GetIsLive())
		{
			m_bullets[i].CheckCollisions();
		}
	}
}

void Weapon::Shutdown()
{
	for (int i = 0; i < m_numBullets; i++)
	{
		m_bullets[i].Shutdown();
	}

	delete[] m_bullets;
}

Weapon::~Weapon()
{

}

/// Other guns
RegGun::RegGun()
{
	m_fireRate = 1;
	m_bulletDamage = 10;
	m_bulletSpeed = 325;

	m_numBullets = 40;
	m_bullets = new Bullet[m_numBullets];

	m_shootEffect = Resources::GetInstance().LoadSFXSample("Laser.ogg");
}

void RegGun::Start()
{
	for (int i = 0; i < m_numBullets; i++)
	{
		m_bullets[i].Start(Enums::OBJECTS::PLAYER_BULLET, "Bullet.png", m_bulletDamage, m_bulletSpeed);
	}
}

// Updates existing bullets and the spawn details for new bullets
void RegGun::Update(Vec2 _pos, float _dir, float _bonusVel)
{
	m_spawnPos = _pos;
	m_spawnDir = _dir;
	m_bonusVel = _bonusVel;

	Fire();

	bool bulletsLive = false;
	
	if (m_bulletsLive)
	{
		for (int i = 0; i < m_numBullets; i++)
		{
			if (m_bullets[i].GetIsLive())
			{
				m_bullets[i].Update();
				bulletsLive = true;
			}
		}
	}

	m_bulletsLive = bulletsLive;

	CheckCollision();
}

// Checks if fire CD is up and if it is spawns a bullet
void RegGun::Fire()
{
	if (m_fireCD - m_fireCounter < 0 && m_isFiring)
	{
		for (int i = 0; i < m_numBullets; i++)
		{
			if (!m_bullets[i].GetIsLive())
			{
				m_spawnPos.x += cos(m_spawnDir) * 20;
				m_spawnPos.y += sin(m_spawnDir) * 20;

				m_bullets[i].Spawn(m_spawnPos, m_spawnDir, m_bulletSpeed + m_bonusVel * 20, false);
				m_fireCounter = 0;
				m_shootEffect.lock()->PlaySample();
				m_bulletsLive = true;

				break;
			}
		}
	}

	else
	{
		m_fireCounter += m_fireRate;
	}
}

RegGun::~RegGun()
{

}



DoubleGun::DoubleGun()
{
	m_fireRate = 4.0;
	m_bulletDamage = 10;
	m_bulletSpeed = 500;
	m_leftGun = true;

	m_numBullets = 80;
	m_bullets = new Bullet[m_numBullets];

	m_shootEffect = Resources::GetInstance().LoadSFXSample("Laser.ogg");
}

void DoubleGun::Start()
{
	for (int i = 0; i < m_numBullets; i++)
	{
		m_bullets[i].Start(Enums::OBJECTS::PLAYER_BULLET, "DoubleBullet.png", m_bulletDamage, m_bulletSpeed);
	}
}

// Updates existing bullets and the spawn details for new bullets
void DoubleGun::Update(Vec2 _pos, float _dir, float _bonusVel)
{
	m_spawnPos = _pos;
	m_spawnDir = _dir;
	m_bonusVel = _bonusVel;

	Fire();

	bool bulletsLive = false;

	if (m_bulletsLive)
	{
		for (int i = 0; i < m_numBullets; i++)
		{
			if (m_bullets[i].GetIsLive())
			{
				m_bullets[i].Update();
				bulletsLive = true;
			}
		}
	}

	m_bulletsLive = bulletsLive;

	CheckCollision();
}

// Checks if fire CD is up and if it is spawns a bullet
void DoubleGun::Fire()
{
	if (m_fireCD - m_fireCounter < 0 && m_isFiring)
	{
		for (int i = 0; i < m_numBullets; i++)
		{
			if (!m_bullets[i].GetIsLive())
			{
				if (m_leftGun)
				{
					m_spawnPos.x -= sin(m_spawnDir) * 20;
					m_spawnPos.y += cos(m_spawnDir) * 20;

					m_leftGun = false;
				}

				else
				{
					m_spawnPos.x += sin(m_spawnDir) * 20;
					m_spawnPos.y -= cos(m_spawnDir) * 20;

					m_leftGun = true;
				}


				m_bullets[i].Spawn(m_spawnPos, m_spawnDir, m_bulletSpeed + m_bonusVel * 20, false);
				m_fireCounter = 0;
				m_shootEffect.lock()->PlaySample();
				m_bulletsLive = true;

				break;
			}
		}
	}

	else
	{
		m_fireCounter += m_fireRate;
	}
}

DoubleGun::~DoubleGun()
{

}



BigGun::BigGun()
{
	m_fireRate = 0.3;
	m_bulletDamage = 60;
	m_bulletSpeed = 250;

	m_numBullets = 12;
	m_bullets = new Bullet[m_numBullets];

	m_shootEffect = Resources::GetInstance().LoadSFXSample("BigLaser.ogg");
}

void BigGun::Start()
{
	for (int i = 0; i < m_numBullets; i++)
	{
		m_bullets[i].Start(Enums::OBJECTS::PLAYER_BULLET, "BigBullet.png", m_bulletDamage, m_bulletSpeed);
	}
}

// Updates existing bullets and the spawn details for new bullets
void BigGun::Update(Vec2 _pos, float _dir, float _bonusVel)
{
	m_spawnPos = _pos;
	m_spawnDir = _dir;
	m_bonusVel = _bonusVel;

	Fire();

	bool bulletsLive = false;

	if (m_bulletsLive)
	{
		for (int i = 0; i < m_numBullets; i++)
		{
			if (m_bullets[i].GetIsLive())
			{
				m_bullets[i].Update();
				bulletsLive = true;
			}
		}
	}

	m_bulletsLive = bulletsLive;

	CheckCollision();
}

// Checks if fire CD is up and if it is spawns a bullet
void BigGun::Fire()
{
	if (m_fireCD - m_fireCounter < 0 && m_isFiring)
	{
		for (int i = 0; i < m_numBullets; i++)
		{
			if (!m_bullets[i].GetIsLive())
			{
				m_spawnPos.x += cos(m_spawnDir) * 20;
				m_spawnPos.y += sin(m_spawnDir) * 20;

				m_bullets[i].Spawn(m_spawnPos, m_spawnDir, m_bulletSpeed + m_bonusVel * 20, true);
				m_fireCounter = 0;
				m_shootEffect.lock()->PlaySample();
				m_bulletsLive = true;

				break;
			}
		}
	}

	else
	{
		m_fireCounter += m_fireRate;
	}
}

BigGun::~BigGun()
{

}



MultiGun::MultiGun()
{
	m_fireRate = 5.55;
	m_bulletDamage = 10;
	m_bulletSpeed = 500;
	m_spawnDir = 0.0f;

	m_numBullets = 80;
	m_bullets = new Bullet[m_numBullets];

	m_shootEffect = Resources::GetInstance().LoadSFXSample("Laser.ogg");
}

void MultiGun::Start()
{
	for (int i = 0; i < m_numBullets; i++)
	{
		m_bullets[i].Start(Enums::OBJECTS::PLAYER_BULLET, "Bullet.png", m_bulletDamage, m_bulletSpeed);
	}
}

// Updates existing bullets and the spawn details for new bullets
void MultiGun::Update(Vec2 _pos, float _dir, float _bonusVel)
{
	m_spawnPos = _pos;
	
	m_bonusVel = _bonusVel;

	Fire();

	bool bulletsLive = false;

	if (m_bulletsLive)
	{
		for (int i = 0; i < m_numBullets; i++)
		{
			if (m_bullets[i].GetIsLive())
			{
				m_bullets[i].Update();
				bulletsLive = true;
			}
		}
	}

	m_bulletsLive = bulletsLive;

	CheckCollision();
}

// Checks if fire CD is up and if it is spawns a bullet
void MultiGun::Fire()
{
	if (m_fireCD - m_fireCounter < 0 && m_isFiring)
	{
		int f = 0;

		for (int i = 0; i < m_numBullets; i++)
		{
			if (!m_bullets[i].GetIsLive())
			{
				m_bullets[i].Spawn(m_spawnPos, GenRandNo(0,360) * degToRad /*m_spawnDir*/, m_bulletSpeed + m_bonusVel * 20, false);
				m_fireCounter = 0;
				m_shootEffect.lock()->PlaySample();
				m_bulletsLive = true;

				m_spawnDir += 0.7855;

				if (m_spawnDir > 2 * ALLEGRO_PI)
					m_spawnDir = 0.0f;

				break;
			}
		}
	}

	else
	{
		m_fireCounter += m_fireRate;
	}
}

MultiGun::~MultiGun()
{

}