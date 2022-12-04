#include <stdexcept>
#include <iostream>

#include "include/PlayerShip.h"
#include "include/GameConfigs.h"

__BEGIN_API

PlayerShip::PlayerShip()
{
	this->init();
}

PlayerShip::PlayerShip(Keyboard *kBoardHandler)
{
	this->_kBoardHandler = kBoardHandler;
	this->init();
}

PlayerShip::~PlayerShip()
{
	shipSprite.reset();
}

void PlayerShip::init()
{
	this->loadSprites();
}

// repeatedly call the state manager function until the _state is EXIT
void PlayerShip::run()
{
	while (!GameConfigs::finished)
	{
		db<PlayerShip>(TRC) << ">>>> PLAYER SHIP starting loop\n";
		this->processAction();
		Thread::yield();
	}
}

void PlayerShip::draw()
{
	db<PlayerShip>(TRC) << "Ship Draw\n";
	this->shipSprite->draw_region(this->row, this->col, 47.0, 40.0, this->shipPosition, 0);
}

// update the game mode
void PlayerShip::update(double diffTime)
{
	this->shipPosition = this->shipPosition + this->speed * diffTime;
	this->updateShipAnimation(); // must happen before we reset our speed
	this->speed = Vector(0, 0);	 // reset our speed
	this->checkExceedingWindowLimit();
}

void PlayerShip::processAction()
{
	if (this->_kBoardHandler == nullptr)
		return;

	act::GameAction action = this->_kBoardHandler->getCurrentAction();
	db<PlayerShip>(TRC) << "Current Action: " << action << "\n";
}

void PlayerShip::updateShipAnimation()
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

void PlayerShip::checkExceedingWindowLimit()
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

void PlayerShip::loadSprites()
{
	db<PlayerShip>(TRC) << "Player Ship loading sprites\n";

	this->spritesLoaded = true;

	// Create Ship
	this->shipPosition = Point(215, 245);
	this->speed = Vector(0, 0);

	// Go to resources directory
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "resources");
	al_change_directory(al_path_cstr(path, '/'));

	// sprites
	this->shipSprite = std::make_shared<Sprite>("Sprite2.png");

	// delete path
	al_destroy_path(path);
}

__END_API