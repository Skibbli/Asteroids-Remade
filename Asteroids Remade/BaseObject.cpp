#include "stdafx.h"

#include "BaseObject.h"
#include "Core.h"


BaseObject::BaseObject()
{
	m_isLive = false;
	Core::GetInstance().AddGameObject(this);
	m_defWinWidth = 1000;
	m_defWinHeight = 1000;

	m_displaySize = Core::GetInstance().GetDisplaySize();
}

void BaseObject::Start() {}

bool BaseObject::Update() { return true; }

void BaseObject::Render() {}

void BaseObject::Shutdown() {}

void BaseObject::SetIsLive(bool _isLive)
{
	m_isLive = _isLive;
}

bool BaseObject::GetIsLive()
{
	return m_isLive;
}

// Checks if object has left the window and returns it on the opposite side
void BaseObject::LimitCheck()
{
	if (m_transform.m_pos.y < 0 - m_bitmap.s_frameHeight / 2)
		m_transform.m_pos.y = m_defWinHeight + m_bitmap.s_frameHeight / 2;
	if (m_transform.m_pos.y > m_defWinHeight + m_bitmap.s_frameHeight / 2)
		m_transform.m_pos.y = 0 - m_bitmap.s_frameHeight / 2;
	if (m_transform.m_pos.x > m_defWinWidth + m_bitmap.s_frameWidth / 2)
		m_transform.m_pos.x = 0 - m_bitmap.s_frameWidth / 2;
	if (m_transform.m_pos.x < 0 - m_bitmap.s_frameWidth / 2)
		m_transform.m_pos.x = m_defWinWidth + m_bitmap.s_frameWidth / 2;

	if (m_transform.m_direction > ALLEGRO_PI * 2)
		m_transform.m_direction = 0;

	if (m_transform.m_direction < 0)
		m_transform.m_direction = ALLEGRO_PI * 2;
}

void BaseObject::UpdateDisplaySize(DisplayInfo &_display)
{
	m_displaySize = _display;
}

BaseObject::~BaseObject()
{
	Core::GetInstance().RemoveGameObject(this);
}