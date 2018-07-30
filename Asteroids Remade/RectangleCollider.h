#ifndef RECTANGLE_COLLIDER_H
#define RECTANGLE_COLLIDER_H

#include "stdafx.h"

#include "Collider.h"


class RectangleCollider : public Collider
{
	public:
		RectangleCollider(Enums::OBJECTS _obj, Vec2 _pos, int _dmg, float _width, float _height);
		~RectangleCollider();

		float GetWidth();
		float GetHeight();

		float GetDirection();

		void CheckCollision(weak<Collider> _col);
		void Update(Vec2 _pos, float _dir);
		void DrawCollider();

	private:
		float m_width;
		float m_height;
		float m_direction;
};

#endif