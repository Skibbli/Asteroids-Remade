#include "stdafx.h"

#include "Transform.h"

Transform::Transform()
{

}

Vec2 Transform::GetPos()
{
	return m_pos;
}

float Transform::GetDirection()
{
	return m_direction;
}

Transform::~Transform()
{

}