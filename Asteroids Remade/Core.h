#ifndef CORE_H
#define CORE_H

#include "stdafx.h"

#include "GamestateManager.h"
#include "Physics.h"
#include "BaseObject.h"
#include "ResourceStructs.h"


class Collider;

class Core
{
	public:	
		bool Initialise();
		void Start();
		void Run();
		void Shutdown();

		static Core& GetInstance();
		GamestateManager& GetStateManager();

		ALLEGRO_DISPLAY* GetDisplay();
		DisplayInfo GetDisplaySize();
		void UpdateDisplaySize(float _width, float _height);

		void AddGameObject(BaseObject* _obj);
		void RemoveGameObject(BaseObject* _obj);

		void UpdatePhysics();
		void AddCollider(weak<Collider> _col);
		void DrawColliders();
		void ResetPhysicsEngine();

	private:
		Physics m_physicsEngine;

		ALLEGRO_DISPLAY *m_display;
		DisplayInfo m_displaySize;
		Bitmap m_taskbarIcon;
		GamestateManager m_stateManager;

		std::vector<BaseObject*> m_gameObjects;

		Core(Core const&);
		void operator=(Core const&);

		Core();
		~Core();
};

#endif