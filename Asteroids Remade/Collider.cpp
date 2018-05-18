#include "stdafx.h"

#include "Collider.h"


Collider::Collider()
{

}

Collider::Collider(OBJECTS _obj, Vec2 _pos, float _radius)
{
	
}

void Collider::SetIsLive(bool _isLive)
{
	m_isLive = _isLive;
}

bool Collider::GetIsLive()
{
	return m_isLive;
}

void Collider::CheckCollision(weak<Collider> _col)
{
	Vec2 distance = m_pos - _col.lock().get()->m_pos;
	float length = glm::length(distance);

	if (length <= m_radius + _col.lock().get()->m_radius)
	{
		m_collDets.push_back(Collision(_col, true));
		_col.lock().get()->AddCollision(shared_from_this());
	}
}

OBJECTS Collider::GetObjType()
{
	return m_objType;
}

std::vector<Collisions> Collider::GetCollision()
{
	return &m_collDets;
}

void Collider::DrawCollider()
{
	al_draw_circle(m_pos.x, m_pos.y, m_radius, al_map_rgb(255, 0, 255), 3);
}

void Collider::AddCollision(weak<Collider> _col)
{
	m_collDets.push_back(Collision(_col, true));
}

void Collider::ResetCollisions()
{
	m_collDets.clear();
}

Collider::~Collider()
{

}