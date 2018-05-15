#include "stdafx.h"

#include "BaseObj.h"

BaseObj::BaseObj()
{

}

void BaseObj::Start()
{

}

bool BaseObj::Update()
{
	return true;
}

void BaseObj::LimitCheck(float _width, float _height)
{
	if (m_pos.y < -50)
		m_pos.y = _height + 50;
	if (m_pos.y > _height + 50)
		m_pos.y = -50;
	if (m_pos.x > _width + 50)
		m_pos.x = -50;
	if (m_pos.x < -50)
		m_pos.x = _width + 50;

	if (m_direction > ALLEGRO_PI * 2)
		m_direction = 0;

	if (m_direction < 0)
		m_direction = ALLEGRO_PI * 2;
}

void BaseObj::Render()
{

}

Vec2 BaseObj::GetPos()
{
	return m_pos;
}

void BaseObj::SetPos(Vec2 _pos)
{
	m_pos = _pos;
}

BaseObj::~BaseObj()
{

}