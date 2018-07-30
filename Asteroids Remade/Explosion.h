#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "stdafx.h"

#include "ResourceStructs.h"


class Explosion
{
	public:
		Explosion();
		~Explosion();

		void Update();
		void Render();

		bool GetIsLive();

		void Spawn(Vec2 _pos, float _size);

	private:
		bool m_isLive;
		bool slower;

		// Frame counter for explosion animation
		int m_maxFrames;
		int m_currFrame;
		int m_animationColumns;

		float m_frameWidth;
		float m_frameHeight;

		float m_size;

		Vec2 m_pos;

		Bitmap m_bitmap;
		weak<SFXSample> m_explosionFX;
};

#endif