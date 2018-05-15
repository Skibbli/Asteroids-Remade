#include "stdafx.h"


class Transform
{
	public:
		Transform();
		~Transform();

		Vec2 GetPos();
		float GetDirection();

		void IncreaseXPos(float _val);
		void DecreaseXPos(float _val);
		void IncreaseYPos(float _val);
		void DecreaseYPos(float _val);

		void SetXPos(float _xPos);
		void SetYPos(float _yPos);

	private:
		Vec2 m_pos;
		float m_direction;

};