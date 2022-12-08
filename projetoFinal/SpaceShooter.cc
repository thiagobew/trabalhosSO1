#include "include/SpaceShooter.h"

__BEGIN_API

Thread *SpaceShooter::playerShipThread;
Thread *SpaceShooter::windowThread;
Thread *SpaceShooter::keyboardThread;
Thread *SpaceShooter::collisionThread;

PlayerShip *SpaceShooter::playerShipObj;
Window *SpaceShooter::windowObj;
Keyboard *SpaceShooter::kBoardObj;
Collision *SpaceShooter::collisionObj;

__END_API
