#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include "stdafx.h"

#include "Collider.h"


class CircleCollider : public Collider
{
	public:
		CircleCollider(Enums::OBJECTS _obj, Vec2 _pos, int _dmg, float _radius);
		~CircleCollider();

		float GetRadius();

		void CheckCollision(weak<Collider> _col);
		void Update(Vec2 _pos);
		void DrawCollider();

	private:
		float m_radius;
};

#endif