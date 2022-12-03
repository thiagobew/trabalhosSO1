#include "include/Engine.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdexcept>
#include <iostream>

#include "include/Timer.h"

Engine::Engine(int w, int h, int fps) : _displayWidth(w), _displayHeight(h),
										_fps(fps), _timer(NULL), _eventQueue(NULL), _finish(false)
{
}

Engine::~Engine()
{
	if (this->_timer != NULL)
		al_destroy_timer(this->_timer);
	if (this->_eventQueue != NULL)
		al_destroy_event_queue(this->_eventQueue);
	if (this->_display != NULL)
		al_destroy_display(this->_display);

	bg.reset();
	spaceShip.reset();
}

// initialize Allegro, the _display window, the addons, the timers, and event sources
void Engine::init()
{
	// initialize allegro
	al_init();
	// create the display
	if ((this->_display = al_create_display(this->_displayWidth, this->_displayHeight)) == NULL)
	{
		std::cout << "Cannot initialize the display\n";
		exit(1);
	}
	// initialize addons
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	// initialize our timers
	if ((this->_timer = al_create_timer(1.0 / this->_fps)) == NULL)
	{
		std::cout << "error, could not create timer\n";
		exit(1);
	}

	if ((this->_eventQueue = al_create_event_queue()) == NULL)
	{
		std::cout << "error, could not create event queue\n";
		exit(1);
	}

	// register our allegro _eventQueue
	al_register_event_source(this->_eventQueue, al_get_display_event_source(_display));
	al_register_event_source(this->_eventQueue, al_get_timer_event_source(_timer));
	al_start_timer(_timer);
	// install keyboard
	if (!al_install_keyboard())
	{
		std::cerr << "Could not install keyboard\n";
	}

	// register keyboard
	al_register_event_source(this->_eventQueue, al_get_keyboard_event_source());

	loadSprites();
}

// repeatedly call the state manager function until the _state is EXIT
void Engine::run()
{
	float prevTime = 0;
	// main engine loop
	while (!_finish)
	{
		gameLoop(prevTime);
	}
}

void Engine::gameLoop(float &prevTime)
{
	ALLEGRO_EVENT event;
	ALLEGRO_KEYBOARD_STATE kBoard;
	bool redraw = true;
	float crtTime;

	// input
	al_get_keyboard_state(&kBoard);
	input(kBoard); // irá retornar uma tecla de ação. TODO: necessário transformar em Thread e fazer a ação

	// get event
	al_wait_for_event(this->_eventQueue, &event);

	// _display closes
	if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		this->_finish = true;
		return;
	}

	// timer
	if (event.type == ALLEGRO_EVENT_TIMER)
	{
		crtTime = al_current_time();
		this->update(crtTime - prevTime);
		prevTime = crtTime;
		redraw = true;
	}

	// render
	if (redraw && al_is_event_queue_empty(_eventQueue))
	{
		redraw = false;
		this->draw();
		al_flip_display();
	}
}

// update the game mode
void Engine::update(double dt)
{
	// Spaceship
	shipPosition = shipPosition + speed * dt;
	this->updateShipAnimation(); // must happen before we reset our speed
	this->speed = Vector(0, 0);	 // reset our speed
	this->checkExceedingWindowLimit();

	// background
	this->bgMid = this->bgMid + this->bgSpeed * dt;
	if (bgMid.x >= 800)
	{
		bgMid.x = 0;
	}
}

// draws for the game mode
void Engine::draw()
{
	this->drawBackground();
	this->drawShip(spaceShip, 0);
}

void Engine::checkExceedingWindowLimit()
{
	// check x bound and adjust if out
	if (this->shipPosition.x > 800 - 16)
		this->shipPosition.x = 800 - 16;
	else if (this->shipPosition.x < 16)
		this->shipPosition.x = 16;
	// check y bound and adjust if out
	if (this->shipPosition.y > 600 - 16)
		this->shipPosition.y = 600 - 16;
	else if (this->shipPosition.y < 16)
		this->shipPosition.y = 16;
}

act::action Engine::input(ALLEGRO_KEYBOARD_STATE &kb)
{
	if (al_key_down(&kb, ALLEGRO_KEY_UP))
	{
		speed.y -= 250;
	}
	if (al_key_down(&kb, ALLEGRO_KEY_RIGHT))
	{
		speed.x += 250;
	}
	if (al_key_down(&kb, ALLEGRO_KEY_DOWN))
	{
		speed.y += 250;
	}
	if (al_key_down(&kb, ALLEGRO_KEY_LEFT))
	{
		speed.x -= 250;
	}
	if (al_key_down(&kb, ALLEGRO_KEY_1))
	{
		std::cout << "missel\n";
		return act::action::FIRE_PRIMARY;
	}
	if (al_key_down(&kb, ALLEGRO_KEY_SPACE))
	{
		std::cout << "tiro normal\n";
		return act::action::FIRE_SECONDARY;
	}
	if (al_key_down(&kb, ALLEGRO_KEY_ESCAPE))
	{
		std::cout << "sair\n";
		return act::action::QUIT_GAME;
	}

	return act::action::NO_ACTION;
}

void Engine::drawShip(std::shared_ptr<Sprite> sprite, int flags)
{
	sprite->draw_region(row, col, 47.0, 40.0, shipPosition, flags);
}

void Engine::drawBackground()
{
	bg->draw_parallax_background(bgMid.x, 0);
}

void Engine::updateShipAnimation()
{
	if (this->speed.x > 0)
	{
		this->col = 1;
		if (this->speed.y > 0)
			this->row = 2;
		else if (this->speed.y < 0)
			this->row = 0;
		else
			this->row = 1;
	}
	else
	{
		this->col = 0;
		if (this->speed.y > 0)
			this->row = 2;
		else if (this->speed.y < 0)
			this->row = 0;
		else
			this->row = 1;
	}
}

void Engine::loadSprites()
{
	// Create Ship
	shipPosition = Point(215, 245);
	color = al_map_rgb(0, 200, 0);

	// represents the middle of the image width-wise, and top height-wise
	bgMid = Point(0, 0);
	fgMid = Point(800, 0);
	fg2Mid = Point(300, 300);
	bgSpeed = Vector(50, 0);
	fgSpeed = Vector(-90, 0);

	// Go to resources directory
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "resources");
	al_change_directory(al_path_cstr(path, '/'));
	// sprites
	spaceShip = std::make_shared<Sprite>("Sprite2.png"); // espaçonave do usuário
	bg = std::make_shared<Sprite>("BGstars.png");		 // fundo da tela - background
	// delete path
	al_destroy_path(path);
}
