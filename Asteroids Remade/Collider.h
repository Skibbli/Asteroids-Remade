#ifndef COLLIDER_H
#define COLLIDER_H

#include "stdafx.h"

#include "Maths.h"


struct Collision
{
	Collision(Enums::OBJECTS _collTypeHit, int _dmg) { s_collTypeHit = _collTypeHit; s_dmg = _dmg; };

	int s_dmg;
	Enums::OBJECTS s_collTypeHit;
};

class Collider
{
	public:
		Collider();
		~Collider();

		bool GetIsLive();
		void SetIsLive(bool _live);

		float GetDamage();
		void SetDamage(int _dmg);
		
		Vec2 GetPos();

		Enums::OBJECTS GetObjectType();
		Enums::COLTYPE GetColliderType();
		void SetColliderType(Enums::OBJECTS _type);

		void AddCollision(Enums::OBJECTS _obj, int _dmg);
		void ResetCollisions();
		std::vector<Collision>& GetCollisions();

		virtual void CheckCollision(weak<Collider> _col);
		virtual void Update();
		virtual void DrawCollider();		

	protected:
		bool m_isLive;
		int m_dmg;
		
		Vec2 m_pos;
		Enums::OBJECTS m_objType;
		Enums::COLTYPE m_colType;

		std::vector<Collision> m_collDets;
};

#endif