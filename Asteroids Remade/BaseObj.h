#ifndef BASEOBJ_H
#define BASEOBJ_H

#include "stdafx.h"


class BaseObj
{
	public:
		BaseObj();
		~BaseObj();

		virtual void Start();
		virtual bool Update();
		virtual void Render();

		void LimitCheck(float _width, float _height);
		Vec2 GetPos();
		void SetPos(Vec2 _pos);
		void SetIsLive(bool _isLive);
		bool GetIsLive();

		virtual void TakeDmg(int _dmg);

	protected:
		bool m_isLive;
		Vec2 m_pos;
		float m_direction;

		int m_frameWidth, m_frameHeight;

		weak<ALLEGRO_BITMAP> m_bitmap;
};

#endif