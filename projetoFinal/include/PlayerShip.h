/**
 * @file PlayerShip.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "GameConfigs.h"
#include "KeyBoard.h"
#include "Sprite.h"
#include "Vector.h"
#include "Action.h"
#include "thread.h"
#include "traits.h"
#include <memory>

__BEGIN_API

// forward declarations
class Menu;
class Root;

class PlayerShip
{

public:
	PlayerShip();
	PlayerShip(Keyboard *kBoardHandler);
	~PlayerShip();

	void init();
	void run();
	void draw();
	void update(double diffTime);

private:
	// Logic methods
	void checkExceedingWindowLimit();
	void updateShipAnimation();
	void processAction();

	// Action variables
	Keyboard *_kBoardHandler;

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
