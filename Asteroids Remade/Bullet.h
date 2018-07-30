#ifndef BULLET_H
#define BULLET_H

#include "stdafx.h"

#include "BaseObject.h"


class CircleCollider;

class Bullet : public BaseObject
{
	public:
		Bullet();
		~Bullet();

		void Start(Enums::OBJECTS _type, std::string _imageName, int _dmg, float _vel);
		bool Update();
		void Render();
		void Shutdown();

		void Spawn(Vec2 _pos, float _dir, float _vel, bool _inv);
		void Despawn();
		void CheckCollisions();

	private:
		bool m_inv;

		int m_dmg;

		float m_distTravelled, m_distLimit, m_vel, m_radius;

		Enums::OBJECTS m_bulletType;

		shared<CircleCollider> m_collider;
		weak<SFXSample> m_collisionFX;
};

#endif