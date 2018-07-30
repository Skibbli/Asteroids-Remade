#ifndef PHYSICS_H
#define PHYSICS_H

#include "stdafx.h"


class Collider;

class Physics
{
	public:
		Physics();
		~Physics();

		void Update();

		void AddCollider(weak<Collider> _col);
		void DrawColliders();
		void Shutdown();

		void Reset();

	private:
		std::vector<weak<Collider>> m_colliders;
};

#endif