#include "stdafx.h"

#include "Transform.h"


class Collider
{
	public:
		Collider();
		~Collider();

	protected:
		weak<Transform> m_transform;

	private:
};

class BoxCollider : public Collider
{
	public:

	private:
		float m_width, m_height;
};

class SphereCollider : public Collider
{
	public:

	private:
		float m_radius;
};