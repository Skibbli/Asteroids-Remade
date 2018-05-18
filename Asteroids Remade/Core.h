#include "stdafx.h"

#include "Physics.h"
#include "GamestateManager.h"


class Core
{
	public:
		Core();
		~Core();

		static Core& GetInstance();
		bool Initialise();
		void Start();
		void Run();
		void Shutdown();

		void AddCollider(weak<Collider> _col);

	private:
		Physics m_physicsEngine;

		ALLEGRO_DISPLAY *m_display;
		GamestateManager m_stateManager;
};