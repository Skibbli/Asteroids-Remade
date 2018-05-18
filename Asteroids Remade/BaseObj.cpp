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
	if (m_pos.y < 0 - m_frameWidth / 2)
		m_pos.y = _height + m_frameWidth / 2;
	if (m_pos.y > _height + m_frameWidth / 2)
		m_pos.y = 0 - m_frameWidth / 2;
	if (m_pos.x > _width + m_frameWidth / 2)
		m_pos.x = 0 - m_frameWidth / 2;
	if (m_pos.x < 0 - m_frameWidth / 2)
		m_pos.x = _width + m_frameWidth / 2;

	if (m_direction > ALLEGRO_PI * 2)
		m_direction = 0;

	if (m_direction < 0)
		m_direction = ALLEGRO_PI * 2;
}

void BaseObj::SetIsLive(bool _isLive)
{
	m_isLive = _isLive;
}

bool BaseObj::GetIsLive()
{
	return m_isLive;
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