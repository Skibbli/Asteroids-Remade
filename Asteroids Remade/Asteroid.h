#ifndef ASTEROID_H
#define ASTEROID_H

#include "stdafx.h"

#include "BaseObj.h"
#include "Collider.h"

class Asteroid : public BaseObj
{
	public:
		Asteroid();
		~Asteroid();

		virtual void Start();
		bool Update();
		virtual void Render();

		virtual void Spawn();
		bool IsLive() { return m_isLive; };
		bool CheckCollision(Vec2 _pos, float _radius);
		void LimitCheck();
		virtual void TakeDmg(int _dmg);

		protected:
			int m_health, m_maxHealth, m_rotDir;
		
			float m_vel, m_radius, m_size, m_frameNo, m_frameCount, m_rotation;
			bool m_isLive;

			shared<Collider> m_collider;

		private:
			
};

#endif

class BigAsteroid : public Asteroid
{
	public:
		BigAsteroid();
		~BigAsteroid();

		void Start();
		bool Update();
		void Render();		

		void Spawn(Vec2 _pos);

	private:

};

class MedAsteroid : public Asteroid
{
	public:
		MedAsteroid();
		~MedAsteroid();

		void Start();
		bool Update();
		void Render();

		void Spawn(Vec2 _pos);

	private:

};

class SmallAsteroid : public Asteroid
{
	public:
		SmallAsteroid();
		~SmallAsteroid();

		void Start();
		bool Update();
		void Render();

		void Spawn(Vec2 _pos);

	private:

};