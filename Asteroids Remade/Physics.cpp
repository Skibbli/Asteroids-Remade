#include "Physics.h"

#include "Collider.h"


Physics::Physics() {}

// Cycles through colliders and checks for collision with other colliders
void Physics::Update()
{
	for (Uint i = 0; i < m_colliders.size(); i++)
	{
		if (m_colliders.at(i).lock()->GetIsLive())
		{
			for (Uint j = i + 1; j < m_colliders.size(); j++)
			{
				if (m_colliders.at(j).lock()->GetIsLive())
				{
					m_colliders.at(i).lock()->CheckCollision(m_colliders.at(j));
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
	{
		if (_col.lock()->GetIsLive())
			_col.lock()->DrawCollider();
	}		
}

void Physics::Reset()
{
	m_colliders.clear();
}

void Physics::Shutdown() {}

Physics::~Physics() {}