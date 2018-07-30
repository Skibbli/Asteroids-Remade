#include "stdafx.h"

#include "CircleCollider.h"
#include "RectangleCollider.h"


CircleCollider::CircleCollider(Enums::OBJECTS _obj, Vec2 _pos, int _dmg, float _radius)
{
	m_objType = _obj;
	m_colType = Enums::COLTYPE::CIRCLE;

	m_pos = _pos;
	m_dmg = _dmg;
	m_radius = _radius;
	m_isLive = false;
}

float CircleCollider::GetRadius()
{
	return m_radius;
}

// Checks for collision with the collision passed in to the function
void CircleCollider::CheckCollision(weak<Collider> _col)
{
	if (_col.lock()->GetColliderType() == Enums::COLTYPE::CIRCLE)
	{
		shared<CircleCollider> col = std::static_pointer_cast<CircleCollider>(_col.lock());

		Vec2 distance = m_pos - col->m_pos;
		float length = glm::length(distance);

		if (length <= m_radius + col->m_radius)
		{
			AddCollision(col->m_objType, col->m_dmg);
			_col.lock()->AddCollision(m_objType, m_dmg);
		}
	}

	else if (_col.lock()->GetColliderType() == Enums::COLTYPE::RECTANGLE)
	{
		shared<RectangleCollider> col = std::static_pointer_cast<RectangleCollider>(_col.lock());

		float radius = sqrt(pow((col->GetWidth() / 2), 2) + pow((col->GetHeight() / 2), 2));

		Vec2 rectPos = col->GetPos();

		Vec2 distance = m_pos - col->GetPos();
		float length = glm::length(distance);

		if (length <= m_radius + radius)
		{
			Vec2 rotPoint = RotateAroundPoint(rectPos, m_pos, -col->GetDirection());

			if (((rotPoint.x + m_radius > rectPos.x - col->GetWidth() / 2 && rotPoint.x + m_radius < rectPos.x + col->GetWidth() / 2)
				|| (rotPoint.x - m_radius > rectPos.x - col->GetWidth() / 2 && rotPoint.x - m_radius < rectPos.x + col->GetWidth() / 2))
				&& ((rotPoint.y + m_radius > rectPos.y - col->GetHeight() / 2 && rotPoint.y + m_radius < rectPos.y + col->GetHeight() / 2)
				|| (rotPoint.y - m_radius > rectPos.y - col->GetHeight() / 2 && rotPoint.y - m_radius < rectPos.y + col->GetHeight() / 2)))
			{
				AddCollision(col->GetObjectType(), col->GetDamage());
				_col.lock()->AddCollision(m_objType, m_dmg);
			}
		}
	}
}

void CircleCollider::Update(Vec2 _pos)
{
	m_pos = _pos;
}

void CircleCollider::DrawCollider()
{
	al_draw_circle(m_pos.x, m_pos.y, m_radius, al_map_rgb(255, 0, 255), 3);
}

CircleCollider::~CircleCollider()
{

}