#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"

#include "BaseObj.h"
#include "Bullet.h"

class Player : public BaseObj
{
	public:
		Player();
		~Player();

		virtual void Start(Bullet *_bullets);
		virtual bool Update();
		virtual void Render();

		void Input();
		bool Fire();
		void Deccelerate();
		void GetBulletDets(Bullet &_bullet);

		Vec2 GetPos() { return m_pos; };
		float GetXVel() { return m_vel.x; };
		float GetYVel() { return m_vel.y; };
		float GetDirection() { return m_direction; };

	private:
		int m_ID;
		float m_boundRadius;
		int m_health, m_score, m_lives;

		bool m_isFiring;
		int m_fireRate;
		int m_fireCD;

		int m_dmg;
		int m_bulletSpeed;

		Vec2 m_vel;
		float m_totalVelocity;
		float m_maxVelocity;
		float m_acceleration;

		Bullet *m_bullets;
};

#endif