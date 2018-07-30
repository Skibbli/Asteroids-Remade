#ifndef UFO_H
#define UFO_H

#include "stdafx.h"

#include "BaseObject.h"

class CircleCollider;
class Bullet;
class Player;


class UFO : public BaseObject
{
	public:
		UFO();
		~UFO();

		void Start(Player *_player);
		bool Update();
		void Render();
		void Shutdown();

		Vec2 GetPos();

		void Spawn();
		void Fire();
		void CheckCollisions();

	private:
		float m_dirChangeDist;
		float m_distTravelled;
		float m_distLimit;

		int m_health;

		float m_vel;

		bool m_bulletsLive;
		bool m_diedThisFrame;

		// Bullet variables and fire rate counters
		int m_fireRate;
		int m_fireCD;
		int m_fireCounter;
		int m_bulletDamage;
		float m_bulletSpeed;

		int m_numBullets;

		Bullet *m_bullets;
		Player *m_player;

		shared<CircleCollider> m_collider;
};

#endif