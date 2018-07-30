#include "stdafx.h"

#include "Core.h"
#include "Input.h"
#include "Resources.h"
#include "Title.h"
#include "GamestateManager.h"
#include "Time.h"


Core::Core() {}

bool Core::Initialise()
{
	//ALLEGRO_MONITOR_INFO info;
	//al_get_monitor_info(0, &info);

	//ALLEGRO_DISPLAY_MODE disp_data;

	//al_get_display_mode(al_get_num_display_modes(), &disp_data);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	al_set_new_display_flags(ALLEGRO_RESIZABLE);

	int width = 1000;
	int height = 1000;

	// Initialize Allegro
	if (!al_init())									
	{
		al_show_native_message_box(m_display, "You Fucked Up", NULL, "Go fix your mistake NOW!", NULL, 0);
		return -1;
	}

	m_display = al_create_display(1000, 1000);
	al_set_window_title(m_display, "More Fucking Asteroids");

	// Test display object
	if (!m_display)
	{
		al_show_native_message_box(m_display, "You Fucked Up", " ", "Go fix your display mistake NOW!", NULL, 0);
		return -1;
	}

	//===============================
	//ADDON INSTALLATION
	//===============================
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();

	Input::GetInstance().Initialise(m_display);
	Resources::GetInstance().Initialise();

	m_taskbarIcon = Resources::GetInstance().LoadBmp("ULTIMATE SHIP.png");
	al_set_display_icon(m_display, m_taskbarIcon.GetBitmap());

	return 1;
}

void Core::Start() {}

void Core::Run()
{
	//Set game loop condition and enter game loop
	bool gameRunning = true;

	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *eventQueue = NULL;
	ALLEGRO_EVENT ev;

	float FPS = 60.0f;

	al_hide_mouse_cursor(m_display);

	eventQueue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(eventQueue, al_get_timer_event_source(timer));
	al_register_event_source(eventQueue, al_get_display_event_source(m_display));

	al_start_timer(timer);

	UpdateDisplaySize(1000, 1000);
	m_stateManager.UpdateDisplaySize(m_displaySize);

	m_stateManager.SetDisplay(m_display);
	m_stateManager.AddState(std::make_shared<Title>());

	while (gameRunning)
	{
		al_wait_for_event(eventQueue, &ev);

		if(ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE)
		{
			UpdateDisplaySize(ev.display.width, ev.display.height);
		}

		Time::Update();
		Input::GetInstance().CheckForInput();
		gameRunning = m_stateManager.Update();

		if(gameRunning)
		{
			m_stateManager.Render();
		}
	}
}

Core& Core::GetInstance()
{
	static Core instance;

	return instance;
}

GamestateManager& Core::GetStateManager()
{
	return m_stateManager;
}

ALLEGRO_DISPLAY* Core::GetDisplay()
{
	return m_display;
}

DisplayInfo Core::GetDisplaySize()
{
	return m_displaySize;
}

// Updates display size following window re-size and updates size for each object in the game
void Core::UpdateDisplaySize(float _width, float _height)
{
	m_displaySize.s_width = _width;
	m_displaySize.s_height = _height;

	m_displaySize.s_wRatio = m_displaySize.s_width / 1000;
	m_displaySize.s_hRatio = m_displaySize.s_height / 1000;

	al_resize_display(m_display, m_displaySize.s_width, m_displaySize.s_height);

	if(m_displaySize.s_width > m_displaySize.s_height)
	{
		m_displaySize.s_wOffset = (m_displaySize.s_width - m_displaySize.s_height) / 2;
		m_displaySize.s_hOffset = 0;
		m_displaySize.s_wRatio = m_displaySize.s_hRatio;
	}

	else
	{
		m_displaySize.s_wOffset = 0;
		m_displaySize.s_hOffset = (m_displaySize.s_height - m_displaySize.s_width) / 2;
		m_displaySize.s_hRatio = m_displaySize.s_wRatio;
	}

	for(BaseObject* obj : m_gameObjects)
	{
		if(obj != nullptr)
		{
			obj->UpdateDisplaySize(m_displaySize);
		}
	}

	m_stateManager.UpdateDisplaySize(m_displaySize);
}

void Core::AddGameObject(BaseObject* _obj)
{
	m_gameObjects.push_back(_obj);
}

void Core::RemoveGameObject(BaseObject* _obj)
{
	for(unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		if(m_gameObjects.at(i) == _obj)
		{
			m_gameObjects.at(i) = nullptr;
			m_gameObjects.erase(m_gameObjects.begin() + i);

			break;
		}
	}
}

void Core::UpdatePhysics()
{
	m_physicsEngine.Update();
}

void Core::AddCollider(weak<Collider> _col)
{
	m_physicsEngine.AddCollider(_col);
}

void Core::DrawColliders()
{
	m_physicsEngine.DrawColliders();
}

void Core::ResetPhysicsEngine()
{
	m_physicsEngine.Reset();
}

void Core::Shutdown()
{
	m_stateManager.Shutdown();
	m_physicsEngine.Shutdown();
	Input::GetInstance().Shutdown();
	al_destroy_display(m_display);
}

Core::~Core() {}