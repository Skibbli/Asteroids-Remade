#include "stdafx.h"

#include "RectangleCollider.h"
#include "CircleCollider.h"


RectangleCollider::RectangleCollider(Enums::OBJECTS _obj, Vec2 _pos, int _dmg, float _width, float _height)
{
	m_objType = _obj;
	m_colType = Enums::COLTYPE::RECTANGLE;

	m_pos = _pos;
	m_dmg = _dmg;
	m_width = _width;
	m_height = _height;
	m_isLive = false;
}

float RectangleCollider::GetWidth()
{
	return m_width;
}

float RectangleCollider::GetHeight()
{
	return m_height;
}

float RectangleCollider::GetDirection()
{
	return m_direction;
}

// Checks for collision with the collision passed in to the function
void RectangleCollider::CheckCollision(weak<Collider> _col)
{
	if (_col.lock()->GetColliderType() == Enums::COLTYPE::CIRCLE)
	{
		shared<CircleCollider> col = std::static_pointer_cast<CircleCollider>(_col.lock());

		float radius = sqrt(pow((m_width / 2), 2) + pow((m_height / 2), 2));

		float circleRadius = col->GetRadius();

		Vec2 distance = m_pos - col->GetPos();
		float length = glm::length(distance);

		if (length <= col->GetRadius() + radius)
		{
			Vec2 rotPoint = RotateAroundPoint(m_pos, col->GetPos(), -m_direction);

			if (((rotPoint.x + circleRadius > m_pos.x - m_width / 2 && rotPoint.x + circleRadius < m_pos.x + m_width / 2)
				|| (rotPoint.x - circleRadius > m_pos.x - m_width / 2 && rotPoint.x - circleRadius < m_pos.x + m_width / 2))
				&& ((rotPoint.y + circleRadius > m_pos.y - m_height / 2 && rotPoint.y + circleRadius < m_pos.y + m_height / 2)
				|| (rotPoint.y - circleRadius > m_pos.y - m_height / 2 && rotPoint.y - circleRadius < m_pos.y + m_height / 2)))
			{
				AddCollision(col->GetObjectType(), col->GetDamage());
				_col.lock()->AddCollision(m_objType, m_dmg);
			}
		}
	}

	else if (_col.lock()->GetColliderType() == Enums::COLTYPE::RECTANGLE)
	{

	}
}

// Updates position and direction of collider each frame
void RectangleCollider::Update(Vec2 _pos, float _dir)
{
	m_pos = _pos;
	m_direction = _dir;
}

void RectangleCollider::DrawCollider()
{
	Vec2 point1 = RotateAroundPoint(m_pos, Vec2(m_pos.x - m_width / 2, m_pos.y - m_width / 2), m_direction);
	Vec2 point2 = RotateAroundPoint(m_pos, Vec2(m_pos.x - m_width / 2, m_pos.y + m_width / 2), m_direction);
	Vec2 point3 = RotateAroundPoint(m_pos, Vec2(m_pos.x + m_width / 2, m_pos.y - m_width / 2), m_direction);
	Vec2 point4 = RotateAroundPoint(m_pos, Vec2(m_pos.x + m_width / 2, m_pos.y + m_width / 2), m_direction);

	al_draw_triangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, al_map_rgb(255, 0, 255), 3);
	al_draw_triangle(point2.x, point2.y, point3.x, point3.y, point4.x, point4.y, al_map_rgb(255, 0, 255), 3);
}

RectangleCollider::~RectangleCollider()
{

}