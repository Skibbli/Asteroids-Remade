#include "stdafx.h"

#include "Input.h"
#include "GamestateManager.h"
#include "Level.h"
#include "Title.h"
#include "Resources.h"


int main()
{
	int nva = al_get_num_video_adapters();

	//ALLEGRO_MONITOR_INFO info;
	//al_get_monitor_info(0, &info);

	ALLEGRO_DISPLAY *display = NULL;
	//ALLEGRO_DISPLAY_MODE disp_data;

	//al_get_display_mode(al_get_num_display_modes(), &disp_data);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	al_set_new_display_flags(ALLEGRO_RESIZABLE);

	int width = 1000;
	int height = 1000;

	if (!al_init())									//initialize Allegro
	{
		al_show_native_message_box(display, "You Fucked Up", NULL, "Go fix your mistake NOW!", NULL, 0);
		return -1;
	}

	display = al_create_display(1000, 1000);
	al_set_window_title(display, "More Fucking Asteroids");

	//display = al_create_display(info.x2 - info.x1, info.y2 - info.y1);		//create display

	if (!display)									//test display object
	{
		al_show_native_message_box(display, "You Fucked Up", " ", "Go fix your display mistake NOW!", NULL, 0);
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

	Input::Initialise(*display);
	Resources::GetInstance().Initialise();

	GamestateManager stateManager;

	stateManager.AddState(new Title(&stateManager, display));

	//Set game loop condition and enter game loop
	bool gameRunning = true;

	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_EVENT ev;

	float FPS = 60.0f;

	al_hide_mouse_cursor(display);

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	while (gameRunning)
	{	
		al_wait_for_event(event_queue, &ev);

		Input::CheckForInput();
		gameRunning = stateManager.Update();
		stateManager.Render();		
	}

	return 0;
}