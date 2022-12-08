#include <stdexcept>
#include <iostream>

#include "include/PlayerShip.h"
#include "include/GameConfigs.h"
#include "include/Laser.h"

__BEGIN_API

int PlayerShip::HALF_PLAYER_SIZE = 8;
int PlayerShip::PLAYER_SIZE = 16;
int PlayerShip::PLAYER_TRAVEL_SPEED = 250;
int PlayerShip::WEAK_ATTACK_DELAY = 8;
int PlayerShip::STRONG_ATTACK_DELAY = 20;
Vector PlayerShip::PLAYER_PROJECTILE_SPEED = Vector(500, 0);
ALLEGRO_COLOR PlayerShip::PLAYER_COLOR = al_map_rgb(150, 0, 0);

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

void PlayerShip::hit() { this->life -= 1; }

bool PlayerShip::isDead() { return this->life <= 0; }

bool PlayerShip::stillLive() { return (!this->isDead()); }

void PlayerShip::run()
{
	while (!GameConfigs::finished)
	{
		// Não executa enquanto as referências não forem corretas
		if (this->_window == nullptr || this->_collision == nullptr)
			Thread::yield();

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
		this->speed.y -= PlayerShip::PLAYER_TRAVEL_SPEED;
	if (this->_kBoardHandler->getKbKeyIsPressed(KbKey::MOVE_DOWN))
		this->speed.y += PlayerShip::PLAYER_TRAVEL_SPEED;
	if (this->_kBoardHandler->getKbKeyIsPressed(KbKey::MOVE_LEFT))
		this->speed.x -= PlayerShip::PLAYER_TRAVEL_SPEED;
	if (this->_kBoardHandler->getKbKeyIsPressed(KbKey::MOVE_RIGHT))
		this->speed.x += PlayerShip::PLAYER_TRAVEL_SPEED;
	if (this->_kBoardHandler->getKbKeyIsPressed(KbKey::NUM_1))
		this->handleStrongAttack();
	if (this->_kBoardHandler->getKbKeyIsPressed(KbKey::SPACE))
		this->handleWeakAttack();
}

void PlayerShip::handleWeakAttack()
{
	// Verifica se já passou o delay do weak shot
	if (this->laserTimer->getCount() > PlayerShip::WEAK_ATTACK_DELAY)
	{
		Laser *laserToShot = new Laser(this->shipPosition, PlayerShip::PLAYER_COLOR, PlayerShip::PLAYER_PROJECTILE_SPEED, true);
		this->laserTimer->srsTimer();
		// Coloca referência do tiro na classe Collision e Window
		this->_window->addDrawableItem(laserToShot);
		this->_collision->addPlayerShot(laserToShot);
	}
}

void PlayerShip::handleStrongAttack()
{
	// Verifica se já passou o delay do weak shot
	if (this->missileTimer->getCount() > PlayerShip::STRONG_ATTACK_DELAY)
	{
		Missile *missileToShot = new Missile(this->shipPosition, PlayerShip::PLAYER_COLOR, PlayerShip::PLAYER_PROJECTILE_SPEED, true);
		this->missileTimer->srsTimer();
		// Coloca referência do tiro na classe Collision e Window
		this->_collision->addPlayerShot(missileToShot);
		this->_window->addDrawableItem(missileToShot);
	}
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
	if (this->shipPosition.x > 800 - PlayerShip::PLAYER_SIZE)
		this->shipPosition.x = 800 - PlayerShip::PLAYER_SIZE;
	else if (this->shipPosition.x < PlayerShip::PLAYER_SIZE)
		this->shipPosition.x = PlayerShip::PLAYER_SIZE;
	// check y bound and adjust if out
	if (this->shipPosition.y > 600 - PlayerShip::PLAYER_SIZE)
		this->shipPosition.y = 600 - PlayerShip::PLAYER_SIZE;
	else if (this->shipPosition.y < PlayerShip::PLAYER_SIZE)
		this->shipPosition.y = PlayerShip::PLAYER_SIZE;
}

int PlayerShip::getSize() { return PlayerShip::PLAYER_SIZE; }

Point PlayerShip::getPosition() { return this->shipPosition; }

void PlayerShip::init()
{
	this->loadSprites();
	// Create the timers for the weapons
	this->laserTimer = std::make_shared<Timer>(GameConfigs::fps);
	this->laserTimer->create();
	this->laserTimer->startTimer();

	this->missileTimer = std::make_shared<Timer>(GameConfigs::fps);
	this->missileTimer->create();
	this->missileTimer->startTimer();
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