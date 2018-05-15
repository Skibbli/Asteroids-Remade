#ifndef BULLET_H
#define BULLET_H

#include "stdafx.h"

#include "BaseObj.h"

class Bullet : public BaseObj
{
	public:
		Bullet();
		~Bullet();

		void Start();
		bool Update();
		void Render();

		void Spawn(Vec2 _pos, float _dir, int _dmg);

		bool IsLive();
		void SetLive(bool _isLive);
		int GetDamage();

	private:
		int m_ID;
		int m_dmg;

		float m_vel;

		bool m_isLive;

		float m_distTravelled, m_distLimit;
};

#endif