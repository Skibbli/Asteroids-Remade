#ifndef SLIDER_H
#define SLIDER_H

#include "stdafx.h"

#include "BaseObject.h"
#include "ResourceStructs.h"

// Class for sliders in menus
class Slider : public BaseObject
{
	public:
		Slider(Vec2 _pos, float _width, float _currVal, std::string _text);
		~Slider();

		bool Update();
		void Render();

		float GetCurrentValue();

	private:
		float m_width;

		Vec2 m_buttonPos;
		float m_buttonWidth, m_buttonHeight;
		float m_val;

		bool m_clicked;

		weak<ALLEGRO_FONT> m_font;
		std::string m_text;
};

#endif