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
#include "Point.h"
#include "traits.h"
#include "Drawable.h"
#include <memory>

__BEGIN_API

class PlayerShip : public Drawable
{

public:
	typedef act::KbKey KbKey;

	PlayerShip();
	PlayerShip(Keyboard *kBoardHandler);
	~PlayerShip();

	void run();
	void draw();
	void update(double diffTime);

	// Drawable methods
	bool inWindow();
	Point getMidPoint();
	Point getTopLeftPoint();
	Point getTopRightPoint();
	Point getBottomLeftPoint();
	Point getBottomRightPoint();

private:
	// Logic methods
	void checkExceedingWindowLimit();
	void updateShipAnimation();
	void processAction();
	void handleWeakAttack();
	void handleStrongAttack();

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
