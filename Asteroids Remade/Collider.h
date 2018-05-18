#include "stdafx.h"


struct Collision
{
	Collision(weak<Collider> _colHit, bool _colOcc) { s_collOcc = _colOcc; s_objHit = _colHit; };

	bool s_collOcc;
	weak<Collider> s_objHit;
};


class Collider : public std::enable_shared_from_this<Collider>
{
	public:
		Collider();
		Collider(OBJECTS _obj, Vec2 _pos, float _radius);
		~Collider();

		void SetIsLive(bool _isLive);
		bool GetIsLive();
		void SetPos(Vec2 _pos);
		void CheckCollision(weak<Collider> _col);
		void AddCollision(weak<Collider> _col);
		std::vector<Collision> GetCollisions();
		OBJECTS GetObjType();
		void ResetCollisions();
		void DrawCollider();

	private:
		bool m_isLive;

		float m_radius;

		Vec2 m_pos;
		OBJECTS m_objType;

		std::vector<Collision> m_collDets;

		BaseObj *m_parent;
};