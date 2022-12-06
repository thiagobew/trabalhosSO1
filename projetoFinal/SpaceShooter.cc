#include "include/SpaceShooter.h"

__BEGIN_API

Thread *SpaceShooter::playerShipThread;
Thread *SpaceShooter::windowThread;
Thread *SpaceShooter::keyboardThread;

PlayerShip *SpaceShooter::playerShipObj;
Window *SpaceShooter::windowObj;
Keyboard *SpaceShooter::kBoardObj;

__END_API
