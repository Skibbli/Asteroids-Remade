#ifndef WEAPON_H
#define WEAPON_H

#include "stdafx.h"

#include "Bullet.h"


// Base weapon class for derived weapons to inherit from - handles bullets
class Weapon
{
	public:
		Weapon();
		~Weapon();

		virtual void Start();
		virtual void Update(Vec2 _pos, float _dir, float _bonusVel);
		void Render();
		void Shutdown();

		void SetIsFiring(bool _isFiring);
		virtual void Fire();

		// Checks collisions for bullets
		void CheckCollision();

	protected:
		bool m_isFiring;
		bool m_powerUp;
		bool m_bulletsLive;

		// Counters used for controlling bullet spawn rate
		float m_fireRate;
		int m_fireCD;
		float m_fireCounter;
		// Max num of bullets
		int m_numBullets;

		float m_bulletSpeed;
		int m_bulletDamage;
		// Additional speed from ship momentum
		float m_bonusVel;

		float m_spawnDir;
		Vec2 m_spawnPos;

		Bullet *m_bullets;
		weak<SFXSample> m_shootEffect;
};

class RegGun : public Weapon
{
	public:
		RegGun();
		~RegGun();

		void Start();
		// Update the spawn details for spawning bullets
		void Update(Vec2 _pos, float _dir, float _bonusVel);

		void Fire();

	private:

};

class DoubleGun : public Weapon
{
	public:
		DoubleGun();
		~DoubleGun();

		void Start();
		// Update the spawn details for spawning bullets
		void Update(Vec2 _pos, float _dir, float _bonusVel);

		void Fire();

	private:
		bool m_leftGun;
};

class BigGun : public Weapon
{
	public:
		BigGun();
		~BigGun();

		void Start();
		// Update the spawn details for spawning bullets
		void Update(Vec2 _pos, float _dir, float _bonusVel);

		void Fire();

	private:

};

class MultiGun : public Weapon
{
	public:
		MultiGun();
		~MultiGun();

		void Start();
		// Update the spawn details for spawning bullets
		void Update(Vec2 _pos, float _dir, float _bonusVel);

		void Fire();

	private:

};

#endif