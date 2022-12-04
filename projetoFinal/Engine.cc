#include <stdexcept>
#include <iostream>

#include "include/Engine.h"
#include "include/GameConfigs.h"
#include "include/Timer.h"

__BEGIN_API

Engine::Engine() {}

Engine::~Engine()
{
	engineSprite.reset();
}

// initialize Allegro, the _display window, the addons, the timers, and event sources
void Engine::init()
{

	loadSprites();
}

// repeatedly call the state manager function until the _state is EXIT
void Engine::run()
{
	while (!GameConfigs::finished)
	{
		Thread::yield();
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

void Engine::draw()
{
	this->engineSprite->draw_region(row, col, 47.0, 40.0, shipPosition, 0);
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

	// Go to resources directory
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "resources");
	al_change_directory(al_path_cstr(path, '/'));

	// sprites
	engineSprite = std::make_shared<Sprite>("Sprite2.png");

	// delete path
	al_destroy_path(path);
}

__END_API