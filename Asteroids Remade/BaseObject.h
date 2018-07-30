#ifndef BASEOBJ_H
#define BASEOBJ_H

#include "stdafx.h"

#include "Transform.h"
#include "ResourceStructs.h"


// Base class for any object in the game
class BaseObject
{
	public:
		BaseObject();
		~BaseObject();

		virtual void Start();
		virtual bool Update();
		virtual void Render();
		virtual void Shutdown();

		bool GetIsLive();
		void SetIsLive(bool _isLive);

		// Keeps object inside the window
		void LimitCheck();
		void UpdateDisplaySize(DisplayInfo &_display);

	protected:
		bool m_isLive;
		int m_ID;

		float m_defWinWidth, m_defWinHeight;
		DisplayInfo m_displaySize;

		Transform m_transform;
		Bitmap m_bitmap;
};

#endif