/**
 * @file PlayerShip.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <memory>
#include "threads/thread.h"
#include "threads/traits.h"

#include "GameConfigs.h"
#include "KeyBoard.h"
#include "Sprite.h"
#include "Vector.h"
#include "Action.h"
#include "Point.h"
#include "Drawable.h"
#include "Window.h"
#include "Laser.h"
#include "Missile.h"
#include "Timer.h"

__BEGIN_API

class PlayerShip : public Drawable
{

public:
	typedef act::KbKey KbKey;

	PlayerShip();
	PlayerShip(Keyboard *kBoardHandler);
	~PlayerShip();

	void setWindowReference(Window *window) { _window = window; }

	void run();
	void draw();
	void hit();
	bool isDead();
	bool stillLive();
	void update(double diffTime);

	// Drawable methods
	int getSize();
	Point getPosition();

private:
	void init();

	// Logic variables
	static int HALF_PLAYER_SIZE;
	static int PLAYER_SIZE;
	static int PLAYER_TRAVEL_SPEED;
	static int WEAK_ATTACK_DELAY;
	static int STRONG_ATTACK_DELAY;
	static Vector PLAYER_PROJECTILE_SPEED;
	static ALLEGRO_COLOR PLAYER_COLOR;
	std::shared_ptr<Timer> laserTimer;
	std::shared_ptr<Timer> missileTimer;
	int life = 3;

	// Logic methods
	void checkExceedingWindowLimit();
	void updateShipAnimation();
	void processAction();
	void handleWeakAttack();
	void handleStrongAttack();

	// Objects variables
	Keyboard *_kBoardHandler;
	Window *_window;

	// Draw information
	std::shared_ptr<Sprite> shipSprite;
	Point shipPosition;		/**< ship position */
	SOLUTION::Vector speed; /**< movement speed in any direction */
	int row;				/**<row of animation to be played */
	int col;				/**< column of animation to be played */
	void loadSprites();
	bool spritesLoaded = false;
};

__END_API

#endif
