#include "Physics.h"


Physics::Physics()
{

}

void Physics::Update()
{
	for (int i = 0; i < m_colliders.size() - 1; i++)
	{
		if (m_colliders.at(i).lock().get()->GetIsLive())
		{
			m_colliders.at(i).lock().get()->ResetCollisions();

			for (int j = i; j < m_colliders.size(); j++)
			{
				if (m_colliders.at(j).lock().get()->GetIsLive())
				{
					m_colliders.at(j).lock().get()->CheckCollision(m_colliders.at(j));
				}
			}
		}
	}
}

void Physics::AddCollider(weak<Collider> _col)
{
	m_colliders.push_back(_col);
}

void Physics::DrawColliders()
{
	for (weak<Collider> _col : m_colliders)
		_col.lock().get()->DrawCollider();
}

Physics::~Physics()
{

}