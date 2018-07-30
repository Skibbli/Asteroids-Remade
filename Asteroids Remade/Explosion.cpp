#include "stdafx.h"

#include "Explosion.h"
#include "Resources.h"


Explosion::Explosion()
{
	m_isLive = false;

	m_bitmap = Resources::GetInstance().LoadBmp("Explosion.png");
	m_explosionFX = Resources::GetInstance().LoadSFXSample("Explosion.ogg");

	m_frameWidth = m_bitmap.s_frameWidth / 5;
	m_frameHeight = m_bitmap.s_frameHeight / 5;

	m_maxFrames = 24;
	m_animationColumns = 5;

	slower = false;
}

// Updates animation frame count
void Explosion::Update()
{
	if (slower)
	{
		m_currFrame++;
		slower = false;
	}

	else
		slower = true;


	if (m_currFrame > m_maxFrames)
	{
		m_isLive = false;
	}
}

void Explosion::Render()
{
	al_draw_tinted_scaled_rotated_bitmap_region(m_bitmap.GetBitmap(), (m_currFrame % m_animationColumns) * m_frameWidth, (m_currFrame / m_animationColumns) * m_frameHeight, m_frameWidth, m_frameHeight, al_map_rgba(255, 255, 255, 100), 0, 0, m_pos.x - m_frameWidth, m_pos.y - m_frameHeight, m_size, m_size, 0.0, NULL);
}

bool Explosion::GetIsLive()
{
	return m_isLive;
}

// Spawns explosion at given position with given size
void Explosion::Spawn(Vec2 _pos, float _size)
{
	m_pos = _pos;
	m_size = _size * 2;
	m_currFrame = 0;
	m_isLive = true;
	slower = false;

	m_explosionFX.lock()->PlaySample();
}

Explosion::~Explosion()
{

}