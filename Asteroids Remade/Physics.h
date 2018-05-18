#include "stdafx.h"

#include "BaseObj.h"
#include "Collider.h"


class Physics
{
	public:
		Physics();
		~Physics();

		void Update();

		void AddCollider(weak<Collider> _col);
		void DrawColliders();

	private:
		std::vector<weak<Collider>> m_colliders;
};