#ifndef ASTEROID_H
#define ASTEROID_H

#include "stdafx.h"

#include "BaseObject.h"
#include "Explosion.h"


class CircleCollider;

// Base class for various asteroid sizes
class Asteroid : public BaseObject
{
	public:
		Asteroid();
		~Asteroid();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

		virtual void Spawn();

		Vec2 GetPos();		
		void CheckCollisions();
		void LimitCheck();

	protected:
		int m_health, m_maxHealth, m_rotDir, m_sizeID, m_colDmg;
		
		float m_vel, m_radius, m_size, m_frameNo, m_frameCount, m_rotation;

		Explosion m_explosion;

		shared<CircleCollider> m_collider;
};

#endif

class BigAsteroid : public Asteroid
{
	public:
		BigAsteroid();
		~BigAsteroid();

		void Spawn(Vec2 _pos);

	private:

};

class MedAsteroid : public Asteroid
{
	public:
		MedAsteroid();
		~MedAsteroid();

		void Spawn(Vec2 _pos);

	private:

};

class SmallAsteroid : public Asteroid
{
	public:
		SmallAsteroid();
		~SmallAsteroid();

		void Spawn(Vec2 _pos);

	private:

};