#include <stdexcept>
#include <iostream>

#include "include/PlayerShip.h"
#include "include/GameConfigs.h"

__BEGIN_API

PlayerShip::PlayerShip()
{
	this->loadSprites();
}

PlayerShip::PlayerShip(Keyboard *kBoardHandler)
{
	this->_kBoardHandler = kBoardHandler;
	this->loadSprites();
}

PlayerShip::~PlayerShip()
{
	shipSprite.reset();
}

void PlayerShip::run()
{
	while (!GameConfigs::finished)
	{
		// db<PlayerShip>(TRC) << ">>>> PLAYER SHIP starting loop\n";
		db<PlayerShip>(TRC) << this->shipPosition.x << " - " << this->shipPosition.y << "\n";

		this->processAction();
		Thread::yield();
	}
}

void PlayerShip::draw()
{
	this->shipSprite->draw_region(this->row, this->col, 47.0, 40.0, this->shipPosition, 0);
}

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
	if (this->_kBoardHandler->getKbKeyIsPressed(KbKey::MOVE_UP))
		this->speed.y -= 250;
	if (this->_kBoardHandler->getKbKeyIsPressed(KbKey::MOVE_DOWN))
		this->speed.y += 250;
	if (this->_kBoardHandler->getKbKeyIsPressed(KbKey::MOVE_LEFT))
		this->speed.x -= 250;
	if (this->_kBoardHandler->getKbKeyIsPressed(KbKey::MOVE_RIGHT))
		this->speed.x += 250;
	if (this->_kBoardHandler->getKbKeyIsPressed(KbKey::NUM_1))
		this->handleStrongAttack();
	if (this->_kBoardHandler->getKbKeyIsPressed(KbKey::SPACE))
		this->handleWeakAttack();
}

void PlayerShip::handleWeakAttack()
{
	std::cout << "Ataque normal\n";
}

void PlayerShip::handleStrongAttack()
{
	std::cout << "Missel\n";
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

Point PlayerShip::getBottomLeftPoint() { return Point(this->shipPosition.x - 8, this->shipPosition.y + 8); }

Point PlayerShip::getTopLeftPoint() { return Point(this->shipPosition.x - 8, this->shipPosition.y - 8); }

Point PlayerShip::getBottomRightPoint() { return Point(this->shipPosition.x + 8, this->shipPosition.y + 8); }

Point PlayerShip::getTopRightPoint() { return Point(this->shipPosition.x + 8, this->shipPosition.y - 8); }

Point PlayerShip::getMidPoint() { return this->shipPosition; }

bool PlayerShip::inWindow() { return true; }

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