#include "stdafx.h"

class Button
{
	public:
		Button();
		~Button();

	virtual void Start();
	virtual bool Update();
	virtual void Render();

	protected:
		bool m_collision;
		bool m_clicked;
		bool m_isLive;
		Vec2 m_pos;

		weak<ALLEGRO_BITMAP> m_bitmap;
};

class CircleButton : public Button
{
	public:
		CircleButton();
		~CircleButton();

		void Start(Vec2 _pos, float _radius);
		bool Update();
		void Render();

	private:
		Vec2 m_pos;

		float m_radius;
};

class RectButton : public Button
{
	public:
		RectButton();
		~RectButton();

		void Start(Vec2 _pos, float _width, float _height);
		bool Update();
		void Render();

	private:
		Vec2 m_pos;

		float m_width, m_height;
};