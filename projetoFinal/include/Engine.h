/**
 * @file Engine.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef ENGINE_H
#define ENGINE_H

#include "GameConfigs.h"
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

class Engine
{

public:
	Engine();
	~Engine();

	void init();
	void run();
	void draw();
	void update(double dt);

	void processAction(act::GameAction action);

private:
	void loadSprites();

	// Spaceship data
	void checkExceedingWindowLimit();
	void updateShipAnimation();
	std::shared_ptr<Sprite> engineSprite;
	Point shipPosition;		/**< ship position */
	ALLEGRO_COLOR color;	/**< ship color */
	SOLUTION::Vector speed; /**< movement speed in any direction */
	int row;				/**<row of animation to be played */
	int col;				/**< column of animation to be played */
};

__END_API

#endif
