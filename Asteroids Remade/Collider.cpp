#include "stdafx.h"

#include "Collider.h"


Collider::Collider() {}

bool Collider::GetIsLive()
{
	return m_isLive;
}

void Collider::SetIsLive(bool _isLive)
{
	m_isLive = _isLive;
}

float Collider::GetDamage()
{
	return m_dmg;
}

void Collider::SetDamage(int _dmg)
{
	m_dmg = _dmg;
}

Vec2 Collider::GetPos()
{
	return m_pos;
}

Enums::OBJECTS Collider::GetObjectType()
{
	return m_objType;
}

Enums::COLTYPE Collider::GetColliderType()
{
	return m_colType;
}

void Collider::SetColliderType(Enums::OBJECTS _type)
{
	m_objType = _type;
}

// Adds collision details for a collision that has occured with this collider
void Collider::AddCollision(Enums::OBJECTS _obj, int _dmg)
{
	m_collDets.push_back(Collision(_obj, _dmg));
}

void Collider::ResetCollisions()
{
	m_collDets.clear();
}

// Gets objects this collider has collided with this frame
std::vector<Collision>& Collider::GetCollisions()
{
	return m_collDets;
}

void Collider::CheckCollision(weak<Collider> _col) {}

void Collider::Update() {}

void Collider::DrawCollider() {}

Collider::~Collider() {}