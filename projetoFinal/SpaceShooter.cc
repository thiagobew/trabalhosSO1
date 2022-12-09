#include "include/SpaceShooter.h"

__BEGIN_API

Thread *SpaceShooter::playerShipThread;
Thread *SpaceShooter::windowThread;
Thread *SpaceShooter::keyboardThread;
Thread *SpaceShooter::collisionThread;
Thread *SpaceShooter::purpleShipsControlThread;

PlayerShip *SpaceShooter::playerShipObj;
Window *SpaceShooter::windowObj;
Keyboard *SpaceShooter::kBoardObj;
Collision *SpaceShooter::collisionObj;
PurpleEnemiesControl *SpaceShooter::purpleShipsControlObj;

__END_API
