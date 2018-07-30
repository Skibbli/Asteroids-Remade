#ifndef POWERUP_H
#define POWERUP_H

#include "stdafx.h"

#include "BaseObject.h"
#include "RectangleCollider.h"


class Powerup : public BaseObject
{
	public:
		Powerup();
		~Powerup();

		void Start();
		bool Update();
		void Render();
		void Shutdown();

		// Spawns the type of powerup
		void Spawn(int _type);
		void CheckCollisions();

	private:
		int m_type;
		float m_vel;
		float m_distTravelled;
		float m_distLimit;

		weak<SFXSample> m_pupFX;

		shared<RectangleCollider> m_collider;
};

#endif