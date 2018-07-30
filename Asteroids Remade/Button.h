#include "stdafx.h"

#include "BaseObject.h"


struct Colour
{
	Colour() {};
	Colour(int _r, int _b, int _g, int _a) { r = _r; b = _b; g = _g; a = _a; }

	int r, g, b, a;
};

// Button objects for menu/UI
class Button : public BaseObject
{
	public:
		Button();
		~Button();

	virtual void Start();
	virtual bool Update();
	virtual void Render();

	void SetText(std::string _fontName, int _fontSize, std::string _text, Colour _col);

	protected:
		bool m_collision;
		bool m_clicked;
		bool m_hasBitmap;

		std::string m_text;

		Colour m_buttonCol;
		Colour m_textCol;

		weak<ALLEGRO_FONT> m_font;
};

class CircleButton : public Button
{
	public:
		CircleButton();
		// Button sizes are % of window size
		CircleButton(std::string _text, Colour _textCol, std::string _font, int _fontSize, Vec2 _pos, float _radius, Colour _col);
		// Button sizes are % of window size
		CircleButton(std::string _bitmap, Vec2 _pos, float _radius);
		~CircleButton();

		void Start();
		bool Update();
		void Render();

	private:
		float m_radius;
};

class RectButton : public Button
{
	public:
		RectButton();
		// Button sizes are % of window size
		RectButton(std::string _text, Colour _textCol, std::string _font, int _fontSize, Vec2 _pos, float _width, float _height, Colour _col);
		// Button sizes are % of window size
		RectButton(std::string _bitmap, Vec2 _pos, float _width, float _height);
		~RectButton();

		void Start();
		bool Update();
		void Render();

	private:
		float m_width, m_height;
};