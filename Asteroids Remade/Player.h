#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"

#include "BaseObject.h"
#include "Weapon.h"
#include "Explosion.h"


class CircleCollider;

class Player : public BaseObject
{
	public:
		Player();
		~Player();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

		void Input();
		// Slows the ship if no movement input is detected
		void Deccelerate();
		void CheckCollisions();
		void ReduceLife();

		void ChangeWeapon(int _weap);

		Vec2 GetPos();
		int GetScore();
		void AddScore(int _score);

	private:
		int m_score;
		int m_lives;

		// Temporary invincibility counters
		bool m_tempInv;
		float m_tempInvTimer;
		float m_tempInvCD;

		// Weapon powerup timers
		bool m_weapPUP;
		bool m_firing;
		float m_weaponCD;
		float m_weaponTimer;

		// Velocity variables
		Vec2 m_vel;
		float m_totalVelocity;
		float m_maxVelocity;
		float m_acceleration;

		float m_boundRadius;

		std::vector<Weapon*> m_guns;
		int m_activeGun;

		weak<ALLEGRO_FONT> m_font;

		Explosion m_explosion;

		shared<CircleCollider> m_collider;
};

#endif