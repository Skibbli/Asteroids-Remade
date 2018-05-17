#ifndef ASTEROID_H
#define ASTEROID_H

#include "stdafx.h"

#include "BaseObj.h"

class Asteroid : public BaseObj
{
	public:
		Asteroid();
		~Asteroid();

		virtual void Start();
		virtual bool Update();
		virtual void Render();

		void Spawn(Vec2 _pos);
		bool IsLive() { return m_isLive; };
		bool DealDamage(int _dmg);
		bool CheckCollision(Vec2 _pos, float _radius);
		void LimitCheck();

		protected:
			int m_health, m_maxHealth;
		
			float m_vel, m_radius, m_size, m_frameNo, m_frameCount;
			bool m_isLive;

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

	private:

};