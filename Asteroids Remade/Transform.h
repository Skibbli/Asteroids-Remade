#include "stdafx.h"


// Class that handles position and direction of objects
class Transform
{
	public:
		Transform();
		~Transform();

		Vec2 m_pos;
		float m_direction;
};